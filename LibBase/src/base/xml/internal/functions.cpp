#include "../../../../include/base/xml/internal/functions.hpp"

#include <QXmlStreamReader>

namespace cutehmi {
namespace base {
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
	return QString::fromUtf8(line.trimmed()) + " (" + positionString + ")";
}

}
}
}
}
