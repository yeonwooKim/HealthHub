// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

/// @file file_io_url_loader.cc

#define __STDC_LIMIT_MACROS
#include <stdio.h>

#include <sstream>
#include <string>
#include <vector>

#include "ppapi/c/pp_stdint.h"
#include "ppapi/c/ppb_file_io.h"
#include "ppapi/cpp/directory_entry.h"
#include "ppapi/cpp/file_io.h"
#include "ppapi/cpp/file_ref.h"
#include "ppapi/cpp/file_system.h"
#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/message_loop.h"
#include "ppapi/cpp/module.h"
#include "ppapi/cpp/var.h"
#include "ppapi/cpp/var_array.h"
#include "ppapi/utility/completion_callback_factory.h"
#include "ppapi/utility/threading/simple_thread.h"

#include "ppapi/cpp/url_loader.h"
#include "url_loader_handler.h"

#include "ppapi/c/ppb_image_data.h"
#include "ppapi/cpp/graphics_2d.h"
#include "ppapi/cpp/image_data.h"

#ifndef INT32_MAX
#define INT32_MAX (0x7FFFFFFF)
#endif

#ifdef WIN32
#undef min
#undef max
#undef PostMessage

// Allow 'this' in initializer list
#pragma warning(disable : 4355)
#endif

namespace {
  typedef std::vector<std::string> StringVector;
  const char* const kLoadUrlMethodId = "getUrl";
  static const char kMessageArgumentSeparator = ':';

  uint32_t MakeColor(uint8_t r, uint8_t g, uint8_t b) {
    uint8_t a = 255;
    PP_ImageDataFormat format = pp::ImageData::GetNativeImageDataFormat();
    if (format == PP_IMAGEDATAFORMAT_BGRA_PREMUL) {
      return (a << 24) | (r << 16) | (g << 8) | b;
    } else {
      return (a << 24) | (b << 16) | (g << 8) | r;
    }
  }
}

/// The Instance class.  One of these exists for each instance of your NaCl
/// module on the web page.  The browser will ask the Module object to create
/// a new Instance for each occurrence of the <embed> tag that has these
/// attributes:
///     type="application/x-nacl"
///     src="file_io_url_loader.nmf"
class FileIoUrlLoaderInstance : public pp::Instance {
  public:
    /// The constructor creates the plugin-side instance.
    /// @param[in] instance the handle to the browser-side plugin instance.
    explicit FileIoUrlLoaderInstance(PP_Instance instance)
      : pp::Instance(instance),
      callback_factory_(this),
      callback_factory_graphics_(this),
      file_system_(this, PP_FILESYSTEMTYPE_LOCALPERSISTENT),
      buffer_(NULL),
      device_scale_(1.0f),
      file_system_ready_(false),
      file_thread_(this) {}

    virtual ~FileIoUrlLoaderInstance() { file_thread_.Join(); }

    virtual bool Init(uint32_t /*argc*/,
        const char * /*argn*/ [],
        const char * /*argv*/ []) {
      file_thread_.Start();
      // Open the file system on the file_thread_. Since this is the first
      // operation we perform there, and because we do everything on the
      // file_thread_ synchronously, this ensures that the FileSystem is open
      // before any FileIO operations execute.
      file_thread_.message_loop().PostWork(
          callback_factory_.NewCallback(&FileIoUrlLoaderInstance::OpenFileSystem));
      return true;
    }

    virtual void DidChangeView(const pp::View& view) {
      device_scale_ = view.GetDeviceScale();
      pp::Size new_size = pp::Size(view.GetRect().width() * device_scale_,
          view.GetRect().height() * device_scale_);

      if (!CreateContext(new_size))
        return;

      // When flush_context_ is null, it means there is no Flush callback in
      // flight. This may have happened if the context was not created
      // successfully, or if this is the first call to DidChangeView (when the
      // module first starts). In either case, start the main loop.
      if (flush_context_.is_null())
        MainLoop(0);
    }
  
