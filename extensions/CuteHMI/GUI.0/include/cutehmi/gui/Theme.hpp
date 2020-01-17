#ifndef H_EXTENSIONS_CUTEHMI_GUI_0_INCLUDE_CUTEHMI_GUI_THEME_HPP
#define H_EXTENSIONS_CUTEHMI_GUI_0_INCLUDE_CUTEHMI_GUI_THEME_HPP

#include "internal/common.hpp"
#include "Palette.hpp"

#include <QObject>

namespace cutehmi {
namespace gui {

/**
 * %Theme.
 *
 * %Theme defines palette used by CuteApplication. In future it may also cover other aspects of user interface appearance.
 */
class CUTEHMI_GUI_API Theme:
	public QObject
{
		Q_OBJECT

	public:
		Q_PROPERTY(Palette * palette READ palette WRITE setPalette NOTIFY paletteChanged RESET resetPalette)

		Theme(QObject * parent = nullptr);

		Palette * palette() const;

		void setPalette(Palette * palette);

		void resetPalette();

	signals:
		void alarmChanged();

		void paletteChanged();

	protected:
		static Palette & DefaultPalette();

	private:
		struct Members
		{
			Palette * palette;

			Members():
				palette(& DefaultPalette())
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif
