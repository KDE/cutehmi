#ifndef TICKEDAXIS_H
#define TICKEDAXIS_H

#include "CartesianAxis.hpp"

#include <QColor>
#include <QFont>

#include <functional>
#include <array>

namespace cutehmi {
namespace charts {

class TickedAxis:
		public CartesianAxis
{
	Q_OBJECT

	public:
		Q_PROPERTY(qreal tickLabelOffset READ tickLabelOffset WRITE setTickLabelOffset NOTIFY tickLabelOffsetChanged)
		Q_PROPERTY(qreal tickLabelSpace READ tickLabelSpace NOTIFY tickLabelSpaceChanged)
//		Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
//		Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
//		Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
//		Q_PROPERTY(qreal thickness READ thickness WRITE setThickness NOTIFY thicknessChanged)
//		Q_PROPERTY(qreal axisPosition READ axisPosition WRITE setAxisPosition NOTIFY axisPositionChanged)
		Q_PROPERTY(bool bounds READ bounds WRITE setBounds NOTIFY boundsChanged)
		Q_PROPERTY(bool ticks READ ticks WRITE setTicks NOTIFY ticksChanged)
		Q_PROPERTY(bool minorTicks READ minorTicks WRITE setMinorTicks NOTIFY minorTicksChanged)

		static constexpr qreal INITIAL_TICK_LABEL_OFFSET = 5.0;
//		static const QColor INITIAL_COLOR;
//		static const QColor INITIAL_TEXT_COLOR;
//		static const QFont INITIAL_FONT;
//		static constexpr qreal INITIAL_THICKNESS = 1.0;
//		static constexpr qreal INITIAL_AXIS_POSITION = 25.0;
		static constexpr bool INITIAL_BOUNDS = true;
		static constexpr bool INITIAL_TICKS = true;
		static constexpr bool INITIAL_MINOR_TICKS = false;

		TickedAxis(QQuickItem * parent = 0);

		qreal tickLabelOffset() const;

		void setTickLabelOffset(qreal offset);

		qreal tickLabelSpace() const;

//		QColor color() const;

//		void setColor(const QColor & color);

//		QColor textColor() const;

//		void setTextColor(const QColor & textColor);

//		QFont font() const;

//		void setFont(const QFont & font);

//		qreal thickness() const;

//		void setThickness(qreal thickness);

//		qreal axisPosition() const;

//		void setAxisPosition(qreal axisPosition);

		bool bounds() const;

		void setBounds(bool bounds);

		bool ticks() const;

		void setTicks(bool ticks);

		bool minorTicks() const;

		void setMinorTicks(bool minorTicks);

		void paint(QPainter * painter) override;

	signals:
		void tickLabelOffsetChanged();

		void tickLabelSpaceChanged();

//		void colorChanged();

//		void textColorChanged();

//		void fontChanged();

//		void thicknessChanged();

//		void axisPositionChanged();

		void boundsChanged();

		void ticksChanged();

		void minorTicksChanged();

	protected:
		/**
		 * Walk ticks.
		 * @param callback callback function. Implementation should call a callback function for each @a tick.
		 */
		virtual void walkTicks(std::function<void (qreal tick)> callback) const = 0;

		/**
		 * Walk minor ticks.
		 * @param callback callback function. Implementation should call a callback function for each minor @a tick.
		 */
		virtual void walkMinorTicks(std::function<void (qreal tick)> callback) const = 0;

		/**
		 * Walk labels.
		 * @param callback callback function. Implementation should call a callback function for each @a labelPos position.
		 */
		virtual void walkTickLabels(std::function<void (qreal labelPos)> callback) const = 0;

		/**
		 * Convert tick to string.
		 * @return string representation of a tick.
		 */
		virtual QString tickToString(qreal tick) const = 0;

		/**
		 * Convert bound to string. Default implementation calls tickToString().
		 * @return string representation of a bound.
		 */
		virtual QString boundToString(qreal bound) const;

		/**
		 * Set tick label space.
		 * @param space space occupied by tick labels.
		 */
		void setTickLabelSpace(qreal space);

		qreal tickLabelPaintOffset() const;

	private:
		void paintTicks(QPainter * painter);

		void paintMinorTicks(QPainter * painter);

		void paintTickLabels(QPainter * painter, const QRectF & labelRect = QRectF());

		QRectF paintTickLabel(QPainter * painter, const QString & label, qreal pos, qreal displacement, const std::array<QRectF, 3> & rects);

		QRectF findMaxTickLabelRect(QPainter * painter) const;

		qreal m_tickLabelOffset;
		qreal m_tickLabelSpace;
//		QColor m_color;
//		QColor m_textColor;
//		QFont m_font;
//		qreal m_thickness;
//		qreal m_axisPosition;
		bool m_bounds;
		bool m_ticks;
		bool m_minorTicks;
};

}
}

#endif // LABELEDAXIS_H
