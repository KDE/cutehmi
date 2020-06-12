#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

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

#endif // INTERPRETER_HPP
