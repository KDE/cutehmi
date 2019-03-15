#include <cutehmi/Dialogist.hpp>

#include <QtQuickTest>
#include <QQmlEngine>
#include <QQmlContext>

class test_QML:
	public QObject
{
	Q_OBJECT

	public slots:
		void applicationAvailable()
		{
		}

		void qmlEngineAvailable(QQmlEngine * engine)
		{
			engine->rootContext()->setContextProperty("dialogist", & cutehmi::Dialogist::Instance());
		}

		void cleanupTestCase()
		{
		}
};


QUICK_TEST_MAIN_WITH_SETUP(CuteHMI.2, test_QML)
#include "test_QML.moc"

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
