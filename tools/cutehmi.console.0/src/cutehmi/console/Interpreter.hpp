#ifndef H_TOOLS_CUTEHMI_CONSOLE_0_SRC_CUTEHMI_CONSOLE_INTERPRETER_HPP
#define H_TOOLS_CUTEHMI_CONSOLE_0_SRC_CUTEHMI_CONSOLE_INTERPRETER_HPP

#include "Command.hpp"

#include <QObject>
#include <QCommandLineParser>
#include <QQmlApplicationEngine>

namespace cutehmi {
namespace console {

class Interpreter:
	public QObject
{
		Q_OBJECT

	public:
		Interpreter(QQmlApplicationEngine * engine, QObject * parent = nullptr);

	public slots:
		void interperetLine(const QString & line);

	signals:
		void lineInterpreted();

	private:
		struct Commands {
				class Help : public Command {
					public:
						using Command::Command;

						QString execute(QQmlApplicationEngine * engine) override;

						QString createSynopsisString(const CommandsContainer & commands);

						QString createDescriptionString(const CommandsContainer & commands);

						QString createDefaultsString(const CommandsContainer & commands);
				} help;

				class Quit : public Command {
					public:
						using Command::Command;

						QString execute(QQmlApplicationEngine * engine) override;
				} quit;
		} m_commands;

		QQmlApplicationEngine * m_engine;
		QCommandLineParser m_cmd;
		QCommandLineOption m_quitOption;
		QObject * m_currentObject;
		Command m_mainContextCommand;
		Command m_helpContextCommand;
};

}
}

#endif

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
