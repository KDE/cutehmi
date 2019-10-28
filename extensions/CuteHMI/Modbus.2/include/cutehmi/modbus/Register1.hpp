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

//(c)C: Copyright © 2019, . All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
