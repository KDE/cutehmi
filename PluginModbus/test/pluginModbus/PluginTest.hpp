#ifndef PLUGINTEST_H
#define PLUGINTEST_H

#include <QtTest>

namespace cutehmi {
namespace pluginModbus {

class Plugin;

class PluginTest:
		public QObject
{
	Q_OBJECT

	private slots:
		void initTestCase();

		void secUsecFromString();
};

}
}

#endif // PLUGINTEST_H
