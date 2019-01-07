#include <cutehmi/gpio/Chip.hpp>

namespace cutehmi {
namespace gpio {

Chip::Chip(QObject * parent):
	QObject(parent),
	m(new Members(this))
{
	connect(this, & Chip::nameChanged, this, & Chip::open);
}

Chip::~Chip()
{
	close();
}

QString Chip::name() const
{
	return m->name;
}

void Chip::setName(const QString & name)
{
	if (m->name != name) {
		m->name = name;
		emit nameChanged();
	}
}

QString Chip::label() const
{
	return m->label;
}

const QQmlListProperty<Line> Chip::lines()
{
	return m->lines;
}

void Chip::open()
{
	close();
	m->chip = gpiod_chip_open_by_name(m->name.toLocal8Bit().constData());
	if (m->chip != nullptr)
		updateProperties();
	else
		CUTEHMI_WARNING("Could not open GPIO chip '" << m->name << "'.");
}

void Chip::close()
{
	clearProperties();
	if (m->chip) {
		gpiod_chip_close(m->chip);
		m->chip = nullptr;
	}
}

int Chip::LineCount(QQmlListProperty<Line> * property)
{
	return static_cast<LinesDataContainer *>(property->data)->count();
}

Line * Chip::LineAt(QQmlListProperty<Line> * property, int index)
{
	Chip * chip = static_cast<Chip *>(property->object);
	LinesDataContainer * linesData = static_cast<LinesDataContainer *>(property->data);
	if (!linesData->at(index))
		linesData->replace(index, new Line(gpiod_chip_get_line(chip->m->chip, static_cast<unsigned int>(index))));
	return linesData->at(index);
}

void Chip::setLabel(const QString & label)
{
	if (m->label != label) {
		m->label = label;
		emit labelChanged();
	}
}

void Chip::resetLineData(int lineCount)
{
	if (m->linesData.count() != lineCount) {
		for (LinesDataContainer::iterator it = m->linesData.begin(); it != m->linesData.end(); ++it)
			if (*it)
				(*it)->deleteLater();
		m->linesData.fill(nullptr, lineCount);
		emit linesChanged();
	}
}

void Chip::updateProperties()
{
	setLabel(gpiod_chip_label(m->chip));
	resetLineData(static_cast<int>(gpiod_chip_num_lines(m->chip)));
}

void Chip::clearProperties()
{
	setLabel(QString());
	resetLineData(0);
}

}
}
