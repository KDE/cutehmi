#ifndef H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_MESSENGER_HPP
#define H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_MESSENGER_HPP

#include "internal/common.hpp"
#include "Message.hpp"
#include "ExceptionMixin.hpp"
#include "Singleton.hpp"

#include <QObject>
#include <QMutexLocker>

namespace cutehmi {

/**
 * %Messenger.
 */
class CUTEHMI_API Messenger:
	public QObject,
	public Singleton<Messenger>
{
		Q_OBJECT

		friend class Singleton<Messenger>;

	public:
		/**
		 * No advertiser exception.
		 */
		class CUTEHMI_API NoAdvertiserException:
			public ExceptionMixin<NoAdvertiserException>
		{
				typedef ExceptionMixin<NoAdvertiserException> Parent;

			public:
				explicit NoAdvertiserException(Message & message);

				NoAdvertiserException(const NoAdvertiserException & other);

				NoAdvertiserException & operator =(const NoAdvertiserException & other);

				/**
				 * Recall message.
				 * @return message object.
				 */
				const Message * message() const;

			private:
				struct Members
				{
					std::unique_ptr<Message> message;
				};

				MPtr<Members> m;
		};

		/**
		 * Advertise message.
		 * @param message_l message to advertise. Parameter will be used locally by this function.
		 * It's passed by a pointer instead of a reference for easier integration with QML.
		 *
		 * @threadsafe
		 *
		 * @throw NoAdvertiserException thrown in case advertiser has not been set.
		 */
		Q_INVOKABLE void advertise(Message * message_l);

		/**
		  * Reset advertiser. Advertiser will be connected to dialogRequested() signal. There can be only one advertiser at a time.
		  * Subsequent call of this function will disconnect previous advertiser.
		  * @param advertiser advertiser object. Advertiser must implement createDialog(QVariant) slot. Parameter of type QVariant
		  * wraps `Message *` pointer.
		  */
		Q_INVOKABLE void resetAdvertiser(QObject * advertiser);

	signals:
		/**
		 * Message requested. This signal is emitted each time advertise() function has been called. This signal will trigger
		 * execution of createDialog() slot in advertiser.
		 * @param message parameter wraps `Message * pointer`. Advertiser should present adequate control to the user and provide a
		 * response by calling Message::acceptResponse() function.
		 */
		void messageRequested(QVariant message);

	protected:
		explicit Messenger(QObject * parent = nullptr);

		struct Members
		{
			QMutex requestMutex {};
			QObject * advertiser {nullptr};
		};

		MPtr<Members> m;
};

}

#endif

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
