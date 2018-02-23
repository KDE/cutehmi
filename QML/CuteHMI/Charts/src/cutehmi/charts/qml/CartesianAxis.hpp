#ifndef CUTEHMI_QML_CUTEHMI_CHARTS_SRC_CHARTS_CARTESIANAXIS_HPP
#define CUTEHMI_QML_CUTEHMI_CHARTS_SRC_CHARTS_CARTESIANAXIS_HPP

#include "ValueAxis.hpp"

namespace cutehmi {
namespace charts {
namespace qml {

class CartesianAxis:
		public ValueAxis
{
	Q_OBJECT

	public:
		Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation NOTIFY orientationChanged)
		Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)
		Q_PROPERTY(qreal labelOffset READ labelOffset WRITE setLabelOffset NOTIFY labelOffsetChanged)
		Q_PROPERTY(qreal labelPlacement READ labelPlacement WRITE setLabelPlacement NOTIFY labelPlacementChanged)
		Q_PROPERTY(bool orientLabel READ orientLabel WRITE setOrientLabel NOTIFY orientLabelChanged)
		Q_PROPERTY(qreal labelSpace READ labelSpace NOTIFY labelSpaceChanged)
		Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
		Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
		Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
		Q_PROPERTY(qreal thickness READ thickness WRITE setThickness NOTIFY thicknessChanged)
		Q_PROPERTY(qreal axisPosition READ axisPosition WRITE setAxisPosition NOTIFY axisPositionChanged)

		static constexpr Qt::Orientation INITIAL_ORIENTATION = Qt::Vertical;
		static const QString INITIAL_LABEL;
		static constexpr qreal INITIAL_LABEL_OFFSET = 0.0;
		static constexpr qreal INITIAL_LABEL_PLACEMENT = 1.0;
		static constexpr bool INITIAL_ORIENT_LABEL = true;
		static const QColor INITIAL_COLOR;
		static const QColor INITIAL_TEXT_COLOR;
		static const QFont INITIAL_FONT;
		static constexpr qreal INITIAL_THICKNESS = 1.0;
		static constexpr qreal INITIAL_AXIS_POSITION = 25.0;

		CartesianAxis(QQuickItem * parent = 0);

		Qt::Orientation orientation() const;

		void setOrientation(Qt::Orientation orientation);

		QString label() const;

		void setLabel(const QString & label);

		qreal labelOffset() const;

		void setLabelOffset(qreal offset);

		qreal labelPlacement() const;

		void setLabelPlacement(qreal placement);

		bool orientLabel() const;

		void setOrientLabel(bool orientLabel);

		qreal labelSpace() const;

		QColor color() const;

		void setColor(const QColor & color);

		QColor textColor() const;

		void setTextColor(const QColor & textColor);

		QFont font() const;

		void setFont(const QFont & font);

		qreal thickness() const;

		void setThickness(qreal thickness);

		qreal axisPosition() const;

		void setAxisPosition(qreal axisPosition);

	signals:
		void orientationChanged();

		void labelChanged();

		void labelOffsetChanged();

		void labelPlacementChanged();

		void orientLabelChanged();

		void labelSpaceChanged();

		void colorChanged();

		void textColorChanged();

		void fontChanged();

		void thicknessChanged();

		void axisPositionChanged();

	protected:
		void paint(QPainter * painter) override;

		/**
		 * Set label space.
		 * @param space space occupied by labels.
		 */
		void setLabelSpace(qreal space);

		void paintAxis(QPainter * painter);

		QRectF paintLabel(QPainter * painter, qreal offset);

		QRectF findLabelRect(QPainter * painter) const;

		qreal labelPaintOffset() const;

	private:
		Qt::Orientation m_orientation;
		QString m_label;
		qreal m_labelOffset;
		qreal m_labelPlacement;
		bool m_orientLabel;
		qreal m_labelSpace;
		QColor m_color;
		QColor m_textColor;
		QFont m_font;
		qreal m_thickness;
		qreal m_axisPosition;
};

}
}
}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
