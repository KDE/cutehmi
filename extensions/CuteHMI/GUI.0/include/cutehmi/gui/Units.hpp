#ifndef UNIT_HPP
#define UNIT_HPP

#include "internal/common.hpp"

#include <QObject>

namespace cutehmi {
namespace gui {

class CUTEHMI_GUI_API Units:
	public QObject
{
		Q_OBJECT

	public:
		static constexpr qreal INITIAL_QUADRAT = 40.0;

		static constexpr bool INITIAL_ROUND_STROKE_WIDTH = true;

		static constexpr qreal STANDARD_STROKE_WIDTH_QUADRAT_RATIO = 40.0;

		Q_PROPERTY(qreal quadrat READ quadrat WRITE setQuadrat NOTIFY quadratChanged)

		Q_PROPERTY(qreal strokeWidth READ strokeWidth WRITE setStrokeWidth NOTIFY strokeWidthChanged)

		Q_PROPERTY(bool roundStrokeWidth READ roundStrokeWidth WRITE setRoundStrokeWidth NOTIFY roundStrokeWidthChanged)

		Units(QObject * parent = nullptr);

		qreal quadrat() const;

		void setQuadrat(qreal quadrat);

		qreal strokeWidth() const;

		void setStrokeWidth(qreal strokeWidth);

		bool roundStrokeWidth() const;

		void setRoundStrokeWidth(bool roundStrokeWidth);

	signals:
		void quadratChanged();

		void strokeWidthChanged();

		void roundStrokeWidthChanged();

	private slots:
		void strokeWidthBinding();

	private:
		void setStrokeWidth(qreal strokeWidth, bool breakBinding);

		struct Members {
			qreal quadrat;
			qreal strokeWidth;
			bool roundStrokeWidth;
			QMetaObject::Connection strokeWidthBindingConnection;
		};

		MPtr<Members> m;
};

}
}

#endif // UNIT_HPP
