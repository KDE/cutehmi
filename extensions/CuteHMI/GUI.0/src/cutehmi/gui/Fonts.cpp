#include <cutehmi/gui/Fonts.hpp>

#include <QFontDatabase>

namespace cutehmi {
namespace gui {

Fonts::Fonts(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

QFont Fonts::monospace() const
{
	return m->monospace;
}

void Fonts::setMonospace(QFont monospace)
{
	if (m->monospace != monospace) {
		m->monospace = monospace;
		emit monospaceChanged();
	}
}

}
}
