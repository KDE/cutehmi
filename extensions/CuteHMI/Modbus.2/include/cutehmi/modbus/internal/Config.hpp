#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_CONFIG_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_CONFIG_HPP

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

#endif