  private:
    bool CreateContext(const pp::Size& new_size) {
      const bool kIsAlwaysOpaque = true;
      context_ = pp::Graphics2D(this, new_size, kIsAlwaysOpaque);
      // Call SetScale before BindGraphics so the image is scaled correctly on
      // HiDPI displays.
      context_.SetScale(1.0f / device_scale_);
      if (!BindGraphics(context_)) {
        fprintf(stderr, "Unable to bind 2d context!\n");
        context_ = pp::Graphics2D();
        return false;
      }

      // Allocate a buffer of palette entries of the same size as the new context.
      buffer_ = new uint8_t[new_size.width() * new_size.height() * 3]; // 3 for RGB
      size_ = new_size;

      return true;
    }
    
    void Update() {
      int width = size_.width();
      int height = size_.height();

      // Draw two rows of random values at the bottom.
      for (int y = 0; y < height; ++y) {
        size_t offset = y * width * 3;
        for (int x = 0; x < width; ++x) {
          buffer_[offset + x * 3] = y * 255 / height;       // R value for (x, y)
          buffer_[offset + x * 3 + 1] = x * 255 / height;   // G value for (x, y)
          buffer_[offset + x * 3 + 2] = 0;   // B value for (x, y)
        }
      }
    }

    void Paint() {
      // See the comment above the call to ReplaceContents below.
      PP_ImageDataFormat format = pp::ImageData::GetNativeImageDataFormat();
      const bool kDontInitToZero = false;
      pp::ImageData image_data(this, format, size_, kDontInitToZero);

      uint32_t* data = static_cast<uint32_t*>(image_data.data());
      if (!data)
        return;

      uint32_t num_pixels = size_.width() * size_.height();
      size_t offset = 0;
      for (uint32_t i = 0; i < num_pixels; ++i) {
        data[offset] = MakeColor (buffer_[offset * 3], buffer_[offset * 3 + 1], buffer_[offset * 3 + 2]);
        offset ++;
      }

      // Using Graphics2D::ReplaceContents is the fastest way to update the
      // entire canvas every frame. According to the documentation:
      //
      //   Normally, calling PaintImageData() requires that the browser copy
      //   the pixels out of the image and into the graphics context's backing
      //   store. This function replaces the graphics context's backing store
      //   with the given image, avoiding the copy.
      //
      //   In the case of an animation, you will want to allocate a new image for
      //   the next frame. It is best if you wait until the flush callback has
      //   executed before allocating this bitmap. This gives the browser the
      //   option of caching the previous backing store and handing it back to
      //   you (assuming the sizes match). In the optimal case, this means no
      //   bitmaps are allocated during the animation, and the backing store and
      //   "front buffer" (which the module is painting into) are just being
      //   swapped back and forth.
      //
      /*
      const pp::ImageData const_data = static_cast<const pp::ImageData>(image_data);
      const pp::Point top_left_ (0, 0);
      const pp::Rect src_rect_ (0, 0, 1000, 1000);
      context_.PaintImageData (const_data, top_left_, src_rect_); */
      context_.ReplaceContents(&image_data);

    }

    void MainLoop(int32_t) {
      if (context_.is_null()) {
        // The current Graphics2D context is null, so updating and rendering is
        // pointless. Set flush_context_ to null as well, so if we get another
        // DidChangeView call, the main loop is started again.
        flush_context_ = context_;
        return;
      }

      Update();
      Paint();
      // Store a reference to the context that is being flushed; this ensures
      // the callback is called, even if context_ changes before the flush
      // completes.
      flush_context_ = context_;
      context_.Flush(
          callback_factory_graphics_.NewCallback(&FileIoUrlLoaderInstance::MainLoop));
    }

    pp::CompletionCallbackFactory<FileIoUrlLoaderInstance> callback_factory_;
    pp::CompletionCallbackFactory<FileIoUrlLoaderInstance> callback_factory_graphics_;
    pp::FileSystem file_system_;
    pp::Graphics2D context_;
    pp::Graphics2D flush_context_;
    pp::Size size_;
    uint8_t* buffer_;
    float device_scale_;

    // Indicates whether file_system_ was opened successfully. We only read/write
    // this on the file_thread_.
    bool file_system_ready_;

