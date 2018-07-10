#include "../../../../include/cutehmi/xml/internal/functions.hpp"

#include <QXmlStreamReader>

namespace cutehmi {
namespace xml {
namespace internal {

QString readerPositionString(const QXmlStreamReader & xmlReader)
{
	QString positionString = QString::number(xmlReader.lineNumber()) + ":" + QString::number(xmlReader.columnNumber() + 1);
	if (!xmlReader.device())
		return positionString;
	qint64 savePos = xmlReader.device()->pos();
	xmlReader.device()->seek(xmlReader.characterOffset() - xmlReader.columnNumber());
	QByteArray line = xmlReader.device()->readLine();
	xmlReader.device()->seek(savePos);
	return QString("'") + QString::fromUtf8(line.trimmed()) + "' (" + positionString + ")";
}

}
}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
