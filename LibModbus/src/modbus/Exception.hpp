#ifndef CUTEHMI_LIBMODBUS_SRC_MODBUS_EXCEPTION_HPP
#define CUTEHMI_LIBMODBUS_SRC_MODBUS_EXCEPTION_HPP

#include "../platform.hpp"

#include <QException>

namespace modbus {

class CUTEHMI_MODBUS_API Exception:
	public QException
{
	public:
		Exception(const QString & what, const QString & details = QString());

		void raise() const override;

		Exception * clone() const override;

		const char * what() const noexcept override;

		const char * details() const noexcept;

		bool hasDetails() const;

	private:
		const QByteArray m_what;
		const QByteArray m_details;
};

}

#endif
