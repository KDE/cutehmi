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
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
