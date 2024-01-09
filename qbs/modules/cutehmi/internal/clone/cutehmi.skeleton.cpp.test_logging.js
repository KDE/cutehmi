function process(copiedQbsFiles, copiedAllFiles) {
	for (var allFileIndex in copiedAllFiles) {
		var entry = copiedAllFiles[allFileIndex]
		if (entry["targetRelativePath"] === "tests/test_logging.cpp") {
			var file = new TextFile(entry["targetPath"], TextFile.ReadOnly);
			try {
				var content = file.readAll()
						console.warn(content)
			} finally {
				file.close()
			}

			content = content.replace("\"" + product.cutehmi.clone.oldProject + "\");", "\"" + product.cutehmi.clone.newProject + "\");")

			file = new TextFile(entry["targetPath"], TextFile.WriteOnly);
			try {
				file.write(content)
			} finally {
				file.close()
			}
		}
	}
}
