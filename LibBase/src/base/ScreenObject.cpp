#include "ScreenObject.hpp"

namespace cutehmi {
namespace base {

ScreenObject::ScreenObject(const QString & source, bool def, QObject * parent):
	QObject(parent),
	m_source(source),
	m_default(def)
{
}

QString ScreenObject::source() const
{
	return m_source;
}

void ScreenObject::setSource(const QString & source)
{
	m_source = source;
}

bool ScreenObject::isDefault() const
{
	return m_default;
}

void ScreenObject::setDefault(bool def)
{
	m_default = def;
}

}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
