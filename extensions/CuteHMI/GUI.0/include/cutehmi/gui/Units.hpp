#ifndef H_EXTENSIONS_CUTEHMI_GUI_0_INCLUDE_CUTEHMI_GUI_UNITS_HPP
#define H_EXTENSIONS_CUTEHMI_GUI_0_INCLUDE_CUTEHMI_GUI_UNITS_HPP

#include "internal/common.hpp"

#include <QObject>

namespace cutehmi {
namespace gui {

class CUTEHMI_GUI_API Units:
	public QObject
{
		Q_OBJECT

	public:
		static constexpr qreal INITIAL_QUADRAT = 80.0;

		static constexpr bool INITIAL_ROUND_STROKE_WIDTH = true;

		static constexpr qreal STANDARD_STROKE_WIDTH_QUADRAT_RATIO = 40.0;

		Q_PROPERTY(qreal quadrat READ quadrat WRITE setQuadrat NOTIFY quadratChanged)

		Q_PROPERTY(qreal strokeWidth READ strokeWidth WRITE setStrokeWidth NOTIFY strokeWidthChanged)

		Q_PROPERTY(bool roundStrokeWidth READ roundStrokeWidth WRITE setRoundStrokeWidth NOTIFY roundStrokeWidthChanged)

		Units(QObject * parent = nullptr);

		qreal quadrat() const;

		void setQuadrat(qreal quadrat);

		qreal strokeWidth() const;

		void setStrokeWidth(qreal strokeWidth);

		bool roundStrokeWidth() const;

		void setRoundStrokeWidth(bool roundStrokeWidth);

	signals:
		void quadratChanged();

		void strokeWidthChanged();

		void roundStrokeWidthChanged();

	private slots:
		void strokeWidthBinding();

	private:
		void setStrokeWidth(qreal strokeWidth, bool breakBinding);

		struct Members {
			qreal quadrat;
			qreal strokeWidth;
			bool roundStrokeWidth;
			QMetaObject::Connection strokeWidthBindingConnection;
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
