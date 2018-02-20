#ifndef CUTEHMI_CUTEHMI__BASE__1__LIB_INCLUDE_BASE_PROMPT_HPP
#define CUTEHMI_CUTEHMI__BASE__1__LIB_INCLUDE_BASE_PROMPT_HPP

#include "internal/common.hpp"

#include <utils/MPtr.hpp>

#include <memory>

#include <QObject>
#include <QAtomicInteger>
#include <QMutex>

namespace cutehmi {
namespace base {

class CUTEHMI_BASE_API Prompt:
	public QObject
{
	Q_OBJECT

	public:
		Q_PROPERTY(type_t type READ type WRITE setType NOTIFY typeChanged)
		Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
		Q_PROPERTY(QString informativeText READ informativeText WRITE setInformativeText NOTIFY informativeTextChanged)
		Q_PROPERTY(QString detailedText READ detailedText WRITE setDetailedText NOTIFY detailedTextChanged)
		Q_PROPERTY(buttons_t buttons READ buttons WRITE setButtons NOTIFY buttonsChanged)

		enum type_t {
			NOTE = 1,
			WARNING = 2,
			CRITICAL = 3,
			QUESTION = 4
		};
		Q_ENUM(type_t)

		enum button_t : qint32 {
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
		Q_DECLARE_FLAGS(buttons_t, button_t)
		Q_FLAG(buttons_t)
		Q_ENUM(button_t)

		explicit Prompt(type_t type = NOTE, const QString & text = QString(), buttons_t buttons = Prompt::NO_BUTTON, QObject * parent = 0);

		Prompt(type_t type, const QString & text, const QString & informativeText, buttons_t buttons = Prompt::NO_BUTTON, QObject * parent = 0);

		Prompt(type_t type, const QString & text, const QString & informativeText, const QString & detailedText, buttons_t buttons = Prompt::NO_BUTTON, QObject * parent = 0);

		~Prompt() override = default;

		static std::unique_ptr<Prompt> Note(const QString & text, buttons_t buttons = BUTTON_OK);

		static std::unique_ptr<Prompt> Warning(const QString & text, buttons_t buttons = BUTTON_OK);

		static std::unique_ptr<Prompt> Question(const QString & text, buttons_t buttons = buttons_t{BUTTON_YES, BUTTON_NO});

		static std::unique_ptr<Prompt> Critical(const QString & text, buttons_t buttons = BUTTON_OK);

		static std::unique_ptr<Prompt> Critical(const ErrorInfo & errorInfo, buttons_t buttons = BUTTON_OK);

		type_t type() const;

		void setType(type_t type);

		QString text() const;

		void setText(const QString & text);

		QString informativeText() const;

		void setInformativeText(const QString & informativeText);

		QString detailedText() const;

		void setDetailedText(const QString & detailedText);

		buttons_t buttons() const;

		void setButtons(buttons_t buttons);

		Q_INVOKABLE button_t response() const;

		std::unique_ptr<Prompt> clone() const;

		button_t exec();

	public slots:
		/**
		 * Accept response. Normally a response can be accepted only once. Subsequent calls of this function with values other than
		 * Prompt::NO_BUTTON will not change the value of @a response property and should be avoided.
		 * @param response response to be set.
		 */
		void acceptResponse(button_t response);

	signals:
		void typeChanged();

		void textChanged();

		void informativeTextChanged();

		void detailedTextChanged();

		void buttonsChanged();

		void responseArrived(button_t response);

	private:
		struct Members
		{
			type_t type;
			QString text;
			QString informativeText;
			QString detailedText;
			buttons_t buttons;
			button_t response;
		};

		utils::MPtr<Members> m;
};

}
}

Q_DECLARE_OPERATORS_FOR_FLAGS(cutehmi::base::Prompt::buttons_t)

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
