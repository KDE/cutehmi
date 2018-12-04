#ifndef H_MODULES_CUTEHMI__1_INCLUDE_CUTEHMI_PROMPT_HPP
#define H_MODULES_CUTEHMI__1_INCLUDE_CUTEHMI_PROMPT_HPP

#include "internal/common.hpp"

#include <memory>

#include <QObject>
#include <QAtomicInteger>
#include <QMutex>

namespace cutehmi {

/**
 * %Prompt message.
 */
class CUTEHMI_API Prompt:
	public QObject
{
	Q_OBJECT

	public:
		Q_PROPERTY(Type type READ type WRITE setType NOTIFY typeChanged)
		Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
		Q_PROPERTY(QString informativeText READ informativeText WRITE setInformativeText NOTIFY informativeTextChanged)
		Q_PROPERTY(QString detailedText READ detailedText WRITE setDetailedText NOTIFY detailedTextChanged)
		Q_PROPERTY(Buttons buttons READ buttons WRITE setButtons NOTIFY buttonsChanged)

		enum Type {
			NOTE = 1,
			WARNING = 2,
			CRITICAL = 3,
			QUESTION = 4
		};
		Q_ENUM(Type)

		enum Button : qint32 {
			BUTTON_OK = 0x00000400,
			BUTTON_OPEN = 0x00002000,
			BUTTON_SAVE = 0x00000800,
			BUTTON_CANCEL = 0x00400000,
			BUTTON_CLOSE = 0x00200000,
			BUTTON_DISCARD = 0x00800000,
			BUTTON_APPLY = 0x02000000,
			BUTTON_RESET = 0x04000000,
			BUTTON_RESTORE_DEFAULTS = 0x08000000,
			BUTTON_HELP = 0x01000000,
			BUTTON_SAVE_ALL = 0x00001000,
			BUTTON_YES = 0x00004000,
			BUTTON_YES_TO_ALL = 0x00008000,
			BUTTON_NO = 0x00010000,
			BUTTON_NO_TO_ALL = 0x00020000,
			BUTTON_ABORT = 0x00040000,
			BUTTON_RETRY = 0x00080000,
			BUTTON_IGNORE = 0x00100000,
			NO_BUTTON = 0x00000000
		};
		Q_DECLARE_FLAGS(Buttons, Button)
		Q_FLAG(Buttons)
		Q_ENUM(Button)

		explicit Prompt(Type type = NOTE, const QString & text = QString(), Buttons buttons = Prompt::NO_BUTTON, QObject * parent = nullptr);

		Prompt(Type type, const QString & text, const QString & informativeText, Buttons buttons = Prompt::NO_BUTTON, QObject * parent = nullptr);

		Prompt(Type type, const QString & text, const QString & informativeText, const QString & detailedText, Buttons buttons = Prompt::NO_BUTTON, QObject * parent = nullptr);

		~Prompt() override = default;

		static std::unique_ptr<Prompt> Note(const QString & text, Buttons buttons = BUTTON_OK);

		static std::unique_ptr<Prompt> Warning(const QString & text, Buttons buttons = BUTTON_OK);

		static std::unique_ptr<Prompt> Question(const QString & text, Buttons buttons = Buttons{BUTTON_YES, BUTTON_NO});

		static std::unique_ptr<Prompt> Critical(const QString & text, Buttons buttons = BUTTON_OK);

		static std::unique_ptr<Prompt> Critical(const ErrorInfo & errorInfo, Buttons buttons = BUTTON_OK);

		Type type() const;

		void setType(Type type);

		QString text() const;

		void setText(const QString & text);

		QString informativeText() const;

		void setInformativeText(const QString & informativeText);

		QString detailedText() const;

		void setDetailedText(const QString & detailedText);

		Buttons buttons() const;

		void setButtons(Buttons buttons);

		Q_INVOKABLE Button response() const;

		std::unique_ptr<Prompt> clone() const;

		Button exec();

	public slots:
		/**
		 * Accept response. Normally a response can be accepted only once. Subsequent calls of this function with values other than
		 * Prompt::NO_BUTTON will not change the value of @a response property and should be avoided.
		 * @param response response to be set.
		 */
		void acceptResponse(Button response);

	signals:
		void typeChanged();

		void textChanged();

		void informativeTextChanged();

		void detailedTextChanged();

		void buttonsChanged();

		void responseArrived(Button response);

	private:
		struct Members
		{
			Type type;
			QString text;
			QString informativeText;
			QString detailedText;
			Buttons buttons;
			Button response;
		};

		MPtr<Members> m;
};

}

Q_DECLARE_OPERATORS_FOR_FLAGS(cutehmi::Prompt::Buttons)

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
