#include "../../include/cutehmi/PopupBridge.hpp"

namespace cutehmi {

PopupBridge::PopupBridge(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

void PopupBridge::advertise(Prompt * prompt_l)
{
	QMutexLocker locker(& m->requestMutex);

	if (m->advertiser == nullptr) {
		CUTEHMI_LOG_CRITICAL("No advertiser has been set. Forcing 'Prompt::NO_BUTTON' response.");
		prompt_l->acceptResponse(Prompt::NO_BUTTON);
		return;
	}

	Prompt * clone = prompt_l->clone().release();

	// Forward response to the original prompt. Connection should be automatically broken if original prompt gets deleted.
	connect(clone, & Prompt::responseArrived, prompt_l, & Prompt::acceptResponse);

	// Set up clone for auto-destruction once response arrived.
	connect(clone, & Prompt::responseArrived, clone, & Prompt::deleteLater);

	emit promptRequested(QVariant::fromValue(clone));
}

void PopupBridge::resetAdvertiser(QObject * advertiser)
{
	m->advertiser = advertiser;
	QObject::connect(this, SIGNAL(promptRequested(QVariant)), advertiser, SLOT(createPrompt(QVariant)));
}

}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
