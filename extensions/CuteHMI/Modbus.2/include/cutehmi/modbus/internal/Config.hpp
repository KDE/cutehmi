#ifndef INCLUDECUTEHMIMODBUSINTERNALCONFIG_HPP
#define INCLUDECUTEHMIMODBUSINTERNALCONFIG_HPP

#include "common.hpp"

namespace cutehmi {
namespace modbus {
namespace internal {

class CUTEHMI_MODBUS_PRIVATE Config:
	public QObject
{
		Q_OBJECT

	public:
		Config(QObject * parent = nullptr);

	signals:
		void configChanged();
};

}
}
}

#endif // INCLUDECUTEHMIMODBUSINTERNALCONFIG_HPP
