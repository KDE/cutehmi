#include <cutehmi/InplaceError.hpp>

namespace cutehmi {

InplaceError::InplaceError(const QString & p_message, const char * p_file, int p_line, const char * p_function, int p_code):
	Error(p_code),
	message(p_message),
	file(p_file),
	line(p_line),
	function(p_function)
{
}

QString InplaceError::str() const
{
	QString result = message;

#ifndef CUTEHMI_NDEBUG
	QStringList location;
	if (file)
		location << QString("file: ") + file;
	if (line)
		location << QString("line: ") + QString::number(line);
	if (function)
		location << QString("function: ") + function;

	if (!location.isEmpty())
		result += QString(" [") + location.join(' ') + "]";
#endif

	return result;
}

}

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
