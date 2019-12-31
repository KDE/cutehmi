#ifndef H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_DIALOG_HPP
#define H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_DIALOG_HPP

#include "internal/platform.hpp"
#include "MPtr.hpp"
#include "ErrorInfo.hpp"

#include <memory>

#include <QObject>
#include <QAtomicInteger>
#include <QMutex>

namespace cutehmi {

/**
 * %Message.
 */
class CUTEHMI_API Message:
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
			INFO = 1,
			WARNING = 2,
			CRITICAL = 3,
			QUESTION = 4
		};
		Q_ENUM(Type)

		/**
		 * %Dialog button. Button is registered as meta type by Message constructors.
		 */
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

		/**
		 * Register Button as meta type and return its metatype type id. This method is called by Message constructors.
		 * @return meta type id of Button.
		 */
		static int RegisterButtonMetaType() noexcept;

		/**
		 * Notice message. Convenient function that creates informative dialog and advertises it through Messenger instance.
		 * @param text message for the user.
		 * @param buttons message dialog buttons.
		 * @return message instance.
		 */
		static std::unique_ptr<Message> Info(const QString & text, Message::Buttons buttons = Message::BUTTON_OK);

		/**
		 * Warning message. Convenient function that creates warning dialog and advertises it through Messenger instance.
		 * @param text message for the user.
		 * @param buttons message dialog buttons.
		 * @return message instance.
		 */
		static std::unique_ptr<Message> Warning(const QString & text, Message::Buttons buttons = Message::BUTTON_OK);

		/**
		 * Question. Convenient function that creates question dialog and advertises it through Messenger instance.
		 * @param text message for the user.
		 * @param buttons message dialog buttons.
		 * @return message instance.
		 */
		static std::unique_ptr<Message> Question(const QString & text, Message::Buttons buttons = Message::Buttons{Message::BUTTON_YES, Message::BUTTON_NO});

		/**
		 * Critical message. Convenient function that creates critical dialog and advertises it through Messenger instance.
		 * @param text message for the user.
		 * @param buttons message dialog buttons.
		 * @return message instance.
		 */
		static std::unique_ptr<Message> Critical(const QString & text, Message::Buttons buttons = Message::BUTTON_OK);

		/**
		* Critical message. Convenient function that creates critical dialog from ErrorInfo object and advertises it through
		* Messenger instance.
		* @param errorInfo error info object.
		* @param buttons message dialog buttons.
		* @return message instance.
		*/
		static std::unique_ptr<Message> Critical(const ErrorInfo & errorInfo, Message::Buttons buttons = Message::BUTTON_OK);

		/**
		 * Constructor.
		 * @param type dialog type.
		 * @param text message for the user.
		 * @param buttons message dialog buttons.
		 * @param parent parent object.
		 */
		explicit Message(Type type = INFO, const QString & text = QString(), Buttons buttons = Message::NO_BUTTON, QObject * parent = nullptr);

		/**
		 * Constructor.
		 * @param type dialog type.
		 * @param text message for the user.
		 * @param informativeText informative message.
		 * @param buttons message dialog buttons.
		 * @param parent parent object.
		 */
		Message(Type type, const QString & text, const QString & informativeText, Buttons buttons = Message::NO_BUTTON, QObject * parent = nullptr);

		/**
		 * Constructor.
		 * @param type dialog type.
		 * @param text message for the user.
		 * @param informativeText informative message.
		 * @param detailedText detailed message.
		 * @param buttons message dialog buttons.
		 * @param parent parent object.
		 */
		Message(Type type, const QString & text, const QString & informativeText, const QString & detailedText, Buttons buttons = Message::NO_BUTTON, QObject * parent = nullptr);

		/**
		 * Destructor.
		 */
		~Message() override = default;

		/**
		 * Get dialog type.
		 * @return dialog type.
		 */
		Type type() const;

		/**
		 * Set dialog type.
		 * @param type dialog type.
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
		 * Get message dialog buttons.
		 * @return message dialog buttons available to the user.
		 */
		Buttons buttons() const;

		/**
		 * Set buttons.
		 * @param buttons buttons that should be available to the user.
		 */
		void setButtons(Buttons buttons);

		/**
		  * Get user response.
		  * @return button that has been pressed by the user or Message::NO_BUTTON if user didn't make a choice.
		  */
		Button response() const;

		/**
		 * Clone message.
		 * @return message clone.
		 */
		std::unique_ptr<Message> clone() const;

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

		void responseArrived(cutehmi::Message::Button response);

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

Q_DECLARE_OPERATORS_FOR_FLAGS(cutehmi::Message::Buttons)

#endif

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
