#include <cutehmi/gui/Units.hpp>

#include <cmath>

namespace cutehmi {
namespace gui {

constexpr qreal Units::INITIAL_QUADRAT;
constexpr bool Units::INITIAL_ROUND_STROKE_WIDTH;
constexpr qreal Units::STANDARD_STROKE_WIDTH_QUADRAT_RATIO;

Units::Units(QObject * parent):
	QObject(parent),
	m(new Members{INITIAL_QUADRAT,
					INITIAL_QUADRAT / STANDARD_STROKE_WIDTH_QUADRAT_RATIO,
					INITIAL_ROUND_STROKE_WIDTH, {}})
{
	m->strokeWidthBindingConnection = connect(this, & Units::quadratChanged, this, & Units::strokeWidthBinding);
}

qreal Units::quadrat() const
{
	return m->quadrat;
}

void Units::setQuadrat(qreal quadrat)
{
	if (m->quadrat != quadrat) {
		m->quadrat = quadrat;
		emit quadratChanged();
	}
}

qreal Units::strokeWidth() const
{
	return m->strokeWidth;
}

void Units::setStrokeWidth(qreal strokeWidth)
{
	setStrokeWidth(strokeWidth, true);
}

bool Units::roundStrokeWidth() const
{
	return m->roundStrokeWidth;
}

void Units::setRoundStrokeWidth(bool roundStrokeWidth)
{
	if (m->roundStrokeWidth != roundStrokeWidth) {
		m->roundStrokeWidth = roundStrokeWidth;
		emit roundStrokeWidthChanged();
	}
}

void Units::strokeWidthBinding()
{
	setStrokeWidth(quadrat() / STANDARD_STROKE_WIDTH_QUADRAT_RATIO, false);
}

void Units::setStrokeWidth(qreal strokeWidth, bool breakBinding)
{
	if (breakBinding)
		disconnect(m->strokeWidthBindingConnection);

	if (roundStrokeWidth())
		strokeWidth = std::max(std::round(strokeWidth), 1.0);

	if (m->strokeWidth != strokeWidth) {
		m->strokeWidth = strokeWidth;
		emit strokeWidthChanged();
	}
}

}
}
