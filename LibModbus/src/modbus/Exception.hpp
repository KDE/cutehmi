#ifndef CUTEHMI_LIBMODBUS_SRC_MODBUS_EXCEPTION_HPP
#define CUTEHMI_LIBMODBUS_SRC_MODBUS_EXCEPTION_HPP

#include "../platform.hpp"

#include <QException>

namespace cutehmi {
namespace modbus {

class CUTEHMI_MODBUS_API Exception:
	public QException
{
	public:
		Exception(const QString & what);

		void raise() const override;

		Exception * clone() const override;

		const char * what() const noexcept override;

	private:
		const QByteArray m_what;
};

}
}

#endif
