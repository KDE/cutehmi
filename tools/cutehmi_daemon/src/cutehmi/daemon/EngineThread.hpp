#ifndef ENGINETHREAD_HPP
#define ENGINETHREAD_HPP

#include <QThread>
#include <QQmlApplicationEngine>

#include <memory>

namespace cutehmi {
namespace daemon {

class EngineThread:
	public QThread
{
	Q_OBJECT

	public:
		EngineThread(QObject * parent = nullptr);

	signals:
		void triggerLoad(const QString & project);
};

}
}

#endif // ENGINETHREAD_HPP
