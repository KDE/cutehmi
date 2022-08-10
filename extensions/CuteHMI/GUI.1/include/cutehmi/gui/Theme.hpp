#ifndef H_EXTENSIONS_CUTEHMI_GUI_1_INCLUDE_CUTEHMI_GUI_THEME_HPP
#define H_EXTENSIONS_CUTEHMI_GUI_1_INCLUDE_CUTEHMI_GUI_THEME_HPP

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
		//<CuteHMI.Workarounds.Qt5Compatibility-4.workaround target="Qt" cause="Qt5.15-QML_SINGLETON">
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
		QML_NAMED_ELEMENT(Theme)
		QML_UNCREATABLE("Theme is a singleton")
		QML_SINGLETON
#endif
		//</CuteHMI.Workarounds.Qt5Compatibility-4.workaround>

		friend class Singleton<Theme>;

	public:
		Q_PROPERTY(cutehmi::gui::Palette * palette READ palette WRITE setPalette NOTIFY paletteChanged RESET resetPalette)

		Q_PROPERTY(cutehmi::gui::Units * units READ units WRITE setUnits NOTIFY unitsChanged RESET resetUnits)

		Q_PROPERTY(cutehmi::gui::Fonts * fonts READ fonts WRITE setFonts NOTIFY fontsChanged RESET resetFonts)

		/**
		 * Create intance.
		 * @param qmlEngine QML engine instance.
		 * @param jsEngine JavaScript engine instance.
		 * @return instance.
		 *
		 * @note this method is used by QQmlEngine when class is annotated with QML_SINGLETON macro.
		 */
		static Theme * create(QQmlEngine * qmlEngine, QJSEngine * jsEngine);

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

//(c)C: Copyright © 2020-2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
