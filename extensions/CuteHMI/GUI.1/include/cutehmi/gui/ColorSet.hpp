#ifndef H_EXTENSIONS_CUTEHMI_GUI_1_INCLUDE_CUTEHMI_GUI_COLORSET_HPP
#define H_EXTENSIONS_CUTEHMI_GUI_1_INCLUDE_CUTEHMI_GUI_COLORSET_HPP

#include "internal/common.hpp"

#include <QObject>
#include <QColor>

namespace cutehmi {
namespace gui {

/**
 * Color set. Color set defines standard colors to be used by @ref Element "elements" and possibly other items.
 */
class CUTEHMI_GUI_API ColorSet:
	public QObject
{
		Q_OBJECT

	public:
		/**
		  Base color of a set. It can be used to display single-color elements over the Palette's main background (such as text).
		  As such it should be contrasting with Palette's background.
		  */
		Q_PROPERTY(QColor base READ base WRITE setBase NOTIFY baseChanged)

		/**
		  Fill color. As name suggests it can be used by components to fill their interiors. Fill color works together with stroke color.
		  Component must have a stroke contour if it uses fill color to fill its interior.
		  Either a stroke color or a fill color should be a variation of base color in order to make color set meaningful.
		  */
		Q_PROPERTY(QColor fill READ fill WRITE setFill NOTIFY fillChanged)

		/**
		  A lighter variation of fill color. It can be used to draw details of a component.
		  */
		Q_PROPERTY(QColor tint READ tint WRITE setTint NOTIFY tintChanged)

		/**
		  A darker variation of fill color. It can be used to draw details of a component.
		  */
		Q_PROPERTY(QColor shade READ shade WRITE setShade NOTIFY shadeChanged)

		/**
		  Background color. Some components may want to display a text or symbols over them. Such components shall use
		  background color to create uniform background and a contrasting foreground color to display text/symbols. Foreground
		  and background colors work in pairs; in one theme background color is a dull variation of base color, while
		  foreground color remains the same across color sets, but the other theme may choose to make foreground color
		  a variation of base color and to keep background the same.
		  */
		Q_PROPERTY(QColor background READ background WRITE setBackground NOTIFY backgroundChanged)

		/**
		  Foreground color. Some components may want to display a text or symbols over them. Such components shall use
		  background color to create uniform background and a contrasting foreground color to display text/symbols. Foreground
		  and background colors work in pairs; in one theme background color is a dull variation of base color, while
		  foreground color remains the same across color sets, but the other theme may choose to make foreground color
		  a variation of base color and keep background the same across multiple sets.
		  */
		Q_PROPERTY(QColor foreground READ foreground WRITE setForeground NOTIFY foregroundChanged)

		/**
		  Strokes. A color of contours. Stroke color should be contrasting with Palette's main background. Stroke color works together
		  with fill color. Component must have a stroke contour if it uses fill color to fill its interior.
		  Either a stroke color or a fill color should be a variation of base color in order to make color set meaningful.
		  */
		Q_PROPERTY(QColor stroke READ stroke WRITE setStroke NOTIFY strokeChanged)

		/**
		  Blank color. Sometimes component has to draw empty areas within itself. Blank color shall be used to fill such areas. It
		  is typically the same color as palette background, but it may also be transparent.
		  */
		Q_PROPERTY(QColor blank READ blank WRITE setBlank NOTIFY blankChanged)

		/**
		 * Constructor.
		 * @param parent parent object.
		 */
		ColorSet(QObject * parent = nullptr);

		/**
		 * Get base color.
		 * @return base color.
		 */
		QColor base() const;

		/**
		 * Set base color.
		 * @param base base color.
		 */
		void setBase(QColor base);

		/**
		 * Get fill color.
		 * @return fill color.
		 */
		QColor fill() const;

		/**
		 * Set fill color.
		 * @param base fill color.
		 */
		void setFill(QColor fill);

		/**
		 * Get tint color.
		 * @return tint color.
		 */
		QColor tint() const;

		/**
		 * Set tint color.
		 * @param tint tint color.
		 */
		void setTint(QColor tint);

		/**
		 * Get shade color.
		 * @return shade color.
		 */
		QColor shade() const;

		/**
		 * Set shade color.
		 * @param shade color.
		 */
		void setShade(QColor shade);

		/**
		 * Get background color.
		 * @return background color.
		 */
		QColor background() const;

		/**
		 * Set background color.
		 * @param background background color.
		 */
		void setBackground(QColor background);

		/**
		 * Get foreground color.
		 * @return foreground color.
		 */
		QColor foreground() const;

		/**
		 * Set foreground color.
		 * @param foreground foreground color.
		 */
		void setForeground(QColor foreground);

		/**
		 * Get stroke color.
		 * @return stroke color.
		 */
		QColor stroke() const;

		/**
		 * Set stroke color.
		 * @param stroke stroke color.
		 */
		void setStroke(QColor stroke);

		/**
		 * Get blank color.
		 * @return blank color.
		 */
		QColor blank() const;

		/**
		 * Set blank color.
		 * @param blank blank color.
		 */
		void setBlank(QColor blank);

	signals:
		/**
		 * This signal is emitted whenever base color has changed.
		 */
		void baseChanged();

		/**
		 * This signal is emitted whenever fill color has changed.
		 */
		void fillChanged();

		/**
		 * This signal is emitted whenever tint color has changed.
		 */
		void tintChanged();

		/**
		 * This signal is emitted whenever shade color has changed.
		 */
		void shadeChanged();

		/**
		 * This signal is emitted whenever background color has changed.
		 */
		void backgroundChanged();

		/**
		 * This signal is emitted whenever foreground color has changed.
		 */
		void foregroundChanged();

		/**
		 * This signal is emitted whenever stroke color has changed.
		 */
		void strokeChanged();

		/**
		 * This signal is emitted whenever blank color has changed.
		 */
		void blankChanged();

	private:
		struct Members
		{
			QColor base;
			QColor fill;
			QColor tint;
			QColor shade;
			QColor background;
			QColor foreground;
			QColor stroke;
			QColor blank;
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
