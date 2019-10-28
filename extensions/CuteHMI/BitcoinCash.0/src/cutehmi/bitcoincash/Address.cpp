#include "../../../include/cutehmi/bitcoincash/Address.hpp"

#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace cutehmi {
namespace bitcoincash {

const QString Address::REQUEST_DETAILS_URL = "https://rest.bitcoin.com/v1/address/details/";

Address::Address(QObject * parent):
	QObject(parent),
	m(new Members)
{
	connect(& m->networkAccessManager, & QNetworkAccessManager::finished, this, & Address::onNetworkAccessManagerFinished);
	connect(this, & Address::addressChanged, this, & Address::update);
}

QString Address::address() const
{
	return m->address;
}

void Address::setAddress(const QString & address)
{
	if (m->address != address) {
		m->address = address;
		emit addressChanged();
	}
}

bool Address::updated() const
{
	return m->updated;
}

double Address::balance() const
{
	return m->balance;
}

double Address::totalReceived() const
{
	return m->totalReceived;
}

double Address::totalSent() const
{
	return m->totalSent;
}

double Address::unconfirmedBalance() const
{
	return m->unconfirmedBalance;
}

int Address::unconfirmedTxApperances() const
{
	return m->unconfirmedTxAppearances;
}

int Address::txAppearances() const
{
	return m->txAppearances;
}

QStringList Address::transactions() const
{
	return m->transactions;
}

QString Address::legacyAddress() const
{
	return m->legacyAddress;
}

QString Address::cashAddress() const
{
	return m->cashAddress;
}

double Address::zeroConfReceived() const
{
	return m->zeroConfReceived;
}

void Address::update()
{
	m->networkAccessManager.get(QNetworkRequest(QUrl(REQUEST_DETAILS_URL + address())));
}

void Address::setUpdated(bool updated)
{
	if (m->updated != updated) {
		m->updated = updated;
		emit updatedChanged();
	}
}

void Address::setBalance(double balance)
{
	if (m->balance != balance) {
		m->balance = balance;
		emit balanceChanged();
	}
}

void Address::setTotalReceived(double totalReceived)
{
	if (m->totalReceived != totalReceived) {
		m->totalReceived = totalReceived;
		emit totalReceivedChanged();
	}
}

void Address::setTotalSent(double totalSent)
{
	if (m->totalSent != totalSent) {
		m->totalSent = totalSent;
		emit totalSentChanged();
	}
}

void Address::setUnconfirmedBalance(double unconfirmedBalance)
{
	if (m->unconfirmedBalance != unconfirmedBalance) {
		m->unconfirmedBalance = unconfirmedBalance;
		emit unconfirmedBalanceChanged();
	}
}

void Address::setUnconfirmedTxAppearances(int unconfirmedTxAppearances)
{
	if (m->unconfirmedTxAppearances != unconfirmedTxAppearances) {
		m->unconfirmedTxAppearances = unconfirmedTxAppearances;
		emit unconfirmedTxAppearancesChanged();
	}
}

void Address::setTxAppearances(int txAppearances)
{
	if (m->txAppearances != txAppearances) {
		m->txAppearances = txAppearances;
		emit txAppearancesChanged();
	}
}

void Address::setTransactions(const QStringList & transactions)
{
	if (m->transactions != transactions) {
		m->transactions = transactions;
		emit transactionsChanged();
	}
}

void Address::setLegacyAddress(const QString & legacyAddess)
{
	if (m->legacyAddress != legacyAddess) {
		m->legacyAddress = legacyAddess;
		emit legacyAddressChanged();
	}
}

void Address::setCashAddress(const QString & cashAddress)
{
	if (m->cashAddress != cashAddress) {
		m->cashAddress = cashAddress;
		emit cashAddressChanged();
	}
}

void Address::setZeroConfReceived(double zeroConfReceived)
{
	if (m->zeroConfReceived != zeroConfReceived) {
		m->zeroConfReceived = zeroConfReceived;
		emit zeroConfReceivedChanged();
	}
}

void Address::onNetworkAccessManagerFinished(QNetworkReply * reply)
{
	if (reply->error() == QNetworkReply::NoError) {
		QJsonDocument jsonReply = QJsonDocument::fromJson(reply->readAll());
		if (!jsonReply.isNull() || !jsonReply.isObject()) {
			try {
				typedef QList<const char *> KeysContainer;

				QJsonObject json = jsonReply.object();

				// Check if keys exist.
				KeysContainer keys = {
					"balance",
					"totalReceived",
					"totalSent",
					"unconfirmedBalance",
					"unconfirmedTxApperances",	// AppErances (sic!).
					"txApperances",				// AppErances (sic!).
					"transactions",
					"legacyAddress",
					"cashAddress"
				};
				for (KeysContainer::const_iterator it = keys.begin(); it != keys.end(); ++it)
					if (!json.contains(*it))
						throw std::runtime_error(*it);

				setBalance(json["balance"].toDouble());
				setTotalReceived(json["totalReceived"].toDouble());
				setTotalSent(json["totalSent"].toDouble());
				setUnconfirmedBalance(json["unconfirmedBalance"].toDouble());
				setUnconfirmedTxAppearances(json["unconfirmedTxApperances"].toInt()); // AppErances (sic!).
				setTxAppearances(json["txApperances"].toInt());	// AppErances (sic!).

				QJsonArray transactions = json["transactions"].toArray();
				QStringList transactionsList;
				for (QJsonArray::const_iterator it = transactions.begin(); it != transactions.end(); ++it)
					transactionsList.append(it->toString());
				setTransactions(transactionsList);

				setLegacyAddress(json["legacyAddress"].toString());
				setCashAddress(json["cashAddress"].toString());

				setZeroConfReceived(totalReceived() + (unconfirmedBalance() > 0.0 ? unconfirmedBalance() : 0.0));

				setUpdated(true);
			} catch (const std::runtime_error & e) {
				CUTEHMI_CRITICAL("Could not find '" << e.what() << "' key in JSON reply.");
				setUpdated(false);
			}
		} else {
			CUTEHMI_WARNING("Could not parse nework reply in JSON format.");
			setUpdated(false);
		}
	} else {
		CUTEHMI_WARNING("Netowrk request for URL '" << reply->request().url().toString() << "' has failed. " << reply->errorString() << ".");
		setUpdated(false);
	}
	reply->deleteLater();
	emit updateFinished();
}

}
}

//(c)C: Copyright © 2019, Michal Policht <michal@policht.pl>, CuteBOT <michpolicht@gmail.com>, Michal Policht <michpolicht@gmail.com>, Mr CuteBOT <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
