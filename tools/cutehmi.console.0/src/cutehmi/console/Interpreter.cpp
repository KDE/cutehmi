#include "Interpreter.hpp"
#include "logging.hpp"

#include <QRegExp>
#include <QQmlExpression>
#include <QMetaObject>

namespace cutehmi {
namespace console {

static QString qobjectShortInfo(const QObject * object) {
	QString info;
	info.append(object->metaObject()->className());
	if (!object->objectName().isEmpty()) {
		info.append(" - ");
		info.append(object->objectName());
	}
	return info;
};

static QString qmetaObjectShortInfo(const QMetaObject * metaObject) {
	return metaObject->className();
};

static QString strError(const QString & message) {
	return QCoreApplication::translate("cutehmi::console::strError", "Command error: %1").arg(message);
}

static QString strErrors(const QStringList & errorMessages) {
	if (errorMessages.isEmpty())
		return "";

	if (errorMessages.count() == 1)
		return strError(errorMessages.at(0));

	QString result = QCoreApplication::translate("cutehmi::console::strErrors", "Command has failed because of following errors:");
	for (auto message : errorMessages) {
		result.append("\n- ");
		result.append(message);
	}
	return result;
}

static QObjectList findInChildren(const QObjectList & children, const QString & name)
{
	QObjectList result;

	for (auto child : children)
		if (child->objectName() == name)
			result.append(child);

	// Search recursively.
	for (auto child : children)
		result.append(findInChildren(child->children(), name));

	return result;
}

static QString strWarning(const QString & message) {
	return QCoreApplication::translate("cutehmi::console::strWarning", "Warning: %1").arg(message);
}

static QString strWarnings(const QStringList & warningMessages) {
	if (warningMessages.isEmpty())
		return "";

	if (warningMessages.count() == 1)
		return strWarning(warningMessages.at(0));

	QString result = QCoreApplication::translate("cutehmi::console::commandWarnings", "Warnings:");
	for (auto message : warningMessages) {
		result.append("\n- ");
		result.append(message);
	}
	return result;
}

static void appendWarnings(QString & string, const QStringList & warningMessages) {
	if (warningMessages.isEmpty())
		return;

	string.append('\n').append(strWarnings(warningMessages));
}


Interpreter::Interpreter(QQmlApplicationEngine * engine, QObject * parent):
	QObject(parent),
	m_context{engine,
			nullptr},
	m_quitOption("quit", QCoreApplication::translate("main", "Gracefully quit the console.")),
	m_currentObject(nullptr)
{
	if (!m_context.engine->rootObjects().isEmpty())
		m_context.scopeObject = m_context.engine->rootObjects().at(0);
	else
		m_context.scopeObject = m_context.engine;


	m_consoleCommand.setNames({"\\"});
	m_consoleCommand.setHelp(tr("Denotes console command."));
	m_consoleCommand.setMatchingStrings({"\\"});
	m_consoleCommand.setSubcommandRequired(true);


	m_commands.list = std::make_unique<Commands::List>(QStringList({"list", "l"}));
	m_commands.list->setHelp(tr("List selected things."));
	m_commands.list->setDefaultSubcommandString("children");
	m_consoleCommand.addSubcommand(m_commands.list.get());

	m_commands.list->children = std::make_unique<Commands::List::Children>(QStringList({"children", "c"}));
	m_commands.list->children->setHelp(tr("List scope object children. List is presented in the form: `index: type [- object_name]`."));
	m_commands.list->addSubcommand(m_commands.list->children.get());

	m_commands.list->property = std::make_unique<Commands::List::Properties>(QStringList({"property", "p"}));
	m_commands.list->property->setHelp(tr("List scope object properties or property details. Without argument command lists"
					" properties of current scope object. Properties are grouped into meta-object class sections. Each section"
					" lists properties in the form: `index: type - propery_name`. If argument is given command prints details on"
					" property selected by the argument."));
	m_commands.list->addSubcommand(m_commands.list->property.get());

	m_commands.list->property->name = std::make_unique<Command>("name");
	m_commands.list->property->name->setHelp(tr("Property name or index."));
	m_commands.list->property->addSubcommand(m_commands.list->property->name.get());


	m_commands.scope = std::make_unique<Commands::Scope>(QStringList({"scope", "s"}));
	m_commands.scope->setHelp(tr("Remind current scope object or select a new one. Without argument command prints short memento of"
					" a current scope object. If argument is given, command will try to change current scope object to the one"
					" specified by the argument."));
	m_consoleCommand.addSubcommand(m_commands.scope.get());

	m_commands.scope->object = std::make_unique<Command>("object");
	m_commands.scope->object->setHelp(tr("Object path relative to current scope object. Object path can be composed of object names"
					" or indices separated by slash character ('/'). Double dot ('..') can be used to choose parent object. If"
					" object names are given search is performed recursively, thus this command does not work like standard file path"
					" lookup. If more than one objects with given name were found, command picks the first one."));
	m_commands.scope->addSubcommand(m_commands.scope->object.get());


	m_commands.quit = std::make_unique<Commands::Quit>(QStringList({"quit", "q"}));
	m_commands.quit->setHelp(tr("Quit the console."));
	m_consoleCommand.addSubcommand(m_commands.quit.get());


	m_helpCommand.setNames({"\\"});
	m_helpCommand.setHelp(tr("Denotes console command."));
	m_helpCommand.setMatchingStrings({"\\"});
	m_helpCommand.setSubcommandRequired(true);

	m_commands.help = std::make_unique<Commands::Help>(QStringList({"help", "h"}));
	m_commands.help->setHelp(tr("Shows help on specified command (arguments may follow)."));
	m_commands.help->addSubcommand(& m_consoleCommand);
	m_helpCommand.addSubcommand(m_commands.help.get());
}

void Interpreter::interperetLine(const QString & line)
{
	QStringList commands = parseLine(line);

	m_helpCommand.parse(commands);
	if (m_commands.help->isSet())
		CUTEHMI_INFO(m_helpCommand.execute(m_context));
	else {
		m_consoleCommand.parse(commands);
		if (m_consoleCommand.isSet()) {
			Command::ErrorsContainer errors = m_consoleCommand.collectErrors();
			if (!errors.isEmpty()) {
				QStringList errorMessages;
				for (auto error : errors)
					errorMessages.append(error.message());
				CUTEHMI_CRITICAL(strErrors(errorMessages));
			} else
				CUTEHMI_INFO(m_consoleCommand.execute(m_context));
		}
	}

	if (!m_consoleCommand.isSet() && !m_helpCommand.isSet()) {
		QQmlExpression qmlExpression(m_context.engine->rootContext(), m_context.scopeObject, line);
		bool valueIsUndefined;
		QVariant expressionResult = qmlExpression.evaluate(& valueIsUndefined);
		if (!valueIsUndefined)
			CUTEHMI_INFO(expressionResult);
	}

	QCoreApplication::processEvents();

	emit lineInterpreted();
}

QStringList Interpreter::parseLine(const QString & line)
{
	// Double quite separated commands
//	QStringList doubleQuoteSeparatedCommands = line.split('"', QString::SkipEmptyParts);

	// Split by whitespace.
	QStringList whitespaceSeparatedCommands = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);

