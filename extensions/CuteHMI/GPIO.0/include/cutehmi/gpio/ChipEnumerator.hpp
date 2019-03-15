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

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
