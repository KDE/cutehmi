#include "Interpreter.hpp"
#include "logging.hpp"

#include <QRegExp>
#include <QQmlExpression>

namespace cutehmi {
namespace console {

Interpreter::Interpreter(QQmlApplicationEngine * engine, QObject * parent):
	QObject(parent),
	m_engine(engine),
	m_quitOption("quit", QCoreApplication::translate("main", "Gracefully quit the console.")),
	m_currentObject(nullptr)
{
	m_mainContextCommand.setNames({"\\"});
	m_mainContextCommand.setHelp(tr("Denotes console command."));
	m_mainContextCommand.setMatchingStrings({"\\"});
	m_mainContextCommand.setSubcommandRequired(true);

	m_commands.quit = Commands::Quit({"quit", "q"});
	m_commands.quit.setHelp(tr("Quit the console."));
	m_commands.help.addSubcommand(& m_commands.quit);
	m_mainContextCommand.addSubcommand(& m_commands.quit);

	m_helpContextCommand.setNames({"\\"});
	m_helpContextCommand.setHelp(tr("Denotes console command."));
	m_helpContextCommand.setMatchingStrings({"\\"});
	m_helpContextCommand.setSubcommandRequired(true);

	m_commands.help = Commands::Help({"help", "h"});
	m_commands.help.setHelp(tr("Shows help."));
	m_commands.help.addSubcommand(& m_mainContextCommand);
	m_commands.help.setDefaultSubcommandString("\\");
	m_helpContextCommand.addSubcommand(& m_commands.help);
}

void Interpreter::interperetLine(const QString & line)
{
	QStringList commands = line.split(QRegExp("\\s+|\\b"), QString::SkipEmptyParts);

	m_helpContextCommand.parse(commands);
	if (m_commands.help.isSet())
		CUTEHMI_INFO(m_helpContextCommand.execute(m_engine));
	else {
		m_mainContextCommand.parse(commands);
		if (m_mainContextCommand.isSet()) {
			Command::ErrorsContainer errors = m_mainContextCommand.collectErrors();
			if (!errors.isEmpty()) {
				QString errorString(tr("Command has failed because of following errors:"));
				for (auto error : errors) {
					errorString.append("\n- ");
					errorString.append(error.message());
				}
				CUTEHMI_CRITICAL(errorString);
			} else
				CUTEHMI_INFO(m_mainContextCommand.execute(m_engine));
		}
	}

	if (!m_mainContextCommand.isSet() && !m_helpContextCommand.isSet()) {
		QObject * object;
		if (!m_engine->rootObjects().isEmpty())
			object = m_engine->rootObjects().at(0);
		else
			object = m_engine;
		QQmlExpression qmlExpression(m_engine->rootContext(), object, line);
		bool valueIsUndefined;
		QVariant expressionResult = qmlExpression.evaluate(& valueIsUndefined);
		if (!valueIsUndefined)
			CUTEHMI_INFO(expressionResult);
	}

	QCoreApplication::processEvents();

	emit lineInterpreted();
}

QString Interpreter::Commands::Quit::execute(QQmlApplicationEngine * engine)
{
	Q_UNUSED(engine)

	QCoreApplication::quit();
	return "See you.";
}

QString Interpreter::Commands::Help::execute(QQmlApplicationEngine * engine)
{
	Q_UNUSED(engine)

	QString result;

	Command::CommandsContainer commands = matchedChain();

	{
		QString commandName;
		Command::CommandsContainer matchedNonDefaultCommands = matchedNonDefaultChain();
		if (!matchedNonDefaultCommands.isEmpty())
			commandName = matchedNonDefaultCommands.last()->names().value(0);
		else if (!commands.isEmpty())
			commandName = commands.last()->names().value(0);
		else {
			commands.append(parentCommand());
			commandName = names().value(0);
		}
		result.append(QCoreApplication::translate("Interpreter::Commands::Help", "Help '%1'...").arg(commandName));
	}

	// Append single choice subcommands to the chain.
	while (commands.last()->subcommands().length() == 1)
		commands.append(commands.last()->subcommands().at(0));

	result.append("\n\n");
	result.append(createSynopsisString(commands));

	result.append("\n");
	result.append(QCoreApplication::translate("Interpreter::Commands::Help", "Where:"));
	result.append("\n");
	result.append(createDescriptionString(commands));

	if (!commands.last()->subcommands().isEmpty()) {
		result.append("\n");
		result.append(QCoreApplication::translate("Interpreter::Commands::Help", "And <command> is one of the following:"));
		result.append("\n");
		result.append(createDescriptionString(commands.last()->subcommands()));
	}

	QString defaultsString(createDefaultsString(commands));
	if (!defaultsString.isEmpty()) {
		result.append("\n");
		result.append(defaultsString);
	}

	result.append("\n");

	return result;
}

QString Interpreter::Commands::Help::createSynopsisString(const Command::CommandsContainer & commands)
{
	QString synopsis(QCoreApplication::translate("Interpreter::Commands::Help", "Synopsis:"));
	bool required = true;
	for (auto command : commands) {
		QString commandString = command->names().at(0);
		if (synopsis.back() != '\\')
			synopsis.append(' ');
		if (!required)
			synopsis.append('[');
		synopsis.append(command->names().at(0));
		if (!required)
			synopsis.append(']');
		required = command->subcommandRequired();
	}
	if (!commands.last()->subcommands().isEmpty()) {
		if (!required)
			synopsis.append('[');
		synopsis.append(QCoreApplication::translate("Interpreter::Commands::Help", "<command>"));
		if (!required)
			synopsis.append(']');
	}
	return synopsis;
}

QString Interpreter::Commands::Help::createDescriptionString(const Command::CommandsContainer & commands)
{
	static constexpr int TERMINAL_WIDTH = 79;
	static constexpr int SPACING = 2;

	QStringList lines;

	QStringList nameList;
	QStringList helpList;
	for (auto command : commands) {
		QString names = command->names().join(", ");
		names.prepend(' ');
		nameList.append(names);
		helpList.append(command->help());
	}
	int nameMaxLenght = 0;
	for (auto name : nameList)
		nameMaxLenght = qMax(nameMaxLenght, name.length());

	for (QStringList::iterator name = nameList.begin(); name != nameList.end(); ++name)
		*name = name->leftJustified(nameMaxLenght);

	const int helpMaxLength = TERMINAL_WIDTH - nameMaxLenght - SPACING;	// Reserve characters for space betweeen names and help string.
	auto helpIt = helpList.begin();
	for (auto nameIt : nameList) {
		QStringList helpLineWords;
		QList<QStringList> helpLineWordsList;
		QStringList helpWords = helpIt->split(' ');
		int remainingLineWidth = helpMaxLength;
		for (auto helpWord : helpWords) {
			helpLineWords.append(helpWord);
			remainingLineWidth -= helpWord.length() + 1;	// Reserve +1 for space between the words.
			if (remainingLineWidth < helpWord.length()) {
				helpLineWordsList.append(helpLineWords);
				helpLineWords.clear();
				remainingLineWidth = helpMaxLength;
			}
		}
		helpLineWordsList.append(helpLineWords);

		QString line;
		line.clear();
		line.append(nameIt);
		line.append(QString(SPACING, ' '));
		line.append(helpLineWordsList.takeFirst().join(' '));
		lines.append(line);

		for (auto helpLineIt : helpLineWordsList)
			lines.append(QString(nameMaxLenght + SPACING, ' ') + helpLineIt.join(' '));

		++helpIt;
	}

	return lines.join('\n');
}

QString Interpreter::Commands::Help::createDefaultsString(const Command::CommandsContainer & commands)
{
	QString result(QCoreApplication::translate("Interpreter::Commands::Help", "Defaults:"));

	QString defaultSubcommand;
	for (auto command : commands) {
		if (!defaultSubcommand.isEmpty()) {
			if (result.back() != '\\')
				result.append(' ');
			CUTEHMI_DEBUG("!isEmpty " << defaultSubcommand);
			result.append('\'').append(defaultSubcommand).append('\'');
		} else {
			if (result.back() != '\\')
				result.append(' ');
			CUTEHMI_DEBUG("isEmpty  " << command->names().value(0));
			result.append(command->names().value(0));
		}
		if (!command->defaultSubcommandString().isEmpty())
			defaultSubcommand = command->defaultSubcommandString();
		else if (!defaultSubcommand.isEmpty())
			break;
	}

	if (!defaultSubcommand.isEmpty())
		return result;

	return QString();
}

}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
