#ifndef H_EXTENSIONS_CUTEHMI_GUI_1_INCLUDE_CUTEHMI_GUI_FONTS_HPP
#define H_EXTENSIONS_CUTEHMI_GUI_1_INCLUDE_CUTEHMI_GUI_FONTS_HPP

#include "internal/common.hpp"

#include <QObject>
#include <QFont>

namespace cutehmi {
namespace gui {

class CUTEHMI_GUI_API Fonts:
	public QObject
{
		Q_OBJECT

	public:
		Q_PROPERTY(QFont monospace READ monospace WRITE setMonospace NOTIFY monospaceChanged RESET resetMonospace)

		Fonts(QObject * parent = nullptr);

		QFont monospace() const;

		void setMonospace(QFont monospace);

		void resetMonospace();

	signals:
		void monospaceChanged();

	protected:
		QFont & DefaultMonospace();

	private:
		struct Members {
			QFont monospace;
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
