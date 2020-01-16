#ifndef H_EXTENSIONS_CUTEHMI_GUI_0_INCLUDE_CUTEHMI_GUI_COLORSET_HPP
#define H_EXTENSIONS_CUTEHMI_GUI_0_INCLUDE_CUTEHMI_GUI_COLORSET_HPP

#include "internal/common.hpp"

#include <QObject>
#include <QColor>

namespace cutehmi {
namespace gui {

/**
 * Color set. Color set defines standard colors to be used by @ref Element "elements" and possibly other items.
 */
class CUTEHMI_GUI_API ColorSet:
	public QObject
{
		Q_OBJECT

	public:
		/**
		  Base color of a set. It can be used to display single-color elements over the Palette's main background (such as text).
		  As such it should be contrasting with Palette's background.
		  */
		Q_PROPERTY(QColor base READ base WRITE setBase NOTIFY baseChanged)

		/**
		  Fill color. As name suggests it can be used by components to fill their interiors. Fill color works together with stroke color.
		  Component must have a stroke contour if it uses fill color to fill its interior.
		  Either a stroke color or a fill color should be a variation of base color in order to make color set meaningful.
		  */
		Q_PROPERTY(QColor fill READ fill WRITE setFill NOTIFY fillChanged)

		/**
		  A lighter variation of fill color. It can be used to draw details of a component.
		  */
		Q_PROPERTY(QColor tint READ tint WRITE setTint NOTIFY tintChanged)

		/**
		  A darker variation of fill color. It can be used to draw details of a component.
		  */
		Q_PROPERTY(QColor shade READ shade WRITE setShade NOTIFY shadeChanged)

		/**
		  Background color. Some components may want to display a text or symbols over them. Such components shall use
		  background color to create uniform background and a contrasting foreground color to display text/symbols. Foreground
		  and background colors work in pairs; in one theme background color is a dull variation of base color, while
		  foreground color remains the same across color sets, but the other theme may choose to make foreground color
		  a variation of base color and to keep background the same.
		  */
		Q_PROPERTY(QColor background READ background WRITE setBackground NOTIFY backgroundChanged)

		/**
		  Foreground color. Some components may want to display a text or symbols over them. Such components shall use
		  background color to create uniform background and a contrasting foreground color to display text/symbols. Foreground
		  and background colors work in pairs; in one theme background color is a dull variation of base color, while
		  foreground color remains the same across color sets, but the other theme may choose to make foreground color
		  a variation of base color and keep background the same across multiple sets.
		  */
		Q_PROPERTY(QColor foreground READ foreground WRITE setForeground NOTIFY foregroundChanged)

		/**
		  Strokes. A color of contours. Stroke color should be contrasting with Palette's main background. Stroke color works together
		  with fill color. Component must have a stroke contour if it uses fill color to fill its interior.
		  Either a stroke color or a fill color should be a variation of base color in order to make color set meaningful.
		  */
		Q_PROPERTY(QColor stroke READ stroke WRITE setStroke NOTIFY strokeChanged)

		/**
		 * Constructor.
		 * @param parent parent object.
		 */
		ColorSet(QObject * parent = nullptr);

		/**
		 * Get base color.
		 * @return base color.
		 */
		QColor base() const;

		/**
		 * Set base color.
		 * @param base base color.
		 */
		void setBase(QColor base);

		/**
		 * Get fill color.
		 * @return fill color.
		 */
		QColor fill() const;

		/**
		 * Set fill color.
		 * @param base fill color.
		 */
		void setFill(QColor fill);

		/**
		 * Get tint color.
		 * @return tint color.
		 */
		QColor tint() const;

		/**
		 * Set tint color.
		 * @param tint tint color.
		 */
		void setTint(QColor tint);

		/**
		 * Get shade color.
		 * @return shade color.
		 */
		QColor shade() const;

		/**
		 * Set shade color.
		 * @param shade color.
		 */
		void setShade(QColor shade);

		/**
		 * Get background color.
		 * @return background color.
		 */
		QColor background() const;

		/**
		 * Set background color.
		 * @param background background color.
		 */
		void setBackground(QColor background);

		/**
		 * Get foreground color.
		 * @return foreground color.
		 */
		QColor foreground() const;

		/**
		 * Set foreground color.
		 * @param foreground foreground color.
		 */
		void setForeground(QColor foreground);

		/**
		 * Get stroke color.
		 * @return stroke color.
		 */
		QColor stroke() const;

		/**
		 * Set stroke color.
		 * @param stroke stroke color.
		 */
		void setStroke(QColor stroke);

	signals:
		/**
		 * this signal is emitted whenever base color changed.
		 */
		void baseChanged();

		/**
		 * this signal is emitted whenever fill color changed.
		 */
		void fillChanged();

		/**
		 * this signal is emitted whenever tint color changed.
		 */
		void tintChanged();

		/**
		 * this signal is emitted whenever shade color changed.
		 */
		void shadeChanged();

		/**
		 * this signal is emitted whenever background color changed.
		 */
		void backgroundChanged();

		/**
		 * this signal is emitted whenever foreground color changed.
		 */
		void foregroundChanged();

		/**
		 * this signal is emitted whenever stroke color changed.
		 */
		void strokeChanged();

	private:
		struct Members
		{
			QColor base;
			QColor fill;
			QColor tint;
			QColor shade;
			QColor background;
			QColor foreground;
			QColor stroke;
		};

		MPtr<Members> m;
};

}
}

#endif // COLORSET_HPP
