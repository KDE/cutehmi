#include "../../include/cutehmi/PopupBridge.hpp"

namespace cutehmi {

PopupBridge::NoAdvertiserException::NoAdvertiserException(Prompt & prompt):
	Parent(tr("No advertiser has been set.")),
	m(new Members{prompt.clone()})
{
}

PopupBridge::NoAdvertiserException::NoAdvertiserException(const PopupBridge::NoAdvertiserException & other):
	Parent(other),
	m(new Members{other.m->prompt->clone()})
{
}

PopupBridge::NoAdvertiserException & PopupBridge::NoAdvertiserException::operator =(const PopupBridge::NoAdvertiserException & other)
{
	Parent::operator =(other);

	// Self-assignment branch not required.
	m->prompt = other.m->prompt->clone();

	return *this;
}

const Prompt * PopupBridge::NoAdvertiserException::prompt() const
{
	return m->prompt.get();
}

PopupBridge::PopupBridge(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

void PopupBridge::advertise(Prompt * prompt_l)
{
	QMutexLocker locker(& m->requestMutex);

	if (m->advertiser == nullptr)
		throw NoAdvertiserException(*prompt_l);

	Prompt * clone = prompt_l->clone().release();

	// Forward response to the original prompt. Connection should be automatically broken if original prompt gets deleted.
	connect(clone, & Prompt::responseArrived, prompt_l, & Prompt::acceptResponse);

	// Set up clone for auto-destruction once response arrived.
	connect(clone, & Prompt::responseArrived, clone, & Prompt::deleteLater);

	emit promptRequested(QVariant::fromValue(clone));
}

void PopupBridge::resetAdvertiser(QObject * advertiser)
{
	if (m->advertiser != nullptr)
		QObject::disconnect(this, SIGNAL(promptRequested(QVariant)), m->advertiser, SLOT(createPrompt(QVariant)));
	m->advertiser = advertiser;
	QObject::connect(this, SIGNAL(promptRequested(QVariant)), advertiser, SLOT(createPrompt(QVariant)));
}

std::unique_ptr<Prompt> PopupBridge::note(const QString & text, Prompt::Buttons buttons)
{
	std::unique_ptr<Prompt> result(new Prompt(Prompt::NOTE, text, buttons));
	advertise(result.get());
	return result;
}

std::unique_ptr<Prompt> PopupBridge::warning(const QString & text, Prompt::Buttons buttons)
{
	std::unique_ptr<Prompt> result(new Prompt(Prompt::WARNING, text, buttons));
	advertise(result.get());
	return result;
}

std::unique_ptr<Prompt> PopupBridge::question(const QString & text, Prompt::Buttons buttons)
{
	std::unique_ptr<Prompt> result(new Prompt(Prompt::QUESTION, text, buttons));
	advertise(result.get());
	return result;
}

std::unique_ptr<Prompt> PopupBridge::critical(const QString & text, Prompt::Buttons buttons)
{
	std::unique_ptr<Prompt> result(new Prompt(Prompt::CRITICAL, text, buttons));
	advertise(result.get());
	return result;
}

std::unique_ptr<Prompt> PopupBridge::critical(const ErrorInfo & errorInfo, Prompt::Buttons buttons)
{
	return critical(errorInfo.toString(), buttons);
}

}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
