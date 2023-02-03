#include <cutehmi/services/SelfService.hpp>
#include <cutehmi/services/SelfServiceAttachedType.hpp>
#include "internal/ServiceStateMachine.hpp"
#include "internal/ServiceStateInterface.hpp"

#include <QQmlContext>
#include <QtQml>

namespace cutehmi {
namespace services {

const char * SelfService::DSM_IMPORT_STATEMENT = "import QtQml.StateMachine 1.15";

SelfService::SelfService(QObject * parent):
	AbstractService(new internal::ServiceStateInterface, DefaultStatus(), parent),
	m(new Members{
	//<CuteHMI.Services-3.workaround target="Qt" cause="design">
	QStateMachine{},	// C++17 mandatory copy elision of explicit ctor call (see: https://en.cppreference.com/w/cpp/language/copy_elision).
	//</CuteHMI.Services-3.workaround>
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	QJSValue::UndefinedValue,
	QJSValue::UndefinedValue,
	QJSValue::UndefinedValue,
	QJSValue::UndefinedValue,
	QJSValue::UndefinedValue,
	false,
	{
		nullptr,
		nullptr,
		QJSValue::UndefinedValue
	}})
{
	// Service status is read-only property, thus it is updated through state interface writebale double.
	connect(stateInterface(), & internal::ServiceStateInterface::statusChanged, this, & SelfService::setStatus);
}

SelfService::~SelfService()
{
	stateInterface()->shutdown();
}

SelfServiceAttachedType * SelfService::qmlAttachedProperties(QObject * object)
{
	return new SelfServiceAttachedType(object);
}

QAbstractState * SelfService::startingState() const
{
	return m->startingState;
}

void SelfService::setStartingState(QAbstractState * startingState)
{
	if (m->startingState != startingState) {
		m->startingState = startingState;
		//<CuteHMI.Services-3.workaround target="Qt" cause="design">
		m->startingState->setParent(& m->surrogateSM);
		//</CuteHMI.Services-3.workaround>
		emit startingStateChanged();

		if (!m->qmlBeingParsed) {
			stateInterface()->reconfigureStarting(*this);
			emit initialized();
		}
	}
}

QAbstractState * SelfService::activeState() const
{
	return m->activeState;
}

void SelfService::setActiveState(QAbstractState * activeState)
{
	if (m->activeState != activeState) {
		m->activeState = activeState;
		//<CuteHMI.Services-3.workaround target="Qt" cause="design">
		m->activeState->setParent(& m->surrogateSM);
		//</CuteHMI.Services-3.workaround>
		emit activeStateChanged();

		if (!m->qmlBeingParsed) {
			stateInterface()->reconfigureStarted(*this);
			emit initialized();
		}
	}
}

QAbstractState * SelfService::stoppingState() const
{
	return m->stoppingState;
}

void SelfService::setStoppingState(QAbstractState * stoppingState)
{
	if (m->stoppingState != stoppingState) {
		m->stoppingState = stoppingState;
		//<CuteHMI.Services-3.workaround target="Qt" cause="design">
		m->stoppingState->setParent(& m->surrogateSM);
		//</CuteHMI.Services-3.workaround>
		emit stoppingStateChanged();

		if (!m->qmlBeingParsed) {
			stateInterface()->reconfigureStopping(*this);
			emit initialized();
		}
	}
}

QAbstractState * SelfService::repairingState() const
{
	return m->repairingState;
}

void SelfService::setBrokenState(QAbstractState * brokenState)
{
	if (m->brokenState != brokenState) {
		m->brokenState = brokenState;
		//<CuteHMI.Services-3.workaround target="Qt" cause="design">
		m->brokenState->setParent(& m->surrogateSM);
		//</CuteHMI.Services-3.workaround>
		emit brokenStateChanged();

		if (!m->qmlBeingParsed) {
			stateInterface()->reconfigureBroken(*this);
			emit initialized();
		}
	}
}

QAbstractState * SelfService::brokenState() const
{
	return m->brokenState;
}

void SelfService::setRepairingState(QAbstractState * repairingState)
{
	if (m->repairingState != repairingState) {
		m->repairingState = repairingState;
		//<CuteHMI.Services-3.workaround target="Qt" cause="design">
		m->repairingState->setParent(& m->surrogateSM);
		//</CuteHMI.Services-3.workaround>
		emit repairingStateChanged();

		if (!m->qmlBeingParsed) {
			stateInterface()->reconfigureRepairing(*this);
			emit initialized();
		}
	}
}

QAbstractState * SelfService::evacuatingState() const
{
	return m->evacuatingState;
}

void SelfService::setEvacuatingState(QAbstractState * evacuatingState)
{
	if (m->evacuatingState != evacuatingState) {
		m->evacuatingState = evacuatingState;
		//<CuteHMI.Services-3.workaround target="Qt" cause="design">
		m->evacuatingState->setParent(& m->surrogateSM);
		//</CuteHMI.Services-3.workaround>
		emit evacuatingStateChanged();

		if (!m->qmlBeingParsed) {
			stateInterface()->reconfigureEvacuating(*this);
			emit initialized();
		}
	}
}

QJSValue SelfService::signalToStarted() const
{
	return m->signalToStarted;
}

void SelfService::setSignalToStarted(const QJSValue & signal)
{
	if (m->signalToStarted.strictlyEquals(signal))
		return;

	m->signalToStarted = signal;

	emit signalToStartedChanged();

	if (!m->qmlBeingParsed) {
		stateInterface()->replaceTransitionToStarted(*this);
		emit initialized();
	}
}

QJSValue SelfService::signalToStopped() const
{
	return m->signalToStopped;
}

void SelfService::setSignalToStopped(const QJSValue & signal)
{
	if (m->signalToStopped.strictlyEquals(signal))
		return;

	m->signalToStopped = signal;

	emit signalToStoppedChanged();

	if (!m->qmlBeingParsed) {
		stateInterface()->replaceTransitionToStopped(*this);
		emit initialized();
	}
}

QJSValue SelfService::signalToBroken() const
{
	return m->signalToBroken;
}

void SelfService::setSignalToBroken(const QJSValue & signal)
{
	if (m->signalToBroken.strictlyEquals(signal))
		return;

	m->signalToBroken = signal;

	emit signalToBrokenChanged();

	if (!m->qmlBeingParsed) {
		stateInterface()->replaceTransitionToBroken(*this);
	}
}

QJSValue SelfService::signalToIdling() const
{
	return m->signalToIdling;
}

void SelfService::setSignalToIdling(const QJSValue & signal)
{
	if (m->signalToIdling.strictlyEquals(signal))
		return;

	m->signalToIdling = signal;

	emit signalToIdlingChanged();

	if (!m->qmlBeingParsed) {
		stateInterface()->replaceTransitionToIdling(*this);
		emit initialized();
	}
}

QJSValue SelfService::signalToYielding() const
{
	return m->signalToYielding;
}

void SelfService::setSignalToYielding(const QJSValue & signal)
{
	if (m->signalToYielding.strictlyEquals(signal))
		return;

	m->signalToYielding = signal;

	emit signalToYieldingChanged();

	if (!m->qmlBeingParsed) {
		stateInterface()->replaceTransitionToYielding(*this);
		emit initialized();
	}
}

void SelfService::configureStarting(QState * starting, AssignStatusFunction assignStatus)
{
	if (m->startingState != nullptr) {
//		QQmlEngine::setObjectOwnership(m->startingState, QQmlEngine::CppOwnership);
		m->startingState->setParent(starting);
		starting->setInitialState(m->startingState);

		// Internally this is a QState subclass - see more elaborate comment in assignStateStatuses().
		if (qobject_cast<QState *>(m->startingState))
			assignStateStatuses(*qobject_cast<QState *>(m->startingState), assignStatus);
		else
			CUTEHMI_CRITICAL("Could not cast starting state to QState!");

		// Assign the same status to the parent, wrapping state.
		SelfServiceAttachedType * soAttachedType = qobject_cast<SelfServiceAttachedType *>(qmlAttachedPropertiesObject<SelfService>(m->startingState));
		assignStateStatus(*starting, assignStatus, soAttachedType);
	}
}

void SelfService::configureStarted(QState * active, const QState * idling, const QState * yielding, AssignStatusFunction assignStatus)
{
	Q_UNUSED(idling)
	Q_UNUSED(yielding)

	if (m->activeState != nullptr) {
//		QQmlEngine::setObjectOwnership(m->activeState, QQmlEngine::CppOwnership);
		m->activeState->setParent(active);
		active->setInitialState(m->activeState);

		// Internally this is a QState subclass - see more elaborate comment in assignStateStatuses().
		if (qobject_cast<QState *>(m->activeState))
			assignStateStatuses(*qobject_cast<QState *>(m->activeState), assignStatus);
		else
			CUTEHMI_CRITICAL("Could not cast active state to QState!");

		// Assign the same status to the parent, wrapping state.
		SelfServiceAttachedType * soAttachedType = qobject_cast<SelfServiceAttachedType *>(qmlAttachedPropertiesObject<SelfService>(m->activeState));
		assignStateStatus(*active, assignStatus, soAttachedType);
	}
}

void SelfService::configureStopping(QState * stopping, AssignStatusFunction assignStatus)
{
	if (m->stoppingState != nullptr) {
//		QQmlEngine::setObjectOwnership(m->stoppingState, QQmlEngine::CppOwnership);
		m->stoppingState->setParent(stopping);
		stopping->setInitialState(m->stoppingState);

		// Internally this is a QState subclass - see more elaborate comment in assignStateStatuses().
		if (qobject_cast<QState *>(m->stoppingState))
			assignStateStatuses(*qobject_cast<QState *>(m->stoppingState), assignStatus);
		else
			CUTEHMI_CRITICAL("Could not cast stopping state to QState!");

		// Assign the same status to the parent, wrapping state.
		SelfServiceAttachedType * soAttachedType = qobject_cast<SelfServiceAttachedType *>(qmlAttachedPropertiesObject<SelfService>(m->stoppingState));
		assignStateStatus(*stopping, assignStatus, soAttachedType);
	}
}

void SelfService::configureBroken(QState * broken, AssignStatusFunction assignStatus)
{
	if (m->brokenState != nullptr) {
//		QQmlEngine::setObjectOwnership(m->brokenState, QQmlEngine::CppOwnership);
		m->brokenState->setParent(broken);
		broken->setInitialState(m->brokenState);

		// Internally this is a QState subclass - see more elaborate comment in assignStateStatuses().
		if (qobject_cast<QState *>(m->brokenState))
			assignStateStatuses(*qobject_cast<QState *>(m->brokenState), assignStatus);
		else
			CUTEHMI_CRITICAL("Could not cast broken state to QState!");

		// Assign the same status to the parent, wrapping state.
		SelfServiceAttachedType * soAttachedType = qobject_cast<SelfServiceAttachedType *>(qmlAttachedPropertiesObject<SelfService>(m->brokenState));
		assignStateStatus(*broken, assignStatus, soAttachedType);
	}
}

void SelfService::configureRepairing(QState * repairing, AssignStatusFunction assignStatus)
{
	if (m->repairingState != nullptr) {
//		QQmlEngine::setObjectOwnership(m->repairingState, QQmlEngine::CppOwnership);
		m->repairingState->setParent(repairing);
		repairing->setInitialState(m->repairingState);

		// Internally this is a QState subclass - see more elaborate comment in assignStateStatuses().
		if (qobject_cast<QState *>(m->repairingState))
			assignStateStatuses(*qobject_cast<QState *>(m->repairingState), assignStatus);
		else
			CUTEHMI_CRITICAL("Could not cast repairing state to QState!");

		// Assign the same status to the parent, wrapping state.
		SelfServiceAttachedType * soAttachedType = qobject_cast<SelfServiceAttachedType *>(qmlAttachedPropertiesObject<SelfService>(m->repairingState));
		assignStateStatus(*repairing, assignStatus, soAttachedType);
	}
}

void SelfService::configureEvacuating(QState * evacuating, AssignStatusFunction assignStatus)
{
	if (m->evacuatingState != nullptr) {
//		QQmlEngine::setObjectOwnership(m->evacuatingState, QQmlEngine::CppOwnership);
		m->evacuatingState->setParent(evacuating);
		evacuating->setInitialState(m->evacuatingState);

		// Internally this is a QState subclass - see more elaborate comment in assignStateStatuses().
		if (qobject_cast<QState *>(m->evacuatingState))
			assignStateStatuses(*qobject_cast<QState *>(m->evacuatingState), assignStatus);
		else
			CUTEHMI_CRITICAL("Could not cast evacuating state to QState!");

		// Assign the same status to the parent, wrapping state.
		SelfServiceAttachedType * soAttachedType = qobject_cast<SelfServiceAttachedType *>(qmlAttachedPropertiesObject<SelfService>(m->evacuatingState));
		assignStateStatus(*evacuating, assignStatus, soAttachedType);
	}
}

std::unique_ptr<QAbstractTransition> SelfService::transitionToStarted() const
{
	if (m->signalToStarted.isUndefined())
		return nullptr;

	std::unique_ptr<QSignalTransition> transition = std::make_unique<QSignalTransition>();

	// <CuteHMI.Services-4.workaround target="Qt" cause="missing">
	auto senderSignal = senderSignalPair(m->signalToStarted);
	transition->setSenderObject(senderSignal.first);
	transition->setSignal(senderSignal.second);
	// </CuteHMI.Services-4.workaround>

	return transition;
}

std::unique_ptr<QAbstractTransition> SelfService::transitionToStopped() const
{
	if (m->signalToStopped.isUndefined())
		return nullptr;

	std::unique_ptr<QSignalTransition> transition = std::make_unique<QSignalTransition>();

	// <CuteHMI.Services-4.workaround target="Qt" cause="missing">
	auto senderSignal = senderSignalPair(m->signalToStopped);
	transition->setSenderObject(senderSignal.first);
	transition->setSignal(senderSignal.second);
	// </CuteHMI.Services-4.workaround>

	return transition;
}

std::unique_ptr<QAbstractTransition> SelfService::transitionToBroken() const
{
	if (m->signalToBroken.isUndefined())
		return nullptr;

	std::unique_ptr<QSignalTransition> transition = std::make_unique<QSignalTransition>();

	// <CuteHMI.Services-4.workaround target="Qt" cause="missing">
	auto senderSignal = senderSignalPair(m->signalToBroken);
	transition->setSenderObject(senderSignal.first);
	transition->setSignal(senderSignal.second);
	// </CuteHMI.Services-4.workaround>

	return transition;
}

std::unique_ptr<QAbstractTransition> SelfService::transitionToYielding() const
{
	if (m->signalToYielding.isUndefined())
		return nullptr;

	std::unique_ptr<QSignalTransition> transition = std::make_unique<QSignalTransition>();

	// <CuteHMI.Services-4.workaround target="Qt" cause="missing">
	auto senderSignal = senderSignalPair(m->signalToYielding);
	transition->setSenderObject(senderSignal.first);
	transition->setSignal(senderSignal.second);
	// </CuteHMI.Services-4.workaround>

	return transition;
}

std::unique_ptr<QAbstractTransition> SelfService::transitionToIdling() const
{
	if (m->signalToIdling.isUndefined())
		return nullptr;

	std::unique_ptr<QSignalTransition> transition = std::make_unique<QSignalTransition>();

	// <CuteHMI.Services-4.workaround target="Qt" cause="missing">
	auto senderSignal = senderSignalPair(m->signalToIdling);
	transition->setSenderObject(senderSignal.first);
	transition->setSignal(senderSignal.second);
	// </CuteHMI.Services-4.workaround>

	return transition;
}

void SelfService::classBegin()
{
	m->qmlBeingParsed = true;
}

void SelfService::componentComplete()
{
	m->qmlBeingParsed = false;

	configureStateInterface();
}

QString & SelfService::DefaultStatus()
{
	static QString name = QObject::tr("Uninitialized");
	return name;
}

internal::ServiceStateInterface * SelfService::stateInterface() const
{
	return static_cast<internal::ServiceStateInterface *>(states());
}

void SelfService::assignStateStatuses(QState & state, AssignStatusFunction assignStatus)
{
	// According to [the documentation](https://doc.qt.io/qt-6/qml-qtqml-statemachine-state.html) State is a subclass of
	// QAbstractState, but it really inherits after QState (see: https://bugreports.qt.io/browse/QTBUG-107597). If it does not
	// holds true that State is a QState subclass, we could probably make each State a child of newly created QState and assign
	// status using this newly created parent QState.

	SelfServiceAttachedType * soAttachedType = qobject_cast<SelfServiceAttachedType *>(qmlAttachedPropertiesObject<SelfService>(& state));
	assignStateStatus(state, assignStatus, soAttachedType);

	for (auto && child : state.children())
		if (qobject_cast<QState *>(child))
			assignStateStatuses(*qobject_cast<QState *>(child), assignStatus);
}

void SelfService::assignStateStatus(QState & state, AssignStatusFunction assignStatus, const SelfServiceAttachedType * soAttachedType)
{
	if (soAttachedType != nullptr) {
		if (!soAttachedType->status().isNull())
			assignStatus(state, soAttachedType->status());
		connect(soAttachedType, & SelfServiceAttachedType::statusChanged, & state, [assignStatus, & state, soAttachedType]() {
			if (!soAttachedType->status().isNull())
				assignStatus(state, soAttachedType->status());
		});
	}
}

// <CuteHMI.Services-4.workaround target="Qt" cause="missing">

std::pair<const QObject *, QByteArray> SelfService::senderSignalPair(const QJSValue & qmlSignal) const
{
	if (!helperSignalTransitionJSValue().isUndefined()) {
		// Instead of dealing with Qt private API we use a helper SignalTransition object created within SelfService's QML
		// engine instance, which acts as a converter between QJSValue and QObject * sender and QByteArray signal name pair.
		helperSignalTransitionJSValue().setProperty("signal", qmlSignal);

		CUTEHMI_ASSERT(helperSignalTransition() != nullptr, "helperSignalTransition() can not be nullptr if helperSignalTransitionJSValue() is not undefined");
		return std::make_pair(helperSignalTransition()->senderObject(), helperSignalTransition()->signal());
	} else if (!helperQmlEngine())
		CUTEHMI_CRITICAL("Can not extract sender and signal pair from QJSValue if no QML engine is associated with " << this << "! You can override cutehmi::services::SelfService::senderSignalPair() function to resolve this, but consider implementing cutehmi::services::Serviceable interface instead.");
	else
		CUTEHMI_CRITICAL("Could not extract sender and signal pair from QJSValue!");

	return std::make_pair(nullptr, QByteArray());
}

QQmlEngine * SelfService::helperQmlEngine() const
{
	if (m->cache.helperQmlEngine == nullptr)
		m->cache.helperQmlEngine = qmlEngine(this);	// Try to obtain QML engine associated with SelfService instance.

	return m->cache.helperQmlEngine;
}

QSignalTransition * SelfService::helperSignalTransition() const
{
	if (m->cache.helperSignalTransition == nullptr) {
		if (helperQmlEngine()) {
			QQmlComponent component(helperQmlEngine());
			component.setData(QByteArray(DSM_IMPORT_STATEMENT).append("\nSignalTransition {}"), QUrl());
			m->cache.helperSignalTransition = qobject_cast<QSignalTransition *>(component.create());
			if (m->cache.helperSignalTransition == nullptr)
				CUTEHMI_CRITICAL("Could not create SignalTransition helper using '" << DSM_IMPORT_STATEMENT << "'! Ensure that QML module is available.");
		}
	}

	return m->cache.helperSignalTransition;
}

QJSValue SelfService::helperSignalTransitionJSValue() const
{
	if (helperSignalTransition() != nullptr && helperQmlEngine() != nullptr)
		m->cache.helperSignalTransitionJSValue = helperQmlEngine()->newQObject(helperSignalTransition());

	return m->cache.helperSignalTransitionJSValue;
}

void SelfService::configureStateInterface()
{
	stateInterface()->configureServiceable(this);
	emit initialized();
}

// </CuteHMI.Services-4.workaround>

}
}

//(c)C: Copyright © 2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
