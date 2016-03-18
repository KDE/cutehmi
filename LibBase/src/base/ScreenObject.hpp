#ifndef CUTEHMI_LIBBASE_SRC_BASE_SCREENOBJECT_HPP
#define CUTEHMI_LIBBASE_SRC_BASE_SCREENOBJECT_HPP

#include "../platform.hpp"

#include <QObject>

namespace cutehmi {
namespace base {

class CUTEHMI_BASE_API ScreenObject:
	public QObject
{
	Q_OBJECT

	public:
		ScreenObject(const QString & source, bool def = false, QObject * parent = 0);

		virtual ~ScreenObject() = default;

		QString source() const;

		void setSource(const QString & source);

		bool isDefault() const;

		void setDefault(bool def);

	private:
		QString m_source;
		bool m_default;
};

}
}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