	// Split words by '\' character.
	QStringList commands;
	for (auto command : whitespaceSeparatedCommands)
		if (command.contains('\\'))
			commands.append(command.split(QRegExp("\\b"), QString::SkipEmptyParts));
		else
			commands.append(command);

	return commands;
}

QString Interpreter::Commands::Quit::execute(ExecutionContext & context)
{
	Q_UNUSED(context)

	QCoreApplication::quit();
	return "See you.";
}

QString Interpreter::Commands::Help::execute(ExecutionContext & context)
{
	Q_UNUSED(context)

	QString result;

	Command::CommandsContainer commands = matchedNonDefaultChain();

	QString commandName;
	if (!commands.isEmpty())
		commandName = commands.last()->names().value(0);
	else if (!commands.isEmpty())
		commandName = commands.last()->names().value(0);
	else {
		commands.append(parentCommand());
		commandName = names().value(0);
	}
	result.append(QCoreApplication::translate("cutehmi::console::Interpreter", "Help '%1'...").arg(commandName));

	// Append single choice subcommands to the chain.
	while (commands.last()->subcommands().length() == 1)
		commands.append(commands.last()->subcommands().at(0));

	result.append("\n\n");
	// Setting `optionalFrom` parameter to matched non-default chain length, so that commands explicity typed by the user won't
	// be presented in square brackets.
	result.append(createSynopsisString(commands, matchedNonDefaultChain().length()));

	result.append("\n\n");
	result.append(QCoreApplication::translate("cutehmi::console::Interpreter", "Where:"));
	result.append("\n");
	result.append(createDescriptionString(commands));

	if (!commands.last()->subcommands().isEmpty()) {
		result.append("\n\n");
		result.append(QCoreApplication::translate("cutehmi::console::Interpreter", "And <command> is one of the following:"));
		result.append("\n");
		result.append(createDescriptionString(commands.last()->subcommands()));
	}

	if (matchedChain().length() > matchedNonDefaultChain().length()) {
		result.append("\n\n");
		result.append(createDefaultsString(matchedChain()));
	}

	result.append("\n");

	return result;
}

QString Interpreter::Commands::Help::createSynopsisString(const Command::CommandsContainer & commands, int optionalFrom)
{
	QString synopsis(QCoreApplication::translate("cutehmi::console::Interpreter", "Synopsis:"));
	bool subcommandRequired = true;
	bool makeSpaceBefore = true;
	bool insideOptional = false;
	int currentCommandIndex = 0;
	for (auto command : commands) {
		QString commandString = command->names().at(0);

		if (makeSpaceBefore)
			synopsis.append(' ');

		if (!subcommandRequired && !insideOptional && (currentCommandIndex >= optionalFrom)) {
			synopsis.append('[');
			insideOptional = true;
		}

		synopsis.append(command->names().at(0));

		if (command->names().at(0) == "\\")
			makeSpaceBefore = false;
		else
			makeSpaceBefore = true;

		subcommandRequired = command->subcommandRequired();

		currentCommandIndex++;
	}
	if (!commands.last()->subcommands().isEmpty()) {
		if (makeSpaceBefore)
			synopsis.append(' ');

		if (!subcommandRequired && !insideOptional && (currentCommandIndex >= optionalFrom)) {
			synopsis.append('[');
			insideOptional = true;
		}

		synopsis.append(QCoreApplication::translate("cutehmi::console::Interpreter", "<command>"));
	}

	if (insideOptional)
		synopsis.append(']');

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
			if (remainingLineWidth < helpWord.length()) {
				helpLineWordsList.append(helpLineWords);
				helpLineWords.clear();
				helpLineWords.append(helpWord);
				remainingLineWidth = helpMaxLength - helpWord.length() - 1; // Reserve -1 for space between the words.
			} else {
				helpLineWords.append(helpWord);
				remainingLineWidth -= helpWord.length() + 1;	// Reserve +1 for space between the words.
			}
		}
		helpLineWordsList.append(helpLineWords);

