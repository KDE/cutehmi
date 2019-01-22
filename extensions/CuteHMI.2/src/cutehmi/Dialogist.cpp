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

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
