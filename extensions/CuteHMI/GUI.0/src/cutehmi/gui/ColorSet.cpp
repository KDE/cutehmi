#include <cutehmi/gui/ColorSet.hpp>

namespace cutehmi {
namespace gui {

ColorSet::ColorSet(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

QColor ColorSet::base() const
{
	return m->base;
}

void ColorSet::setBase(QColor base)
{
	if (m->base != base) {
		m->base = base;
		emit baseChanged();
	}
}

QColor ColorSet::fill() const
{
	return m->fill;
}

void ColorSet::setFill(QColor fill)
{
	if (m->fill != fill) {
		m->fill = fill;
		emit fillChanged();
	}
}

QColor ColorSet::tint() const
{
	return m->tint;
}

void ColorSet::setTint(QColor tint)
{
	if (m->tint != tint) {
		m->tint = tint;
		emit tintChanged();
	}
}

QColor ColorSet::shade() const
{
	return m->shade;
}

void ColorSet::setShade(QColor shade)
{
	if (m->shade != shade) {
		m->shade = shade;
		emit shadeChanged();
	}
}

QColor ColorSet::background() const
{
	return m->background;
}

void ColorSet::setBackground(QColor background)
{
	if (m->background != background) {
		m->background = background;
		emit backgroundChanged();
	}
}

QColor ColorSet::foreground() const
{
	return m->foreground;
}

void ColorSet::setForeground(QColor foreground)
{
	if (m->foreground != foreground) {
		m->foreground = foreground;
		emit foregroundChanged();
	}
}

QColor ColorSet::stroke() const
{
	return m->stroke;
}

void ColorSet::setStroke(QColor stroke)
{
	if (m->stroke != stroke) {
		m->stroke = stroke;
		emit strokeChanged();
	}
}

}
}