    // We do all our file operations on the file_thread_.
    pp::SimpleThread file_thread_;

    void PostArrayMessage(const char* command, const StringVector& strings) {
      pp::VarArray message;
      // FILEIO prefix attached to the first index of VarArray
      // to differentiate message for fileIO and for urlLoader.
      message.Set(0, "FILEIO");
      message.Set(1, command);
      for (size_t i = 0; i < strings.size(); ++i) {
        message.Set(i + 2, strings[i]);
      }

      PostMessage(message);
    }

    void PostArrayMessage(const char* command) {
      PostArrayMessage(command, StringVector());
    }

    void PostArrayMessage(const char* command, const std::string& s) {
      StringVector sv;
      sv.push_back(s);
      PostArrayMessage(command, sv);
    }

    /// Handler for messages coming in from the browser via postMessage().  The
    /// @a var_message can contain anything: a JSON string; a string that encodes
    /// method names and arguments; etc.
    ///
    /// Here we use messages to communicate with the user interface
    ///
    /// @param[in] var_message The message posted by the browser.
    virtual void HandleMessage(const pp::Var& var_message) {
      if (!var_message.is_array())
        return;

      pp::VarArray messageArray(var_message);
      pp::Var prefix = messageArray.Get(0);

      if (prefix.AsString() == "URLLOADER") { ///< message from URL Loader
        std::string message = messageArray.Get(1).AsString();
        if (message.find(kLoadUrlMethodId) == 0) {
          // The argument to getUrl is everything after the first ':'.
          size_t sep_pos = message.find_first_of(kMessageArgumentSeparator);
          if (sep_pos != std::string::npos) {
            std::string url = message.substr(sep_pos + 1);
            printf("URLLoaderInstance::HandleMessage('%s', '%s')\n",
                message.c_str(),
                url.c_str());
            fflush(stdout);
            URLLoaderHandler* handler = URLLoaderHandler::Create(this, url);
            if (handler != NULL) {
              // Starts asynchronous download. When download is finished or when an
              // error occurs, |handler| posts the results back to the browser
              // vis PostMessage and self-destroys.

              handler->Start();
            }
          }
        }
      }
      else if (prefix.AsString() == "FILEIO") { ///< message from file IO
        // Message should be an array with the following elements:
        // [command, path, extra args]
        std::string command = messageArray.Get(1).AsString();
        std::string file_name = messageArray.Get(2).AsString();

        if (file_name.length() == 0 || file_name[0] != '/') {
          ShowStatusMessage("File name must begin with /");
          return;
        }

        printf("command: %s file_name: %s\n", command.c_str(), file_name.c_str());

        if (command == "load") {
          file_thread_.message_loop().PostWork(
              callback_factory_.NewCallback(&FileIoUrlLoaderInstance::Load, file_name));
        } else if (command == "save") {
          std::string file_text = messageArray.Get(3).AsString();
          file_thread_.message_loop().PostWork(callback_factory_.NewCallback(
                &FileIoUrlLoaderInstance::Save, file_name, file_text));
        } 
        /*else if (command == "delete") {
          file_thread_.message_loop().PostWork(
          callback_factory_.NewCallback(&FileIoUrlLoaderInstance::Delete, file_name));
          } else if (command == "list") {
          const std::string& dir_name = file_name;
          file_thread_.message_loop().PostWork(
          callback_factory_.NewCallback(&FileIoUrlLoaderInstance::List, dir_name));
          } else if (command == "makedir") {
          const std::string& dir_name = file_name;
          file_thread_.message_loop().PostWork(
          callback_factory_.NewCallback(&FileIoUrlLoaderInstance::MakeDir, dir_name));
          } else if (command == "rename") {
          const std::string new_name = messageArray.Get(3).AsString();
          file_thread_.message_loop().PostWork(callback_factory_.NewCallback(
          &FileIoUrlLoaderInstance::Rename, file_name, new_name));
          }*/
      }
      else {
        //TODO paint picture with received data!
      }
    }

