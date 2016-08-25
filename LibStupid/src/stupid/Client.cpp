#include "Client.hpp"

#include <QtConcurrent>

namespace cutehmi {
namespace stupid {

Client::Client(std::unique_ptr<QSqlDatabase> db, QObject * parent):
	QObject(parent),
	m_db(std::move(db))
{
}

//Client::~Client()
//{
//	QThreadPool::globalInstance()->waitForDone();

//	for (IrDataContainer::KeysContainer::const_iterator it = m_irData.keys().begin(); it != m_irData.keys().end(); ++it)
//		delete m_irData.at(*it);
//	m_irData.clear();
//	for (RDataContainer::KeysContainer::const_iterator it = m_rData.keys().begin(); it != m_rData.keys().end(); ++it)
//		delete m_rData.at(*it);
//	m_rData.clear();
//	for (IbDataContainer::KeysContainer::const_iterator it = m_ibData.keys().begin(); it != m_ibData.keys().end(); ++it)
//		delete m_ibData.at(*it);
//	m_ibData.clear();
//	for (BDataContainer::KeysContainer::const_iterator it = m_bData.keys().begin(); it != m_bData.keys().end(); ++it)
//		delete m_bData.at(*it);
//	m_bData.clear();
//}

/**
 * Connect client to the STUPiD database.
 */
void Client::connect()
{
//	m_db.open();
}

/**
 * Disconnect client from the STUPiD database.
 */
void Client::disconnect()
{

}

}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
