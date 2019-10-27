#ifndef H_EXTENSIONS_CUTEHMI_GPIO_0_INCLUDE_CUTEHMI_GPIO_CHIPENUMERATOR_HPP
#define H_EXTENSIONS_CUTEHMI_GPIO_0_INCLUDE_CUTEHMI_GPIO_CHIPENUMERATOR_HPP

#include "internal/common.hpp"

#include <cutehmi/Singleton.hpp>

#include <QObject>

namespace cutehmi {
namespace gpio {

class CUTEHMI_GPIO_API ChipEnumerator:
	public QObject,
	public Singleton<ChipEnumerator>
{
	Q_OBJECT

	friend class Singleton<ChipEnumerator>;

	public slots:
		void update();

	private:
		ChipEnumerator();
};

}
}

extern template class cutehmi::Singleton<cutehmi::gpio::ChipEnumerator>;

#endif

//(c)C: Copyright © 2019, CuteBOT <michpolicht@gmail.com>, Michal Policht <michal@policht.pl>, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