		QString line;
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
	QString result(QCoreApplication::translate("cutehmi::console::Interpreter", "Defaults:"));

	QString defaultSubcommand;
	for (auto command : commands) {
		if (!defaultSubcommand.isEmpty()) {
			if (result.back() != '\\')
				result.append(' ');
			result.append(defaultSubcommand);
		} else {
			if (result.back() != '\\')
				result.append(' ');
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

QString Interpreter::Commands::Scope::execute(ExecutionContext & context)
{
	QStringList warnings;

	CommandsContainer subcommands = matchedChain();
	if (subcommands.isEmpty())
		return qobjectShortInfo(context.scopeObject);
	else {
		if (subcommands.at(0) == object.get()) {
			QString path = object->matchedString();
			QStringList parts = path.split('/', QString::SkipEmptyParts);
			QObject * candidate;
			if (path.startsWith('/'))
				candidate = context.engine;
			else
				candidate = context.scopeObject;
			for (auto part : parts) {
				if (part == ".") {
					candidate = context.scopeObject;
				} else if (part == "..") {
					// Select parent.
					if (candidate->parent() != nullptr)
						candidate = candidate->parent();
					else {
						if (candidate != context.engine)
							candidate = context.engine;
						else
							return strError(QCoreApplication::translate("cutehmi::console::Interpreter", "Can not select parent - root object already reached."));
					}
				} else {
					QObjectList childList;
					if (candidate == context.engine)
						// If QML engine is a scope object then list its root object instead of its children.
						childList = context.engine->rootObjects();
					else
						childList = candidate->children();

					bool ok;
					int index = part.toInt(& ok);
					if (ok) {
						// Select by index.
						if (index < 0)
							return strError(QCoreApplication::translate("cutehmi::console::Interpreter", "Can not use negative indices."));
						else if (index >= childList.count())
							return strError(QCoreApplication::translate("cutehmi::console::Interpreter", "Given index ('%1') is too large.").arg(index));
						else
							candidate = childList.at(index);
					} else {
						// Select by objectName.
						QObjectList children = findInChildren(childList, part);
						if (children.count() == 0)
							return strError(QCoreApplication::translate("cutehmi::console::Interpreter", "Child object with given name ('%1') not found.").arg(part));
						else {
							if (children.count() > 1)
								warnings.append(QCoreApplication::translate("cutehmi::console::Interpreter", "Found more than one object with given name ('%1').").arg(part));
							candidate = children.at(0);
						}
					}
				}
			}
			context.scopeObject = candidate;

			QString result = QCoreApplication::translate("cutehmi::console::Interpreter", "New scope object: '%1'.").arg(qobjectShortInfo(context.scopeObject));
			appendWarnings(result, warnings);
			return result;
		}
	}

	return strError("Unrecognized argument.");
}

QString Interpreter::Commands::List::Children::execute(Command::ExecutionContext & context)
{
	QString result;

	result.append(QCoreApplication::translate("cutehmi::console::Interpreter", "List children of '%1'...").arg(qobjectShortInfo(context.scopeObject)));

	QObjectList childList;
	if (context.scopeObject == context.engine)
		// If QML engine is a scope object then list its root object instead of its children.
		childList = context.engine->rootObjects();
	else
		childList = context.scopeObject->children();

	if (childList.isEmpty()) {
		result.append("\n\n");
		result.append(QCoreApplication::translate("cutehmi::console::Interpreter", "None"));
		result.append('\n');
	} else {
		result.append("\n\n");
		int index = 0;
		for (auto child : childList) {
			result.append(QString::number(index)).append(": ");
			result.append(qobjectShortInfo(child));
			result.append('\n');
			index++;
		}
	}

	return result;
}

QString Interpreter::Commands::List::Properties::execute(Command::ExecutionContext & context)
{
	if (!matchedChain().isEmpty())
		// List property details.
		return property(context, name->matchedString());
	else
		// List properties.
		return properties(context);
}

QString Interpreter::Commands::List::Properties::properties(Command::ExecutionContext & context)
{
	QString result;

	result.append(QCoreApplication::translate("cutehmi::console::Interpreter", "List properties of '%1'...").arg(qobjectShortInfo(context.scopeObject)));

	QList<const QMetaObject *> moStack;
	{
		const QMetaObject * mo = context.scopeObject->metaObject();
		do {
			moStack.append(mo);
			mo = mo->superClass();
		} while (mo != nullptr);
	}

	result.append("\n");
	while (!moStack.isEmpty()) {
		const QMetaObject * mo = moStack.takeLast();

		result.append("\n");
		result.append(qmetaObjectShortInfo(mo));
		result.append(":\n");

		for (int i = mo->propertyOffset(); i < mo->propertyCount(); i++) {
			QMetaProperty mp = mo->property(i);
			result.append(QString::number(i)).append(": ");
			result.append(mp.typeName());
			result.append(" - ");
			result.append(mp.name());
			result.append('\n');
		}
	}

	return result;
}

QString Interpreter::Commands::List::Properties::property(Command::ExecutionContext & context, const QString & matchedString)
{
	QString result;

	const QMetaObject * mo = context.scopeObject->metaObject();
	bool ok;
	int index = matchedString.toInt(& ok);
	if (ok) {
		// Select by index.
		if (index < 0)
			return strError(QCoreApplication::translate("cutehmi::console::Interpreter", "Can not use negative indices."));
		else if (index >= mo->propertyCount())
			return strError(QCoreApplication::translate("cutehmi::console::Interpreter", "Given index ('%1') is too large.").arg(index));
	} else {
		// Select by name.
		index = mo->indexOfProperty(matchedString.toLocal8Bit().constData());
		if (index == -1)
			return strError(QCoreApplication::translate("cutehmi::console::Interpreter", "Could not find property with given name ('%1').").arg(matchedString));
	}

	QMetaProperty mp = mo->property(index);

	QString trYes = QCoreApplication::translate("cutehmi::console::Interpreter", "yes");
	QString trNo = QCoreApplication::translate("cutehmi::console::Interpreter", "no");

	result.append(QCoreApplication::translate("cutehmi::console::Interpreter", "List property '%1' details...").arg(mp.name()));
	result.append("\n\n");
	result.append(QCoreApplication::translate("cutehmi::console::Interpreter", "Name: '%1'").arg(mp.name()));
	result.append("\n");
	result.append(QCoreApplication::translate("cutehmi::console::Interpreter", "Type: '%1'").arg(mp.typeName()));
	result.append("\n");
	result.append(QCoreApplication::translate("cutehmi::console::Interpreter", "Constant: %1").arg(mp.isConstant() ? trYes : trNo));
	result.append("\n");
	result.append(QCoreApplication::translate("cutehmi::console::Interpreter", "Designable: %1").arg(mp.isDesignable(context.scopeObject) ? trYes : trNo));
	result.append("\n");
	result.append(QCoreApplication::translate("cutehmi::console::Interpreter", "Enum: %1").arg(mp.isEnumType() ? trYes : trNo));
	result.append("\n");
	result.append(QCoreApplication::translate("cutehmi::console::Interpreter", "Final: %1").arg(mp.isFinal() ? trYes : trNo));
	result.append("\n");
	result.append(QCoreApplication::translate("cutehmi::console::Interpreter", "Flag: %1").arg(mp.isFlagType() ? trYes : trNo));
	result.append("\n");
	result.append(QCoreApplication::translate("cutehmi::console::Interpreter", "Readable: %1").arg(mp.isReadable() ? trYes : trNo));
	result.append("\n");
	result.append(QCoreApplication::translate("cutehmi::console::Interpreter", "Resettable: %1").arg(mp.isResettable() ? trYes : trNo));
	result.append("\n");
	result.append(QCoreApplication::translate("cutehmi::console::Interpreter", "Scriptable: %1").arg(mp.isScriptable(context.scopeObject) ? trYes : trNo));
	result.append("\n");
	result.append(QCoreApplication::translate("cutehmi::console::Interpreter", "Stored: %1").arg(mp.isStored(context.scopeObject) ? trYes : trNo));
	result.append("\n");
	result.append(QCoreApplication::translate("cutehmi::console::Interpreter", "User: %1").arg(mp.isUser(context.scopeObject) ? trYes : trNo));
	result.append("\n");
	result.append(QCoreApplication::translate("cutehmi::console::Interpreter", "Valid: %1").arg(mp.isValid() ? trYes : trNo));
	result.append("\n");
	result.append(QCoreApplication::translate("cutehmi::console::Interpreter", "Writable: %1").arg(mp.isWritable() ? trYes : trNo));
	result.append("\n");
	result.append(QCoreApplication::translate("cutehmi::console::Interpreter", "Notify signal: %1").arg(mp.notifySignal().name().constData()));
	result.append("\n");

	return result;
}

}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
