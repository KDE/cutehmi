#ifndef THREADREGISTER_H
#define THREADREGISTER_H

#include "../platform.hpp"

#include <QList>
#include <QObject>

namespace cutehmi {
namespace base {

class IRunner;

class CUTEHMI_BASE_API RunnersRegister:
	public QObject
{
	Q_OBJECT

	public:
		void add(IRunner * runner);

		void clear();

	public slots:
		void start();

		void stop();

	private:
		typedef QList<IRunner *> RunnersContainer;

		RunnersContainer m_runners;
};

}
}

#endif // THREADREGISTER_H
