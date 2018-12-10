#ifndef H_MODULES_CUTEHMI_u_2_INCLUDE_CUTEHMI_PROMPT_HPP
#define H_MODULES_CUTEHMI_u_2_INCLUDE_CUTEHMI_PROMPT_HPP

#include "internal/platform.hpp"
#include "MPtr.hpp"
#include "ErrorInfo.hpp"

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
		Q_PROPERTY(Button response READ response NOTIFY responseChanged)

		enum Type {
			NOTE = 1,
			WARNING = 2,
			CRITICAL = 3,
			QUESTION = 4
		};
		Q_ENUM(Type)

		enum Button: qint32 {
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

		/**
		 * Constructor.
		 * @param type prompt type.
		 * @param text message for the user.
		 * @param buttons prompt buttons.
		 * @param parent parent object.
		 */
		explicit Prompt(Type type = NOTE, const QString & text = QString(), Buttons buttons = Prompt::NO_BUTTON, QObject * parent = nullptr);

		/**
		 * Constructor.
		 * @param type prompt type.
		 * @param text message for the user.
		 * @param informativeText informative message.
		 * @param buttons prompt buttons.
		 * @param parent parent object.
		 */
		Prompt(Type type, const QString & text, const QString & informativeText, Buttons buttons = Prompt::NO_BUTTON, QObject * parent = nullptr);

		/**
		 * Constructor.
		 * @param type prompt type.
		 * @param text message for the user.
		 * @param informativeText informative message.
		 * @param detailedText detailed message.
		 * @param buttons prompt buttons.
		 * @param parent parent object.
		 */
		Prompt(Type type, const QString & text, const QString & informativeText, const QString & detailedText, Buttons buttons = Prompt::NO_BUTTON, QObject * parent = nullptr);

		/**
		 * Destructor.
		 */
		~Prompt() override = default;

		/**
		 * Get prompt type.
		 * @return prompt type.
		 */
		Type type() const;

		/**
		 * Set prompt type.
		 * @param type prompt type.
		 */
		void setType(Type type);

		/**
		 * Get text.
		 * @return text message for the user.
		 */
		QString text() const;

		/**
		 * Set text.
		 * @param text message for the user.
		 */
		void setText(const QString & text);

		/**
		 * Get informative text.
		 * @return informative message for the user.
		 */
		QString informativeText() const;

		/**
		 * Set informative text.
		 * @param informativeText informative message for the user.
		 */
		void setInformativeText(const QString & informativeText);

		/**
		 * Get detailed text.
		 * @return detailed message for the user.
		 */
		QString detailedText() const;

		/**
		 * Set detailed text.
		 * @param detailedText detailed message for the user.
		 */
		void setDetailedText(const QString & detailedText);

		/**
		 * Get prompt buttons.
		 * @return prompt buttons available to the user.
		 */
		Buttons buttons() const;

		/**
		 * Set buttons.
		 * @param buttons buttons that should be available to the user.
		 */
		void setButtons(Buttons buttons);

		/**
		  * Get prompt response.
		  * @return button that has been pressed by the user or Prompt::NO_BUTTON if user didn't make a choice.
		  */
		Button response() const;

		/**
		 * Clone prompt.
		 * @return prompt clone.
		 */
		std::unique_ptr<Prompt> clone() const;

		/**
		 * Block until user provides a response. This function creates local event loop and blocks until user provides a response.
		 * Before calling exec() you have to connect some signal to acceptResponse() slot.
		 * @return user response.
		 *
		 * @note nested event loops should be avoided in general.
		 *
		 * @return button that has been pressed by the user.
		 */
		Button exec();

	public slots:
		/**
		 * Accept response. Normally a response can be accepted only once. Subsequent calls of this function will not change the
		 * value of @a response property and should be avoided.
		 * @param response response to be set.
		 */
		void acceptResponse(Button response);

	signals:
		void typeChanged();

		void textChanged();

		void informativeTextChanged();

		void detailedTextChanged();

		void buttonsChanged();

		void responseChanged();

		void responseArrived(cutehmi::Prompt::Button response);

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
