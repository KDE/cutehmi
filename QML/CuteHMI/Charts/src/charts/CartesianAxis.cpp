#include "CartesianAxis.hpp"

namespace cutehmi {
namespace charts {

constexpr Qt::Orientation CartesianAxis::INITIAL_ORIENTATION;

CartesianAxis::CartesianAxis(QQuickItem * parent):
	ValueAxis(parent),
	m_orientation(INITIAL_ORIENTATION)
{
	connect(this, & CartesianAxis::orientationChanged, this, & QQuickItem::update);
}

Qt::Orientation CartesianAxis::orientation() const
{
	return m_orientation;
}

void CartesianAxis::setOrientation(Qt::Orientation orientation)
{
	if (m_orientation != orientation) {
		m_orientation = orientation;
		emit orientationChanged();
	}
}

}
}
