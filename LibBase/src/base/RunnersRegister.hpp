#ifndef CUTEHMI_LIBBASE_SRC_BASE_RUNNERSREGISTER_HPP
#define CUTEHMI_LIBBASE_SRC_BASE_RUNNERSREGISTER_HPP

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

#endif
