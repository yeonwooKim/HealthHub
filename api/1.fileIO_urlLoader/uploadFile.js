function handleFileSelect(evt) {
	var files = evt.target.files;
	var output = [];
	for (var i = 0, f ; f = files[i] ; i ++) {
		output.push('<li><strong>', escape(f.name), '</strong> (', f.type || 'n/a', ') - ',
				f.size, ' bytes, last modifed: ',
				f.lastModifiedDate ?
				f.lastModifiedDate.toLocaleDateString() : 'n/a',
				'</li>');
	}
	document.getElementById('list').innerHTML = '<ul>' + output.join('') + '</ul>';
}
document.getElementById('files').addEventListener('change', handleFileSelect, false);
