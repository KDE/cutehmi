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
