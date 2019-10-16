#ifndef INCLUDECUTEHMIMODBUSREGISTER16_HPP
#define INCLUDECUTEHMIMODBUSREGISTER16_HPP

#include "internal/common.hpp"

#include <QAtomicInteger>

namespace cutehmi {
namespace modbus {

/**
 * Cached properties of 16 bit register.
 */
class CUTEHMI_MODBUS_API Register16
{
	public:
		/**
		 * Constructor.
		 * @param value initial value.
		 */
		explicit Register16(quint16 value = 0);

		quint16 value() const;

		void rest();

		void awake();

		bool wakeful() const;

	protected:
		void setValue(quint16 value);

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

#endif // INCLUDECUTEHMIMODBUSINTERNALREGISTER16_HPP
