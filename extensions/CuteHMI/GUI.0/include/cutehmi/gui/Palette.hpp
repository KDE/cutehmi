#ifndef H_EXTENSIONS_CUTEHMI_GUI_0_INCLUDE_CUTEHMI_GUI_PALETTE_HPP
#define H_EXTENSIONS_CUTEHMI_GUI_0_INCLUDE_CUTEHMI_GUI_PALETTE_HPP

#include "internal/common.hpp"
#include "ColorSet.hpp"

#include <QObject>

namespace cutehmi {
namespace gui {

/**
 * %Palette.
 *
 * %Palette defines standard color sets to be used by various user interface items. For example @ref Element "elements" are using
 * color codes to signal specific states of an equipment, such as "active", warning", "alarm" or "inactive". For each such state a
 * separate ColorSet is prvided by Palette object.
 */
class CUTEHMI_GUI_API Palette:
	public QObject
{
		Q_OBJECT

	public:
		/**
		  Background color.
		  */
		Q_PROPERTY(QColor background READ background WRITE setBackground NOTIFY backgroundChanged)

		/**
		  Alarm items color set.
		  */
		Q_PROPERTY(ColorSet * alarm READ alarm WRITE setAlarm NOTIFY alarmChanged)

		/**
		  Warning items color set.
		  */
		Q_PROPERTY(ColorSet * warning READ warning WRITE setWarning NOTIFY warningChanged)

		/**
		  Active items color set.
		  */
		Q_PROPERTY(ColorSet * active READ active WRITE setActive NOTIFY activeChanged)

		/**
		  Inactive items color set.
		  */
		Q_PROPERTY(ColorSet * inactive READ inactive WRITE setInactive NOTIFY inactiveChanged)

		/**
		  Neutral color set. Neutral color set is for items that do not distinguish between active and inactive states.
		  */
		Q_PROPERTY(ColorSet  * neutral READ neutral WRITE setNeutral NOTIFY neutralChanged)

		Palette(QObject * parent = nullptr);

		QColor background() const;

		void setBackground(QColor background);

		ColorSet * alarm() const;

		void setAlarm(ColorSet * alarm);

		ColorSet * warning() const;

		void setWarning(ColorSet * warning);

		ColorSet * active() const;

		void setActive(ColorSet * active);

		ColorSet * inactive() const;

		void setInactive(ColorSet * inactive);

		ColorSet * neutral() const;

		void setNeutral(ColorSet * neutral);

	signals:
		void backgroundChanged();

		void alarmChanged();

		void warningChanged();

		void activeChanged();

		void inactiveChanged();

		void neutralChanged();

	private:
		struct Members
		{
			QColor background;
			ColorSet * alarm;
			ColorSet * warning;
			ColorSet * active;
			ColorSet * inactive;
			ColorSet * neutral;

			Members():
				alarm(nullptr),
				warning(nullptr),
				active(nullptr),
				inactive(nullptr),
				neutral(nullptr)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif // PALETTE_HPP
