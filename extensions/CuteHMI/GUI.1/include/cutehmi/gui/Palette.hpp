#ifndef H_EXTENSIONS_CUTEHMI_GUI_1_INCLUDE_CUTEHMI_GUI_PALETTE_HPP
#define H_EXTENSIONS_CUTEHMI_GUI_1_INCLUDE_CUTEHMI_GUI_PALETTE_HPP

#include "internal/common.hpp"
#include "ColorSet.hpp"

#include <QObject>

namespace cutehmi {
namespace gui {

/**
 * %Palette.
 *
 * %Palette defines standard color sets to be used by various user interface items. For example @ref Element "elements" are using
 * color codes to signal specific states of an equipment, such as "active", warning", "alarm" or "inactive". For each such state a
 * separate ColorSet is prvided by Palette object.
 */
class CUTEHMI_GUI_API Palette:
	public QObject
{
		Q_OBJECT

	public:
		/**
		  Background color.
		  */
		Q_PROPERTY(QColor background READ background WRITE setBackground NOTIFY backgroundChanged)

		/**
		  Alarm items color set.
		  */
		Q_PROPERTY(cutehmi::gui::ColorSet * alarm READ alarm WRITE setAlarm NOTIFY alarmChanged RESET resetAlarm)

		/**
		  Warning items color set.
		  */
		Q_PROPERTY(cutehmi::gui::ColorSet * warning READ warning WRITE setWarning NOTIFY warningChanged RESET resetWarning)

		/**
		  Active items color set.
		  */
		Q_PROPERTY(cutehmi::gui::ColorSet * active READ active WRITE setActive NOTIFY activeChanged RESET resetActive)

		/**
		  Inactive items color set.
		  */
		Q_PROPERTY(cutehmi::gui::ColorSet * inactive READ inactive WRITE setInactive NOTIFY inactiveChanged RESET resetInactive)

		/**
		  Neutral color set. Neutral color set is for items that do not distinguish between active and inactive states.
		  */
		Q_PROPERTY(cutehmi::gui::ColorSet  * neutral READ neutral WRITE setNeutral NOTIFY neutralChanged RESET resetNeutral)

		Palette(QObject * parent = nullptr);

		QColor background() const;

		void setBackground(QColor background);

		ColorSet * alarm() const;

		void setAlarm(ColorSet * alarm);

		void resetAlarm();

		ColorSet * warning() const;

		void setWarning(ColorSet * warning);

		void resetWarning();

		ColorSet * active() const;

		void setActive(ColorSet * active);

		void resetActive();

		ColorSet * inactive() const;

		void setInactive(ColorSet * inactive);

		void resetInactive();

		ColorSet * neutral() const;

		void setNeutral(ColorSet * neutral);

		void resetNeutral();

	signals:
		void backgroundChanged();

		void alarmChanged();

		void warningChanged();

		void activeChanged();

		void inactiveChanged();

		void neutralChanged();

	protected:
		static ColorSet & DefaultAlarm();

		static ColorSet & DefaultWarning();

		static ColorSet & DefaultActive();

		static ColorSet & DefaultInactive();

		static ColorSet & DefaultNeutral();

	private:
		static constexpr Qt::GlobalColor INITIAL_BACKGROUND = Qt::white;

		struct Members
		{
			QColor background;
			ColorSet * alarm;
			ColorSet * warning;
			ColorSet * active;
			ColorSet * inactive;
			ColorSet * neutral;

			Members():
				background(INITIAL_BACKGROUND),
				alarm(& DefaultAlarm()),
				warning(& DefaultWarning()),
				active(& DefaultActive()),
				inactive(& DefaultInactive()),
				neutral(& DefaultNeutral())
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)C: Copyright © 2020-2021, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
