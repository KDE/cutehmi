#include <cutehmi/gui/Palette.hpp>

namespace cutehmi {
namespace gui {

Palette::Palette(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

QColor Palette::background() const
{
	return m->background;
}

void Palette::setBackground(QColor background)
{
	if (m->background != background) {
		m->background = background;
		emit backgroundChanged();
	}
}

ColorSet * Palette::alarm() const
{
	return m->alarm;
}

void Palette::setAlarm(ColorSet * alarm)
{
	if (m->alarm != alarm) {
		m->alarm = alarm;
		emit alarmChanged();
	}
}

ColorSet * Palette::warning() const
{
	return m->warning;
}

void Palette::setWarning(ColorSet * warning)
{
	if (m->warning != warning) {
		m->warning = warning;
		emit warningChanged();
	}
}

ColorSet * Palette::active() const
{
	return m->active;
}

void Palette::setActive(ColorSet * active)
{
	if (m->active != active) {
		m->active = active;
		emit activeChanged();
	}
}

ColorSet * Palette::inactive() const
{
	return m->inactive;
}

void Palette::setInactive(ColorSet * inactive)
{
	if (m->inactive != inactive) {
		m->inactive = inactive;
		emit inactiveChanged();
	}
}

ColorSet * Palette::neutral() const
{
	return m->neutral;
}

void Palette::setNeutral(ColorSet * neutral)
{
	if (m->neutral != neutral) {
		m->neutral = neutral;
		emit neutralChanged();
	}
}

}
}
