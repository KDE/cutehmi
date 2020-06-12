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

		typedef QList<Error> ErrorsContainer;

		typedef QList<Command *> CommandsContainer;

		Command(const QString & name = QString(), const QRegularExpression & matchingPattern = QRegularExpression(".*"));

		Command(const QStringList & matchingStrings);

		virtual ~Command() = default;

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

		virtual QString execute(QQmlApplicationEngine * engine);

	protected:
		bool match(QStringList commandStrings);

		void pushError(const Error & error);

		void setMatchedByDefaultSubcommandString(bool matchedByDefaultSubcommandString);

	private:
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
