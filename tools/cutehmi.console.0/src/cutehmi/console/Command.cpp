#include "Command.hpp"
#include "logging.hpp"

namespace cutehmi {
namespace console {

Command::Command(const QString & name, const QRegularExpression & matchingPattern):
	m_names(name),
	m_subcommandRequired(false),
	m_matchingPattern(matchingPattern),
	m_matchedByDefaultSubcommandString(false)
{
#ifndef CUTEHMI_NDEBUG
	if (!m_matchingPattern.isValid())
		CUTEHMI_CRITICAL("Invalid regular expression pattern '" << m_matchingPattern.pattern() << "' provided for 'matchingPattern' argument.");
#endif
}

Command::Command(const QStringList & matchingStrings):
	m_names(matchingStrings),
	m_subcommandRequired(false),
	m_matchedByDefaultSubcommandString(false)
{
	setMatchingStrings(matchingStrings);
}

QStringList Command::names() const
{
	return m_names;
}

void Command::setNames(const QStringList & names)
{
	m_names = names;
}

bool Command::subcommandRequired() const
{
	return m_subcommandRequired;
}

void Command::setSubcommandRequired(bool required)
{
	m_subcommandRequired = required;

	CUTEHMI_ASSERT(m_defaultSubcommandString.isEmpty() || !m_subcommandRequired, "subcommand can not be required if command provides default subcommand");
}

QString Command::defaultSubcommandString() const
{
	return m_defaultSubcommandString;
}

void Command::setDefaultSubcommandString(const QString & defaultSubcommand)
{
	m_defaultSubcommandString = defaultSubcommand;

	CUTEHMI_ASSERT(m_defaultSubcommandString.isEmpty() || !m_subcommandRequired, "subcommand can not be required if command provides default subcommand");
}

QString Command::help() const
{
	return m_help;
}

void Command::setHelp(const QString & help)
{
	m_help = help;
}

QRegularExpression Command::matchingPattern() const
{
	return m_matchingPattern;
}

void Command::setMatchingPattern(const QRegularExpression & matchingPattern)
{
	m_matchingPattern = matchingPattern;
#ifndef CUTEHMI_NDEBUG
	if (!m_matchingPattern.isValid())
		CUTEHMI_CRITICAL("Invalid regular expression pattern '" << m_matchingPattern.pattern() << "' provided for 'matchingPattern' argument.");
#endif
}

void Command::setMatchingStrings(const QStringList & matchingStrings)
{
	QStringList escapedStrings;
	for (auto matchingString : matchingStrings)
		escapedStrings.append(QRegularExpression::escape(matchingString));

	m_matchingPattern = QRegularExpression(QString("^(") + escapedStrings.join('|') + ")$");
}

Command & Command::addSubcommand(Command * subcommand)
{
	m_subcommands.append(subcommand);
	return *this;
}

Command::CommandsContainer & Command::subcommands()
{
	return m_subcommands;
}

const Command::CommandsContainer & Command::subcommands() const
{
	return m_subcommands;
}

const Command::CommandsContainer & Command::matchedChain() const
{
	return m_matchedChain;
}

Command::CommandsContainer Command::matchedNonDefaultChain() const
{
	CommandsContainer result;

	for (auto command : matchedChain())
		if (!command->matchedByDefaultSubcommandString())
			result.append(command);

	return result;
}

bool Command::isSet() const
{
	return !m_matchedString.isNull();
}

QString Command::matchedString() const
{
	return m_matchedString;
}

bool Command::matchedByDefaultSubcommandString() const
{
	return m_matchedByDefaultSubcommandString;
}

void Command::parse(const QStringList & commandStrings)
{
	reset();
	match(commandStrings);
}

void Command::reset()
{
	m_matchedByDefaultSubcommandString = false;
	m_errors.clear();
	m_matchedChain.clear();
	m_matchedString = QString();
	for (auto subcommand : m_subcommands)
		subcommand->reset();
}

void Command::sortByMatchingPatterns()
{
	std::sort(m_subcommands.begin(), m_subcommands.end(), [](Command * a, Command * b) {
		return a->matchingPattern().pattern() > b->matchingPattern().pattern();
	});
	for (auto subcommand : m_subcommands)
		subcommand->sortByMatchingPatterns();
}

const Command::ErrorsContainer & Command::errors() const
{
	return m_errors;
}

Command::ErrorsContainer Command::collectErrors() const
{
	ErrorsContainer result = errors();

	for (auto subcommand : m_subcommands)
		result.append(subcommand->collectErrors());

	return result;
}

QString Command::execute(QQmlApplicationEngine * engine)
{
	QString result;

	for (auto subcommand : m_subcommands)
		if (subcommand->isSet())
			result.append(subcommand->execute(engine));

	return result;
}

bool Command::match(QStringList commandStrings)
{
	if (commandStrings.isEmpty())
		return false;

	QRegularExpressionMatch match = m_matchingPattern.match(commandStrings.takeFirst());
	if (match.hasMatch()) {
		m_matchedString = match.captured(match.lastCapturedIndex());

		bool defaultSubcommandStringAppended = false;
		if (commandStrings.isEmpty() && !defaultSubcommandString().isEmpty()) {
			commandStrings.append(defaultSubcommandString());
			defaultSubcommandStringAppended = true;
		}

		if (!commandStrings.isEmpty()) {
			CommandsContainer::iterator subcommandIt = m_subcommands.begin();
			while (subcommandIt != m_subcommands.end()) {
				if ((*subcommandIt)->match(commandStrings)) {
					(*subcommandIt)->setMatchedByDefaultSubcommandString(defaultSubcommandStringAppended);
					m_matchedChain.append(*subcommandIt);
					m_matchedChain.append((*subcommandIt)->matchedChain());
					break;
				}
				++subcommandIt;
			}
			if (subcommandIt == m_subcommands.end())
				pushError(Error(Error::UNACCEPTED_SUBCOMMAND, QCoreApplication::translate("Command", "Unaccepted command line argument '%1'.").arg(commandStrings.first())));
		} else if (subcommandRequired())
			pushError(Error(Error::SUBCOMMAND_REQUIRED, QCoreApplication::translate("Command", "Command '%1' requires an argument.").arg(names().value(0))));
	}

	return match.hasMatch();
}

void Command::pushError(const Command::Error & error)
{
	m_errors.append(error);
}

void Command::setMatchedByDefaultSubcommandString(bool matchedByDefaultSubcommandString)
{
	m_matchedByDefaultSubcommandString = matchedByDefaultSubcommandString;
}

Command::Error::Error(int code, const QString & message):
	cutehmi::Error(code),
	m_message(message)
{
}

QString Command::Error::message() const
{
	return m_message;
}

}
}
