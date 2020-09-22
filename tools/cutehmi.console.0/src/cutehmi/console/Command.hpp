#ifndef H_TOOLS_CUTEHMI_CONSOLE_0_SRC_CUTEHMI_CONSOLE_COMMAND_HPP
#define H_TOOLS_CUTEHMI_CONSOLE_0_SRC_CUTEHMI_CONSOLE_COMMAND_HPP

#include <cutehmi/Error.hpp>

#include <QList>
#include <QString>
#include <QRegularExpression>
#include <QQmlApplicationEngine>

namespace cutehmi {
namespace console {

class Command
{
	public:
		class Error:
			public cutehmi::Error
		{
			public:
				enum : int {
					UNACCEPTED_SUBCOMMAND = SUBCLASS_BEGIN,
					SUBCOMMAND_REQUIRED
				};

				Error(int code, const QString & message);

				QString message() const;

			private:
				QString m_message;
		};

		struct ExecutionContext
		{
			QQmlApplicationEngine * engine;
			QObject * scopeObject;
		};

		typedef QList<Error> ErrorsContainer;

		typedef QList<Command *> CommandsContainer;

		Command(const QString & name = QString(), const QRegularExpression & matchingPattern = QRegularExpression(".*"));

		Command(const QStringList & matchingStrings);

		virtual ~Command() = default;

		const Command * parentCommand() const;

		Command * parentCommand();

		QStringList names() const;

		void setNames(const QStringList & names);

		bool subcommandRequired() const;

		void setSubcommandRequired(bool required);

		QString defaultSubcommandString() const;

		void setDefaultSubcommandString(const QString & defaultSubcommandString);

		QString help() const;

		void setHelp(const QString & help);

		QRegularExpression matchingPattern() const;

		void setMatchingPattern(const QRegularExpression & matchingPattern);

		void setMatchingStrings(const QStringList & matchingStrings);

		Command & addSubcommand(Command * subcommand);

		CommandsContainer & subcommands();

		const CommandsContainer & subcommands() const;

		const CommandsContainer & matchedChain() const;

		CommandsContainer matchedNonDefaultChain() const;

		bool isSet() const;

		QString matchedString() const;

		bool matchedByDefaultSubcommandString() const;

		void parse(const QStringList & commandStrings);

		void reset();

		void sortByMatchingPatterns();

		const ErrorsContainer & errors() const;

		ErrorsContainer collectErrors() const;

		virtual QString execute(ExecutionContext & context);

	protected:
		void setParentCommand(Command * parentCommand);

		bool match(QStringList commandStrings);

		void pushError(const Error & error);

		void setMatchedByDefaultSubcommandString(bool matchedByDefaultSubcommandString);

	private:
		Command * m_parentCommand;
		QStringList m_names;
		bool m_subcommandRequired;
		QRegularExpression m_matchingPattern;
		bool m_matchedByDefaultSubcommandString;
		QString m_defaultSubcommandString;
		QString m_help;
		CommandsContainer m_subcommands;
		CommandsContainer m_matchedChain;
		QString m_matchedString;
		ErrorsContainer m_errors;
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