    void OpenFileSystem(int32_t /* result */) {
      int32_t rv = file_system_.Open(1024 * 1024, pp::BlockUntilComplete());
      if (rv == PP_OK) {
        file_system_ready_ = true;
        // Notify the user interface that we're ready
        PostArrayMessage("READY");
      } else {
        ShowErrorMessage("Failed to open file system", rv);
      }
    }

    void Save(int32_t /* result */,
        const std::string& file_name,
        const std::string& file_contents) {
      if (!file_system_ready_) {
        ShowErrorMessage("File system is not open", PP_ERROR_FAILED);
        return;
      }
      pp::FileRef ref(file_system_, file_name.c_str());
      pp::FileIO file(this);

      int32_t open_result =
        file.Open(ref,
            PP_FILEOPENFLAG_WRITE | PP_FILEOPENFLAG_CREATE |
            PP_FILEOPENFLAG_TRUNCATE,
            pp::BlockUntilComplete());
      if (open_result != PP_OK) {
        ShowErrorMessage("File open for write failed", open_result);
        return;
      }

      // We have truncated the file to 0 bytes. So we need only write if
      // file_contents is non-empty.
      if (!file_contents.empty()) {
        if (file_contents.length() > INT32_MAX) {
          ShowErrorMessage("File too big", PP_ERROR_FILETOOBIG);
          return;
        }
        int64_t offset = 0;
        int32_t bytes_written = 0;
        do {
          bytes_written = file.Write(offset,
              file_contents.data() + offset,
              file_contents.length(),
              pp::BlockUntilComplete());
          if (bytes_written > 0) {
            offset += bytes_written;
          } else {
            ShowErrorMessage("File write failed", bytes_written);
            return;
          }
        } while (bytes_written < static_cast<int64_t>(file_contents.length()));
      }
      // All bytes have been written, flush the write buffer to complete
      int32_t flush_result = file.Flush(pp::BlockUntilComplete());
      if (flush_result != PP_OK) {
        ShowErrorMessage("File fail to flush", flush_result);
        return;
      }
      ShowStatusMessage("Save success");
    }

    void Load(int32_t /* result */, const std::string& file_name) {
      if (!file_system_ready_) {
        ShowErrorMessage("File system is not open", PP_ERROR_FAILED);
        return;
      }
      pp::FileRef ref(file_system_, file_name.c_str());
      pp::FileIO file(this);

      int32_t open_result =
        file.Open(ref, PP_FILEOPENFLAG_READ, pp::BlockUntilComplete());
      if (open_result == PP_ERROR_FILENOTFOUND) {
        ShowErrorMessage("File not found", open_result);
        return;
      } else if (open_result != PP_OK) {
        ShowErrorMessage("File open for read failed", open_result);
        return;
      }
      PP_FileInfo info;
      int32_t query_result = file.Query(&info, pp::BlockUntilComplete());
      if (query_result != PP_OK) {
        ShowErrorMessage("File query failed", query_result);
        return;
      }
      // FileIO.Read() can only handle int32 sizes
      if (info.size > INT32_MAX) {
        ShowErrorMessage("File too big", PP_ERROR_FILETOOBIG);
        return;
      }

      std::vector<char> data(info.size);
      int64_t offset = 0;
      int32_t bytes_read = 0;
      int32_t bytes_to_read = info.size;
      while (bytes_to_read > 0) {
        bytes_read = file.Read(offset,
            &data[offset],
            data.size() - offset,
            pp::BlockUntilComplete());
        if (bytes_read > 0) {
          offset += bytes_read;
          bytes_to_read -= bytes_read;
        } else if (bytes_read < 0) {
          // If bytes_read < PP_OK then it indicates the error code.
          ShowErrorMessage("File read failed", bytes_read);
          return;
        }
      }
      // Done reading, send content to the user interface
      std::string string_data(data.begin(), data.end());
      PostArrayMessage("DISP", string_data);
      ShowStatusMessage("Load success");
      ShowStatusMessage(string_data);
    }

