#include <cutehmi/gui/Theme.hpp>

namespace cutehmi {
namespace gui {

Theme::Theme(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

Palette * Theme::palette() const
{
	return m->palette;
}

void Theme::setPalette(Palette * palette)
{
	if (m->palette != palette) {
		m->palette = palette;
		emit paletteChanged();
	}
}

void Theme::resetPalette()
{
	m->palette = & DefaultPalette();
}

Palette & Theme::DefaultPalette()
{
	static Palette palette;
	static ColorSet alarm;
	static ColorSet warning;
	static ColorSet active;
	static ColorSet inactive;
	static ColorSet neutral;

	palette.setBackground("white");

	alarm.setBase("#FF3300");
	alarm.setFill(alarm.base());
	alarm.setTint("#FF4B1D");
	alarm.setShade(alarm.base().darker());
	alarm.setForeground("black");
	alarm.setBackground(alarm.tint());
	alarm.setStroke("black");
	palette.setAlarm(& alarm);

	warning.setBase("#FF9933");
	warning.setFill(warning.base());
	warning.setTint("#FFA64D");
	warning.setShade(warning.base().darker());
	warning.setForeground("black");
	warning.setBackground(warning.tint());
	warning.setStroke("black");
	palette.setWarning(& warning);

	active.setBase("#66CC33");
	active.setFill(active.base());
	active.setTint("#CCF4CC");
	active.setShade(active.base().darker());
	active.setForeground("black");
	active.setBackground(active.tint());
	active.setStroke("black");
	palette.setActive(& active);

	inactive.setBase("#CECECE");
	inactive.setFill(inactive.base());
	inactive.setTint("#E3E3E3");
	inactive.setShade(inactive.base().darker());
	inactive.setForeground("black");
	inactive.setBackground(inactive.tint());
	inactive.setStroke("black");
	palette.setInactive(& inactive);

	neutral.setBase("black");
	neutral.setFill("white");
	neutral.setTint(neutral.base().lighter());
	neutral.setShade(neutral.base().darker());
	neutral.setForeground("black");
	neutral.setBackground("white");
	neutral.setStroke("black");
	palette.setNeutral(& neutral);

	return palette;
}

}
}
