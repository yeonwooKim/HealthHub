// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

function moduleDidLoad() {
}

// Called by the common.js module.
function domContentLoaded(name, tc, config, width, height) {
  navigator.webkitPersistentStorage.requestQuota(5 * 1024 * 1024,
      function(bytes) {
        common.updateStatus(
          'Allocated ' + bytes + ' bytes of persistant storage.');
        common.attachDefaultListeners();
        common.createNaClModule(name, tc, config, width, height);
      },
      function(e) { alert('Failed to allocate space') });
}

// Called by the common.js module.
function attachListeners() {
  function addEventListenerToButton(parentId, func) {
    document.querySelector('#' + parentId + ' button')
      .addEventListener('click', func);
  }

  addEventListenerToButton('loadFile', loadFile);
  addEventListenerToButton('makeDir', makeDir);
  addEventListenerToButton('loadURL', loadUrl);
  addEventListenerToButton('delete', deleteFileOrDirectory);
  addEventListenerToButton('listDir', listDir);
}

function loadUrl() {
  if (common.naclModule) {
    var fileName = document.querySelector('#loadURL input').value;
    common.naclModule.postMessage(['URLLOADER','getUrl:6.bmp', fileName]);
  }
}

function makeMessage(command, path) {
  // Package a message using a simple protocol containing:
  // [command, <path>, <extra args>...]
  var msg = ['FILEIO',command, path];
  for (var i = 3; i < arguments.length; ++i) {
    msg.push(arguments[i]);
  }
  return msg;
}

function saveFile(fileName, fileData) {
  if (common.naclModule)
    common.naclModule.postMessage(makeMessage('save', fileName, fileData));
}

function loadFile() {
  if (common.naclModule) {
    var dirname = document.querySelector('#loadFile input').value;
    common.naclModule.postMessage(makeMessage('load', dirname));
  }
}

function deleteFileOrDirectory() {
  if (common.naclModule) {
    var fileName = document.querySelector('#delete input').value;
    common.naclModule.postMessage(makeMessage('delete', fileName));
  }
}

function listDir() {
  if (common.naclModule) {
    var dirName = document.querySelector('#listDir input').value;
    common.naclModule.postMessage(makeMessage('list', dirName));
  }
}

function makeDir() {
  if (common.naclModule) {
    var dirName = document.querySelector('#makeDir input').value;
    common.naclModule.postMessage(makeMessage('makedir', dirName));
  }
}

/*
   function rename() {
   if (common.naclModule) {
   var oldName = document.querySelector('#renameOld').value;
   var newName = document.querySelector('#renameNew').value;
   common.naclModule.postMessage(makeMessage('rename', oldName, newName));
   }
   }
 */

// Called by the common.js module.
function handleMessage(message_event) {
  var fromFile = 'FILEIO';
  var fromUrl = 'URLLOADER';
  var fromGraphics = 'GRAPHICS';
  var rawMsg = message_event.data;
  // Parse the raw message to prefix and message
  // depending on the prefix, decide whether the message is from fileIO or urlLoader
  var prefix = rawMsg[0];
  var msg = rawMsg.slice(1);

  if (prefix == fromFile) {
    var command = msg[0];
    var args = msg.slice(1);

    if (command == 'ERR') {
      common.logMessage('Error: ' + args[0]);
    } else if (command == 'STAT') {
      common.logMessage(args[0]);
    } else if (command == 'READY') {
      common.logMessage('Filesystem ready!');
    } else if (command == 'DISP') {
      // Find the file editor that is currently visible.
      var fileEditorEl =
        document.querySelector('.function:not([hidden]) > textarea');
      // Rejoin args with pipe (|) -- there is only one argument, and it can
      // contain the pipe character.
      fileEditorEl.value = args.join('|');
    } else if (command == 'LIST') {
      var listDirOutputEl = document.getElementById('listDirOutput');

      // TODO
      // NOTE: files with | in their names will be incorrectly split. Fixing this
      // is left as an exercise for the reader.

      // Remove all children of this element...
      while (listDirOutputEl.firstChild) {
        listDirOutputEl.removeChild(listDirOutputEl.firstChild);
      }

      if (args.length) {
        // Add new <li> elements for each file.
        for (var i = 0; i < args.length; ++i) {
          var itemEl = document.createElement('li');
          itemEl.textContent = args[i];
          listDirOutputEl.appendChild(itemEl);
        }
      } else {
        var itemEl = document.createElement('li');
        itemEl.textContent = '<empty directory>';
        listDirOutputEl.appendChild(itemEl);
      }
    }
  }

  else if (prefix == fromUrl) {
    // Find the first line break.  This separates the URL data from the
    // result text.  Note that the result text can contain any number of
    // '\n' characters, so split() won't work here.
    var url = msg[0];
    var result = '';
    var eolPos = msg[0].indexOf('\n');
    if (eolPos != -1) {
      url = msg[0].substring(0, eolPos);
      if (eolPos < msg[0].length - 1) {
        result = msg[0].substring(eolPos + 1);
      }
      common.naclModule.postMessage(['FILEIO', 'save', '/' + url, result]);
      common.logMessage(url);
      //common.logMessage(result);
    }
  }

  else if (prefix == fromGraphics) {
    var command = msg[0];
    var args = msg.slice(1);
   
    if (command == 'WH') {
      var width = args[0];
      var height = args[1];
      common.naclModule.width = width;
      common.naclModule.height = height;
    }
  }
}
