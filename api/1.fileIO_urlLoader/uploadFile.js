function handleFileSelect(evt) {
  var files = evt.target.files;
  var output = [];
  for (var i = 0, f ; i < files.length ; i ++) {
    f = files[i];
    output.push('<li><strong>', escape(f.name), '</strong> (', f.type || 'n/a', ') - ',
        f.size, ' bytes, last modifed: ',
        f.lastModifiedDate ?
        f.lastModifiedDate.toLocaleDateString() : 'n/a',
        '</li>');

    var reader = new FileReader();
    reader.onload = (function(f) {
      return function(e) {
        if (common.naclModule) {
          var arrayBuffer = e.target.result;
          var uint8Array = new Uint8Array(arrayBuffer);
          var array = Array.prototype.slice.call(uint8Array);
          common.logMessage("SENT");
          common.naclModule.postMessage(array);
        }
      };
    })(f);
    reader.readAsArrayBuffer(f);
  }
  document.getElementById('filelist').innerHTML = '<ul>' + output.join('') + '</ul>';
}
document.getElementById('files').addEventListener('change', handleFileSelect, false);
