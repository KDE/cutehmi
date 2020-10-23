#include "../../include/cutehmi/functions.hpp"
#include "../cutehmi.dirs.hpp"

#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>

namespace cutehmi {

QJsonObject metadata(const QString & product)
{
	QString relativePath = QDir("/" CUTEHMI_DIRS_TOOLS_INSTALL_SUBDIR).relativeFilePath("/" CUTEHMI_DIRS_METADATA_INSTALL_SUBDIR);
	QFile file(relativePath + "/" + product + ".metadata.json");
	if (!file.open(QIODevice::ReadOnly)) {
		CUTEHMI_CRITICAL("Could not open '" << file.fileName() << "' file.");
		return QJsonObject();
	}

	return QJsonDocument::fromJson(file.readAll()).object();
}

}
