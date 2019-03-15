#ifndef H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_DIALOGIST_HPP
#define H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_DIALOGIST_HPP

#include "internal/common.hpp"
#include "Dialog.hpp"
#include "ExceptionMixin.hpp"
#include "Singleton.hpp"

#include <QObject>
#include <QMutexLocker>

namespace cutehmi {

/**
 * %Dialogist.
 */
class CUTEHMI_API Dialogist:
	public QObject,
	public Singleton<Dialogist>
{
	Q_OBJECT

	friend class Singleton<Dialogist>;

	public:
		/**
		 * No advertiser exception.
		 */
		class CUTEHMI_API NoAdvertiserException:
			public ExceptionMixin<NoAdvertiserException>
		{
			typedef ExceptionMixin<NoAdvertiserException> Parent;

			public:
				explicit NoAdvertiserException(Dialog & dialog);

				NoAdvertiserException(const NoAdvertiserException & other);

				NoAdvertiserException & operator =(const NoAdvertiserException & other);

				/**
				 * Recall dialog.
				 * @return dialog object.
				 */
				const Dialog * dialog() const;

			private:
				struct Members
				{
					std::unique_ptr<Dialog> dialog;
				};

				MPtr<Members> m;
		};

		/**
		 * Advertise dialog.
		 * @param dialog_l dialog to advertise. Parameter will be used locally by this function.
		 * It's passed by a pointer instead of a reference for easier integration with QML.
		 *
		 * @threadsafe
		 *
		 * @throw NoAdvertiserException thrown in case advertiser has not been set.
		 */
		Q_INVOKABLE void advertise(Dialog * dialog_l);

		/**
		  * Reset advertiser. Advertiser will be connected to dialogRequested() signal. There can be only one advertiser at a time.
		  * Subsequent call of this function will disconnect previous advertiser.
		  * @param advertiser advertiser object. Advertiser must implement createDialog(QVariant) slot. Parameter of type QVariant
		  * wraps `Dialog *` pointer.
		  */
		Q_INVOKABLE void resetAdvertiser(QObject * advertiser);

	signals:
		/**
		 * Dialog requested. This signal is emitted each time advertise() function has been called. This signal will trigger
		 * execution of createDialog() slot in advertiser.
		 * @param dialog parameter wraps `Dialog * pointer`. Advertiser should present adequate control to the user and provide a
		 * response by calling Dialog::acceptResponse() function.
		 */
		void dialogRequested(QVariant dialog);

	protected:
		explicit Dialogist(QObject * parent = nullptr);

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
