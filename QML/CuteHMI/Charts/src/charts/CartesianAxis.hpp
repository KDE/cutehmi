#ifndef CARTESIANAXIS_H
#define CARTESIANAXIS_H

#include "ValueAxis.hpp"

namespace cutehmi {
namespace charts {

class CartesianAxis:
		public ValueAxis
{
	Q_OBJECT

	public:
		static constexpr Qt::Orientation INITIAL_ORIENTATION = Qt::Vertical;

		Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation NOTIFY orientationChanged)

		CartesianAxis(QQuickItem * parent = 0);

		Qt::Orientation orientation() const;

		void setOrientation(Qt::Orientation orientation);

	signals:
		void orientationChanged();

	private:
		Qt::Orientation m_orientation;
};

}
}

#endif // CARTESIANAXIS_H
