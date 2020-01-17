#ifndef H_EXTENSIONS_CUTEHMI_GUI_0_INCLUDE_CUTEHMI_GUI_THEME_HPP
#define H_EXTENSIONS_CUTEHMI_GUI_0_INCLUDE_CUTEHMI_GUI_THEME_HPP

#include "internal/common.hpp"
#include "Palette.hpp"

#include <QObject>

namespace cutehmi {
namespace gui {

/**
 * %Theme.
 *
 * %Theme defines palette used by CuteApplication. In future it may also cover other aspects of user interface appearance.
 */
class CUTEHMI_GUI_API Theme:
	public QObject
{
		Q_OBJECT

	public:
		Q_PROPERTY(Palette * palette READ palette WRITE setPalette NOTIFY paletteChanged RESET resetPalette)

		Theme(QObject * parent = nullptr);

		Palette * palette() const;

		void setPalette(Palette * palette);

		void resetPalette();

	signals:
		void alarmChanged();

		void paletteChanged();

	protected:
		static Palette & DefaultPalette();

	private:
		struct Members
		{
			Palette * palette;

			Members():
				palette(& DefaultPalette())
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
