#include "InputHandler.hpp"
#include "logging.hpp"

namespace cutehmi {
namespace console {

InputHandler::InputHandler():
	m_inputStream(stdin, QIODevice::ReadOnly)
{
}

void InputHandler::readLine()
{
	printCommandPrompt();
	m_inputStream.readLineInto(& m_line);
	emit lineRead(m_line);
}

void InputHandler::printCommandPrompt()
{
	putc('#', stdout);
	putc(' ', stdout);
}

}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
