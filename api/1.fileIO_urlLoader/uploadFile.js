function handleFileSelect(evt) {
	var files = evt.target.files;
	var output = [];
	var reader = new FileReader();
	for (var i = 0, f ; f = files[i] ; i ++) {
		output.push('<li><strong>', escape(f.name), '</strong> (', f.type || 'n/a', ') - ',
				f.size, ' bytes, last modifed: ',
				f.lastModifiedDate ?
				f.lastModifiedDate.toLocaleDateString() : 'n/a',
				'</li>');

		reader.onload = function(e) {
			var arrayBuffer = reader.result;
			var uint8Array = new Uint8Array(arrayBuffer);
			var array = Array.prototype.slice.call(uint8Array);
			common.naclModule.postMessage(array);
		}
		reader.readAsArrayBuffer(f);
	}
	document.getElementById('filelist').innerHTML = '<ul>' + output.join('') + '</ul>';
}
document.getElementById('files').addEventListener('change', handleFileSelect, false);
