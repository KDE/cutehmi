#ifndef H_TOOLS_CUTEHMI_CONSOLE_0_SRC_CUTEHMI_CONSOLE_INTERPRETER_HPP
#define H_TOOLS_CUTEHMI_CONSOLE_0_SRC_CUTEHMI_CONSOLE_INTERPRETER_HPP

#include "Command.hpp"

#include <QObject>
#include <QCommandLineParser>
#include <QQmlApplicationEngine>

#include <memory>

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
		QStringList parseLine(const QString & line);

		struct Commands {
				class List : public Command {
					public:
						using Command::Command;

						class Children : public Command {
							public:
								using Command::Command;

								QString execute(ExecutionContext & context) override;
						};
						std::unique_ptr<Children> children;

						class Property : public Command {
							public:
								using Command::Command;

								QString execute(ExecutionContext & context) override;

								std::unique_ptr<Command> name;

							private:
								QString  properties(ExecutionContext & context);

								QString  property(ExecutionContext & context, const QString & matchedString);
						};
						std::unique_ptr<Property> property;
				};
				std::unique_ptr<List> list;

				class Scope : public Command {
					public:
						using Command::Command;

						QString execute(ExecutionContext & context) override;

						std::unique_ptr<Command> object;
				};
				std::unique_ptr<Scope> scope;

				class Quit : public Command {
					public:
						using Command::Command;

						QString execute(ExecutionContext & context) override;
				};
				std::unique_ptr<Quit> quit;

				// Help has different root, so it may need to be moved to separate struct at some point.
				class Help : public Command {
					public:
						using Command::Command;

						QString execute(ExecutionContext & context) override;

					private:
						QString createSynopsisString(const CommandsContainer & commands, int optionalFrom);

						QString createDescriptionString(const CommandsContainer & commands);

						QString createDefaultsString(const CommandsContainer & commands);
				};
				std::unique_ptr<Help> help;
		} m_commands;

		Command::ExecutionContext m_context;
		QCommandLineParser m_cmd;
		QCommandLineOption m_quitOption;
		QObject * m_currentObject;
		Command m_consoleCommand;
		Command m_helpCommand;
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
