#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_REGISTER1_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_REGISTER1_HPP

#include "internal/common.hpp"

#include <QAtomicInteger>

namespace cutehmi {
namespace modbus {

/**
 * Cached properties of 1 bit register.
 */
class CUTEHMI_MODBUS_API Register1
{
	public:
		/**
		 * Constructor.
		 * @param value initial value.
		 */
		explicit Register1(bool value = false);

		bool value() const;

		void rest();

		void awake();

		bool wakeful() const;

	protected:
		void setValue(bool value);

	private:
		struct Members
		{
			QAtomicInteger<quint16> value;
			QAtomicInt awaken;
		};

		MPtr<Members> m;
};

}
}

#endif
