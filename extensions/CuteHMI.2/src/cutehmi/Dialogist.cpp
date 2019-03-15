#include "../../include/cutehmi/Dialogist.hpp"

namespace cutehmi {

Dialogist::NoAdvertiserException::NoAdvertiserException(Dialog & dialog):
	Parent(tr("No advertiser has been set. Dialog message: ") + dialog.text()),
	m(new Members{dialog.clone()})
{
}

Dialogist::NoAdvertiserException::NoAdvertiserException(const Dialogist::NoAdvertiserException & other):
	Parent(other),
	m(new Members{other.m->dialog->clone()})
{
}

Dialogist::NoAdvertiserException & Dialogist::NoAdvertiserException::operator =(const Dialogist::NoAdvertiserException & other)
{
	Parent::operator =(other);

	// Self-assignment branch not required.
	m->dialog = other.m->dialog->clone();

	return *this;
}

const Dialog * Dialogist::NoAdvertiserException::dialog() const
{
	return m->dialog.get();
}

void Dialogist::advertise(Dialog * dialog_l)
{
	QMutexLocker locker(& m->requestMutex);

	if (m->advertiser == nullptr)
		throw NoAdvertiserException(*dialog_l);

	Dialog * clone = dialog_l->clone().release();

	// Forward response to the original dialog. Connection should be automatically broken if dialog gets deleted.
	connect(clone, & Dialog::responseArrived, dialog_l, & Dialog::acceptResponse);

	// Set up clone for auto-destruction once response arrived.
	connect(clone, & Dialog::responseArrived, clone, & Dialog::deleteLater);

	emit dialogRequested(QVariant::fromValue(clone));
}

void Dialogist::resetAdvertiser(QObject * advertiser)
{
	if (m->advertiser != nullptr)
		QObject::disconnect(this, SIGNAL(dialogRequested(QVariant)), m->advertiser, SLOT(createDialog(QVariant)));
	m->advertiser = advertiser;
	QObject::connect(this, SIGNAL(dialogRequested(QVariant)), advertiser, SLOT(createDialog(QVariant)));
}

Dialogist::Dialogist(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

}

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
