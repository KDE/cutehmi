#ifndef ENGINETHREAD_HPP
#define ENGINETHREAD_HPP

#include <QThread>

namespace cutehmi {
namespace daemon {

class EngineThread:
	public QThread
{
	Q_OBJECT

	public:
		EngineThread(QObject * parent = nullptr);

	signals:
		void loadRequested(const QString & project);
};

}
}

#endif // ENGINETHREAD_HPP
