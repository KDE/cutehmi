#include <cutehmi/PopupBridge.hpp>

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
			m_popupBridge.reset(new cutehmi::PopupBridge);
		}

		void qmlEngineAvailable(QQmlEngine * engine)
		{
			engine->rootContext()->setContextProperty("popupBridge", m_popupBridge.get());
		}

		void cleanupTestCase()
		{
		}

	private:
		std::unique_ptr<cutehmi::PopupBridge> m_popupBridge;
};


QUICK_TEST_MAIN_WITH_SETUP(CuteHMI.2, test_QML)
#include "test_QML.moc"

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
