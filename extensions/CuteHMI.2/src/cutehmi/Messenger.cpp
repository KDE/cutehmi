#include "../../include/cutehmi/Messenger.hpp"

namespace cutehmi {

Messenger::NoAdvertiserException::NoAdvertiserException(Message & message):
	Parent(tr("No advertiser has been set. Dialog message: ") + message.text()),
	m(new Members{message.clone()})
{
}

Messenger::NoAdvertiserException::NoAdvertiserException(const Messenger::NoAdvertiserException & other):
	Parent(other),
	m(new Members{other.m->message->clone()})
{
}

Messenger::NoAdvertiserException & Messenger::NoAdvertiserException::operator =(const Messenger::NoAdvertiserException & other)
{
	Parent::operator =(other);

	// Self-assignment branch not required.
	m->message = other.m->message->clone();

	return *this;
}

const Message * Messenger::NoAdvertiserException::message() const
{
	return m->message.get();
}

void Messenger::advertise(Message * message_l)
{
	QMutexLocker locker(& m->requestMutex);

	if (m->advertiser == nullptr)
		throw NoAdvertiserException(*message_l);

	Message * clone = message_l->clone().release();

	// Forward response to the original message. Connection should be automatically broken if message gets deleted.
	connect(clone, & Message::responseArrived, message_l, & Message::acceptResponse);

	// Set up clone for auto-destruction once response arrived.
	connect(clone, & Message::responseArrived, clone, & Message::deleteLater);

	emit messageRequested(QVariant::fromValue(clone));
}

void Messenger::resetAdvertiser(QObject * advertiser)
{
	if (m->advertiser != nullptr)
		QObject::disconnect(this, SIGNAL(messageRequested(QVariant)), m->advertiser, SLOT(createDialog(QVariant)));
	m->advertiser = advertiser;
	QObject::connect(this, SIGNAL(messageRequested(QVariant)), advertiser, SLOT(createDialog(QVariant)));
}

Messenger::Messenger(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

}

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
