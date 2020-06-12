#ifndef H_TOOLS_CUTEHMI_CONSOLE_0_SRC_CUTEHMI_CONSOLE_INPUTHANDLER_HPP
#define H_TOOLS_CUTEHMI_CONSOLE_0_SRC_CUTEHMI_CONSOLE_INPUTHANDLER_HPP

#include <QTextStream>

namespace cutehmi {
namespace console {

class InputHandler:
	public QObject
{
		Q_OBJECT

	public:
		InputHandler();

	public slots:
		void readLine();

	signals:
		void lineRead(QString line);

	protected:
		void printCommandPrompt();

	private:
		QTextStream m_inputStream;
		QString m_line;
};

}
}

#endif
