#include <cutehmi/gpio/ChipEnumerator.hpp>

#include <gpiod.h>

template class cutehmi::Singleton<cutehmi::gpio::ChipEnumerator>;

namespace cutehmi {
namespace gpio {

void ChipEnumerator::update()
{
	::gpiod_chip_iter * iter = ::gpiod_chip_iter_new();
	::gpiod_chip * chip = gpiod_chip_iter_next(iter);
	while (chip != nullptr) {
		CUTEHMI_WARNING("Name: " << ::gpiod_chip_name(chip));
		CUTEHMI_WARNING("Label: " << ::gpiod_chip_label(chip));
		CUTEHMI_WARNING("Num lines: " << ::gpiod_chip_num_lines(chip));
		chip = gpiod_chip_iter_next(iter);
	}
	::gpiod_chip_iter_free(iter);
}

ChipEnumerator::ChipEnumerator()
{
}

}
}

//(c)C: Copyright © 2019, Mr CuteBOT <michpolicht@gmail.com>, CuteBOT <michpolicht@gmail.com>, Michal Policht <michpolicht@gmail.com>, Michal Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
