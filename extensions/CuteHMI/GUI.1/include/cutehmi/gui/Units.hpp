#ifndef H_EXTENSIONS_CUTEHMI_GUI_1_INCLUDE_CUTEHMI_GUI_UNITS_HPP
#define H_EXTENSIONS_CUTEHMI_GUI_1_INCLUDE_CUTEHMI_GUI_UNITS_HPP

#include "internal/common.hpp"

#include <QObject>
#include <QQmlEngine>

namespace cutehmi {
namespace gui {

/**
 * Unit. This class provides relative units of measurment.
 */
class CUTEHMI_GUI_API Units:
	public QObject
{
		Q_OBJECT
		QML_NAMED_ELEMENT(Units)

	public:
		static constexpr qreal INITIAL_QUADRAT = 80.0;

		static constexpr qreal INITIAL_STROKE_WIDTH_RATIO = 40.0;

		static constexpr bool INITIAL_ROUND_STROKE_WIDTH = true;

		/**
		  Quadrat. Role of this unit is similar to role of @p em unit used in typography. It defines reference size of graphical
		  elements. Quadrat size is measured in pixels although elements being drawn should not refer to underlying unit, but
		  describe their own size as multiples of quadrat.
		  */
		Q_PROPERTY(qreal quadrat READ quadrat WRITE setQuadrat NOTIFY quadratChanged)

		/**
		  Stroke width. By default binded to the formula @a strokeWidth = @a quadrat / @a strokeWidthRatio.
		  */
		Q_PROPERTY(qreal strokeWidth READ strokeWidth WRITE setStrokeWidth NOTIFY strokeWidthChanged)

		/**
		  Stroke width ratio.
		  */
		Q_PROPERTY(qreal strokeWidthRatio READ strokeWidthRatio WRITE setStrokeWidthRatio NOTIFY strokeWidthRatioChanged)

		/**
		  Whether to round stroke width to whole integer.
		  */
		Q_PROPERTY(bool roundStrokeWidth READ roundStrokeWidth WRITE setRoundStrokeWidth NOTIFY roundStrokeWidthChanged)

		Units(QObject * parent = nullptr);

		qreal quadrat() const;

		void setQuadrat(qreal quadrat);

		qreal strokeWidth() const;

		void setStrokeWidth(qreal strokeWidth);

		qreal strokeWidthRatio() const;

		void setStrokeWidthRatio(qreal ratio);

		bool roundStrokeWidth() const;

		void setRoundStrokeWidth(bool roundStrokeWidth);

	signals:
		void quadratChanged();

		void strokeWidthChanged();

		void strokeWidthRatioChanged();

		void roundStrokeWidthChanged();

	private slots:
		void strokeWidthBinding();

	private:
		void setStrokeWidth(qreal strokeWidth, bool breakBinding);

		struct Members {
			qreal quadrat;
			qreal strokeWidth;
			qreal strokeWidthRatio;
			bool roundStrokeWidth;
			QMetaObject::Connection strokeWidthBindingConnection;
			QMetaObject::Connection strokeWidthRatioBindingConnection;
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