    /*
    void Delete(int32_t, const std::string& file_name) {
      if (!file_system_ready_) {
        ShowErrorMessage("File system is not open", PP_ERROR_FAILED);
        return;
      }
      pp::FileRef ref(file_system_, file_name.c_str());

      int32_t result = ref.Delete(pp::BlockUntilComplete());
      if (result == PP_ERROR_FILENOTFOUND) {
        ShowStatusMessage("File/Directory not found");
        return;
      } else if (result != PP_OK) {
        ShowErrorMessage("Deletion failed", result);
        return;
      }
      ShowStatusMessage("Delete success");
    }

    void List(int32_t, const std::string& dir_name) {
      if (!file_system_ready_) {
        ShowErrorMessage("File system is not open", PP_ERROR_FAILED);
        return;
      }

      pp::FileRef ref(file_system_, dir_name.c_str());

      // Pass ref along to keep it alive.
      ref.ReadDirectoryEntries(callback_factory_.NewCallbackWithOutput(
            &FileIoUrlLoaderInstance::ListCallback, ref));
    }

    void ListCallback(int32_t result,
        const std::vector<pp::DirectoryEntry>& entries,
        pp::FileRef ) {
      if (result != PP_OK) {
        ShowErrorMessage("List failed", result);
        return;
      }

      StringVector sv;
      for (size_t i = 0; i < entries.size(); ++i) {
        pp::Var name = entries[i].file_ref().GetName();
        if (name.is_string()) {
          sv.push_back(name.AsString());
        }
      }
      PostArrayMessage("LIST", sv);
      ShowStatusMessage("List success");
    }

    void MakeDir(int32_t, const std::string& dir_name) {
      if (!file_system_ready_) {
        ShowErrorMessage("File system is not open", PP_ERROR_FAILED);
        return;
      }
      pp::FileRef ref(file_system_, dir_name.c_str());

      int32_t result = ref.MakeDirectory(
          PP_MAKEDIRECTORYFLAG_NONE, pp::BlockUntilComplete());
      if (result != PP_OK) {
        ShowErrorMessage("Make directory failed", result);
        return;
      }
      ShowStatusMessage("Make directory success");
    }

    void Rename(int32_t,
        const std::string& old_name,
        const std::string& new_name) {
      if (!file_system_ready_) {
        ShowErrorMessage("File system is not open", PP_ERROR_FAILED);
        return;
      }

      pp::FileRef ref_old(file_system_, old_name.c_str());
      pp::FileRef ref_new(file_system_, new_name.c_str());

      int32_t result = ref_old.Rename(ref_new, pp::BlockUntilComplete());
      if (result != PP_OK) {
        ShowErrorMessage("Rename failed", result);
        return;
      }
      ShowStatusMessage("Rename success");
    }
    */

    /// Encapsulates our simple javascript communication protocol
    void ShowErrorMessage(const std::string& message, int32_t result) {
      std::stringstream ss;
      ss << message << " -- Error #: " << result;
      PostArrayMessage("ERR", ss.str());
    }

    void ShowStatusMessage(const std::string& message) {
      PostArrayMessage("STAT", message);
    }
};

/// The Module class.  The browser calls the CreateInstance() method to create
/// an instance of your NaCl module on the web page.  The browser creates a new
/// instance for each <embed> tag with type="application/x-nacl".
class FileIoUrlLoaderModule : public pp::Module {
  public:
    FileIoUrlLoaderModule() : pp::Module() {}
    virtual ~FileIoUrlLoaderModule() {}

    /// Create and return a FileIoInstance object.
    /// @param[in] instance The browser-side instance.
    /// @return the plugin-side instance.
    virtual pp::Instance* CreateInstance(PP_Instance instance) {
      return new FileIoUrlLoaderInstance(instance);
    }
};

namespace pp {
  /// Factory function called by the browser when the module is first loaded.
  /// The browser keeps a singleton of this module.  It calls the
  /// CreateInstance() method on the object you return to make instances.  There
  /// is one instance per <embed> tag on the page.  This is the main binding
  /// point for your NaCl module with the browser.
  Module* CreateModule() { return new FileIoUrlLoaderModule(); }
}  // namespace pp
