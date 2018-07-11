#include "../../../include/cutehmi/xml/conversions.hpp"

#include <QString>
#include <QUuid>
#include <QRegExp>

namespace cutehmi {
namespace xml {

static uint randPort()
{
	static uint port = qHash(QUuid::createUuid());
	return port;
}

QString portToString(uint port, bool random)
{
	if (random)
		return QString::number(port);
	else
		return QString("randPlus(") + QString::number(port) + ")";
}

uint portFromString(const QString & string, bool & ok)
{
	constexpr uint PORT_BEGIN = CUTEHMI_XML_RANDOM_PORT_BEGIN;
	constexpr uint PORT_END = CUTEHMI_XML_RANDOM_PORT_END;

	qDebug() << "string: " << string;
	QRegExp test("^\\s*randPlus\\(([0-9]*\\))\\s*$");
	qDebug() << "exactMatch: " << test.exactMatch(string);

	QRegExp randPlus("^\\s*randPlus\\(([0-9]*)\\)\\s*$");
	if (randPlus.exactMatch(string)) {
		uint plusPort = randPlus.cap(1).toUInt(& ok);
		qDebug() << "CAP : " << randPlus.cap(1);	//temp
		qDebug() << "return: " << PORT_BEGIN + ((randPort() + plusPort) % (PORT_END - PORT_BEGIN + 1)); // temp
		if (ok)
			return PORT_BEGIN + ((randPort() + plusPort) % (PORT_END - PORT_BEGIN + 1));
	}
	return string.toUInt(& ok);
}

}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
