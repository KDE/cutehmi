#include <cutehmi/gpio/LineConfig.hpp>

namespace cutehmi {
namespace gpio {

LineConfig::LineConfig(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

LineConfig::Direction LineConfig::direction() const
{
	return m->direction;
}

void LineConfig::setDirection(LineConfig::Direction direction)
{
	if (m->direction != direction) {
		m->direction = direction;
		emit directionChanged();
	}
}

LineConfig::ActiveState LineConfig::activeState() const
{
	return m->activeState;
}

void LineConfig::setActiveState(LineConfig::ActiveState activeState)
{
	if (m->activeState != activeState) {
		m->activeState = activeState;
		emit activeStateChanged();
	}
}

bool LineConfig::openDrain() const
{
	return m->openDrain;
}

void LineConfig::setOpenDrain(bool openDrain)
{
	if (m->openDrain != openDrain) {
		m->openDrain = openDrain;
		emit openDrainChanged();
	}
}

bool LineConfig::openSource() const
{
	return m->openSource;
}

void LineConfig::setOpenSource(bool openSource)
{
	if (m->openSource != openSource) {
		m->openSource = openSource;
		emit openSourceChanged();
	}
}

}
}
