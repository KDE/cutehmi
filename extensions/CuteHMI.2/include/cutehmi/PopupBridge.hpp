#ifndef H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_POPUPBRIDGE_HPP
#define H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_POPUPBRIDGE_HPP

#include "internal/common.hpp"
#include "Prompt.hpp"
#include "ExceptionMixin.hpp"

#include <QObject>
#include <QMutexLocker>

namespace cutehmi {

/**
 * %Popup bridge.
 */
class CUTEHMI_API PopupBridge:
	public QObject
{
	Q_OBJECT

	public:
		/**
		 * No advertiser exception.
		 */
		class CUTEHMI_API NoAdvertiserException:
			public ExceptionMixin<NoAdvertiserException>
		{
			typedef ExceptionMixin<NoAdvertiserException> Parent;

			public:
				explicit NoAdvertiserException(Prompt & prompt);

				NoAdvertiserException(const NoAdvertiserException & other);

				NoAdvertiserException & operator =(const NoAdvertiserException & other);

				/**
				 * Recall prompt.
				 * @return prompt object.
				 */
				const Prompt * prompt() const;

			private:
				struct Members
				{
					std::unique_ptr<Prompt> prompt;
				};

				MPtr<Members> m;
		};

		explicit PopupBridge(QObject * parent = nullptr);

		/**
		 * Advertise prompt.
		 * @param prompt_l prompt to advertise. Parameter will be used locally by this function.
		 * It's passed by a pointer instead of a reference for easier integration with QML.
		 *
		 * @threadsafe
		 *
		 * @throw NoAdvertiserException thrown in case advertiser has not been set.
		 */
		Q_INVOKABLE void advertise(Prompt * prompt_l);

		/**
		  * Reset advertiser. Advertiser will be connected to promptRequested() signal. There can be only one advertiser at a time.
		  * Subsequent call of this function will disconnect previous advertiser.
		  * @param advertiser advertiser object. Advertiser must implement createPrompt(QVariant) slot. Parameter of type QVariant
		  * wraps `Prompt *` pointer.
		  */
		Q_INVOKABLE void resetAdvertiser(QObject * advertiser);

		/**
		 * Notice message. Convenient function that creates informative prompt.
		 * @param text message for the user.
		 * @param buttons prompt buttons.
		 * @return prompt.
		 */
		std::unique_ptr<Prompt> note(const QString & text, Prompt::Buttons buttons = Prompt::BUTTON_OK);

		/**
		 * Warning message. Convenient function that creates warning prompt.
		 * @param text message for the user.
		 * @param buttons prompt buttons.
		 * @return prompt.
		 */
		std::unique_ptr<Prompt> warning(const QString & text, Prompt::Buttons buttons = Prompt::BUTTON_OK);

		/**
		 * Question. Convenient function that creates question prompt.
		 * @param text message for the user.
		 * @param buttons prompt buttons.
		 * @return prompt.
		 */
		std::unique_ptr<Prompt> question(const QString & text, Prompt::Buttons buttons = Prompt::Buttons{Prompt::BUTTON_YES, Prompt::BUTTON_NO});

		/**
		 * Critical message. Convenient function that creates critical prompt.
		 * @param text message for the user.
		 * @param buttons prompt buttons.
		 * @return prompt.
		 */
		std::unique_ptr<Prompt> critical(const QString & text, Prompt::Buttons buttons = Prompt::BUTTON_OK);

		/**
		* Critical message. Convenient function that creates critical prompt from ErrorInfo object.
		* @param errorInfo error info object.
		* @param buttons prompt buttons.
		* @return prompt.
		*/
		std::unique_ptr<Prompt> critical(const ErrorInfo & errorInfo, Prompt::Buttons buttons = Prompt::BUTTON_OK);

	signals:
		/**
		 * Prompt requested. This signal is emitted each time advertise() function has been called. This signal will trigger
		 * execution of createPrompt() slot in advertiser.
		 * @param prompt parameter wraps `Prompt * pointer`. Advertiser should present adequate control to the user and provide a
		 * response by calling Prompt::acceptResponse() function.
		 */
		void promptRequested(QVariant prompt);

	private:
		struct Members
		{
			QMutex requestMutex {};
			QObject * advertiser {nullptr};
		};

		MPtr<Members> m;
};

}

#endif

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
