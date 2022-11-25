#ifndef STATEINTERFACEHELPERS_HPP
#define STATEINTERFACEHELPERS_HPP

#include <cutehmi/services/internal/common.hpp>

#include <QAbstractTransition>
#include <QState>

#include <memory>
#include <array>

namespace cutehmi {
namespace services {
namespace internal {

template<std::size_t N>
QAbstractTransition * getTransition(const std::array<QAbstractTransition *, N> & transitions, int index)
{
	if (index < 0 || static_cast<std::size_t>(index) >= transitions.size()) {
		CUTEHMI_WARNING("There is no transition with index " << index << ".");
		return nullptr;
	}

	return transitions[index];
}

template<typename T>
void clearTransition(T & stateData, std::size_t index)
{
	if (stateData.transitions[index] != nullptr) {
		if (stateData.persistent)
			stateData.persistent->removeTransition(stateData.transitions[index]);
		stateData.transitions[index]->deleteLater();
		stateData.transitions[index] = nullptr;
	}
}

inline
QAbstractTransition * addServiceableTransition(QState * source, QState * target, std::unique_ptr<QAbstractTransition> serviceableTransition, bool unconditionalIfNull = false)
{
	CUTEHMI_ASSERT(source != nullptr, "source state can not be nullptr");

	QAbstractTransition * transition = nullptr;

	if (serviceableTransition) {
		transition = serviceableTransition.release();
		transition->setTargetState(target);
		source->addTransition(transition);
	} else if (unconditionalIfNull)
		transition = source->addTransition(target);

	return transition;
}

template<typename T>
void recreateState(T & stateData, const QString & ephemericName)
{
	if (stateData.ephemeric) {
		stateData.ephemeric->setParent(nullptr);
		stateData.ephemeric->deleteLater();
	}
	stateData.ephemeric = new QState(stateData.persistent);
	stateData.ephemeric->setObjectName(ephemericName);
	stateData.persistent->setInitialState(stateData.ephemeric);
}

}
}
}

#endif // STATEINTERFACEHELPERS_HPP
