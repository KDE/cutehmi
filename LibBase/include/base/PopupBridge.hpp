#ifndef CUTEHMI_LIBBASE_INCLUDE_BASE_POPUPBRIDGE_HPP
#define CUTEHMI_LIBBASE_INCLUDE_BASE_POPUPBRIDGE_HPP

#include "internal/common.hpp"
#include "Prompt.hpp"

#include <QObject>
#include <QMutexLocker>

namespace cutehmi {
namespace base {

class CUTEHMI_BASE_API PopupBridge:
	public QObject
{
	Q_OBJECT

	public:
		explicit PopupBridge(QObject * parent = 0);

		~PopupBridge() override = default;

		Q_INVOKABLE void advertise(Prompt * prompt);

		Q_INVOKABLE void resetAdvertiser(QObject * advertiser);

	signals:
		void promptRequested(QVariant);

	private:
		struct Members
		{
			QMutex requestMutex {};
			QObject * advertiser {nullptr};
		};

		utils::MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
