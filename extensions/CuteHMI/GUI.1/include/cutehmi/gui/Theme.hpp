#ifndef H_EXTENSIONS_CUTEHMI_GUI_0_INCLUDE_CUTEHMI_GUI_THEME_HPP
#define H_EXTENSIONS_CUTEHMI_GUI_0_INCLUDE_CUTEHMI_GUI_THEME_HPP

#include "internal/common.hpp"
#include "Palette.hpp"
#include "Units.hpp"
#include "Fonts.hpp"

#include <cutehmi/Singleton.hpp>

#include <QObject>

namespace cutehmi {
namespace gui {

/**
 * %Theme.
 *
 * %Theme defines palette, units and fonts.
 */
class CUTEHMI_GUI_API Theme:
	public QObject,
	public Singleton<Theme>
{
		Q_OBJECT

		friend class Singleton<Theme>;

	public:
		Q_PROPERTY(Palette * palette READ palette WRITE setPalette NOTIFY paletteChanged RESET resetPalette)

		Q_PROPERTY(Units * units READ units WRITE setUnits NOTIFY unitsChanged RESET resetUnits)

		Q_PROPERTY(Fonts * fonts READ fonts WRITE setFonts NOTIFY fontsChanged RESET resetFonts)

		Palette * palette() const;

		void setPalette(Palette * palette);

		void resetPalette();

		Units * units() const;

		void setUnits(Units * units);

		void resetUnits();

		Fonts * fonts() const;

		void setFonts(Fonts * fonts);

		void resetFonts();

	signals:
		void paletteChanged();

		void unitsChanged();

		void fontsChanged();

	protected:
		Theme(QObject * parent = nullptr);

		static Palette & DefaultPalette();

		static Units & DefaultUnits();

		static Fonts & DefaultFonts();

	private:
		void establishFontBindings();

		struct Members
		{
			Palette * palette;
			Units * units;
			Fonts * fonts;

			Members():
				palette(& DefaultPalette()),
				units(& DefaultUnits()),
				fonts(& DefaultFonts())
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
