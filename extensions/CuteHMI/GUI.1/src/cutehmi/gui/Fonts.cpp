#include <cutehmi/gui/Fonts.hpp>

#include <QFontDatabase>

namespace cutehmi {
namespace gui {

Fonts::Fonts(QObject * parent):
	QObject(parent),
	m(new Members{DefaultMonospace()})
{
}

QFont Fonts::monospace() const
{
	return m->monospace;
}

void Fonts::setMonospace(QFont monospace)
{
	if (m->monospace != monospace) {
		m->monospace = monospace;
		emit monospaceChanged();
	}
}

void Fonts::resetMonospace()
{
	m->monospace = DefaultMonospace();
}

QFont & Fonts::DefaultMonospace()
{
	static QFont monospace;

	//<CuteHMI.GUI-2.workaround target="Qt" cause="bug">
	// Look for available monospace family manually.
	QFontDatabase fontDatabase;
	QStringList availableFamilies = fontDatabase.families();
	QStringList monospaceFamilies({"Droid Sans Mono",
					"Lucida Console",
					"Ubuntu Mono",
					"Liberation Mono",
					"Courier New"});
	QString monospaceFamily;
	for (auto it = monospaceFamilies.begin(); it != monospaceFamilies.end(); ++it)
		if (availableFamilies.contains(*it)) {
			monospaceFamily = *it;
			break;
		}
	//</CuteHMI.GUI-2.workaround>

	if (!monospaceFamily.isNull())
		monospace.setFamily(monospaceFamily);

	return monospace;
}

}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
