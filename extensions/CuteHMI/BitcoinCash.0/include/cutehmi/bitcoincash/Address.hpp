#ifndef H_EXTENSIONS_CUTEHMI_BITCOINCASH_0_INCLUDE_CUTEHMI_BITCOINCASH_ADDRESS_HPP
#define H_EXTENSIONS_CUTEHMI_BITCOINCASH_0_INCLUDE_CUTEHMI_BITCOINCASH_ADDRESS_HPP

#include "internal/common.hpp"

#include <QNetworkAccessManager>
#include <QStringList>
#include <QObject>

class QNetworkReply;

namespace cutehmi {
namespace bitcoincash {

/**
 * Bitcoin cash address.
 */
class CUTEHMI_BITCOINCASH_API Address:
	public QObject
{
	Q_OBJECT

	friend class test_Address;

	public:
		Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
		Q_PROPERTY(bool updated READ updated NOTIFY updatedChanged)
		Q_PROPERTY(double balance READ balance NOTIFY balanceChanged)
		Q_PROPERTY(double totalReceived READ totalReceived NOTIFY totalReceivedChanged)
		Q_PROPERTY(double totalSent READ totalSent NOTIFY totalSentChanged)
		Q_PROPERTY(double unconfirmedBalance READ unconfirmedBalance NOTIFY unconfirmedBalanceChanged)
		Q_PROPERTY(int unconfirmedTxApperances READ unconfirmedTxApperances NOTIFY unconfirmedTxAppearancesChanged)
		Q_PROPERTY(int txAppearances READ txAppearances NOTIFY txAppearancesChanged)
		Q_PROPERTY(QStringList transactions READ transactions NOTIFY transactionsChanged)
		Q_PROPERTY(QString legacyAddress READ legacyAddress NOTIFY legacyAddressChanged)
		Q_PROPERTY(QString cashAddress READ cashAddress NOTIFY cashAddressChanged)
		Q_PROPERTY(double zeroConfReceived READ zeroConfReceived WRITE setZeroConfReceived NOTIFY zeroConfReceivedChanged)

		static const QString REQUEST_DETAILS_URL;

		explicit Address(QObject * parent = nullptr);

		QString address() const;

		void setAddress(const QString & address);

		bool updated() const;

		double balance() const;

		double totalReceived() const;

		double totalSent() const;

		double unconfirmedBalance() const;

		int unconfirmedTxApperances() const;

		int txAppearances() const;

		QStringList transactions() const;

		QString legacyAddress() const;

		QString cashAddress() const;

		double zeroConfReceived() const;

	public slots:
		void update();

	protected:
		void setUpdated(bool updated);

		void setBalance(double balance);

		void setTotalReceived(double totalReceived);

		void setTotalSent(double totalSent);

		void setUnconfirmedBalance(double unconfirmedBalance);

		void setUnconfirmedTxAppearances(int unconfirmedTxAppearances);

		void setTxAppearances(int txAppearances);

		void setTransactions(const QStringList & transactions);

		void setLegacyAddress(const QString & legacyAddess);

		void setCashAddress(const QString & cashAddress);

		void setZeroConfReceived(double zeroConfReceived);

	signals:
		void updateFinished();

		void addressChanged();

		void updatedChanged();

		void balanceChanged();

		void totalReceivedChanged();

		void totalSentChanged();

		void unconfirmedBalanceChanged();

		void unconfirmedTxAppearancesChanged();

		void txAppearancesChanged();

		void transactionsChanged();

		void legacyAddressChanged();

		void cashAddressChanged();

		void zeroConfReceivedChanged();

	private slots:
		void onNetworkAccessManagerFinished(QNetworkReply * reply);

	private:
		struct Members {
			QString address;
			bool updated = false;
			double totalReceived = 0.0;
			double totalSent = 0.0;
			double balance = 0.0;
			double unconfirmedBalance = 0.0;
			int unconfirmedTxAppearances = 0;
			int txAppearances = 0;
			QStringList transactions;
			QString legacyAddress;
			QString cashAddress;
			double zeroConfReceived = 0.0;
			QNetworkAccessManager networkAccessManager;
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
