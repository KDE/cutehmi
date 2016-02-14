#include "RecentFiles.hpp"

namespace cutehmi {

RecentFiles::RecentFiles(const QString & id, QObject * parent, int filesNum):
	QObject(parent),
	m_id(id),
	m_filesNum(filesNum),
	m_files(m_settings.value(id).toStringList())
{
}

RecentFiles::~RecentFiles()
{
}

void RecentFiles::put(const QString & filePath)
{
	m_files.removeAll(filePath);
	m_files.prepend(filePath);
	while (m_files.count() > m_filesNum)
		m_files.removeLast();

	m_settings.setValue(m_id, m_files);
}

void RecentFiles::remove(const QString & filePath)
{
	m_files.removeOne(filePath);
	m_settings.setValue(m_id, m_files);
}

QString RecentFiles::lastDir(const QString & defaultValue) const
{
	if (m_files.isEmpty())
		return defaultValue;
	return QFileInfo(m_files.first()).dir().path();
}

bool RecentFiles::empty() const
{
	return m_files.isEmpty();
}

void RecentFiles::updateMenu(QMenu & menu)
{
	int ctr = 1;
	menu.clear();	//actions will not be accessible to other objects so they shall be deleted by QMenu
	for (QStringList::iterator i = m_files.begin(); i != m_files.end(); ++i) {
		QString text = QString("&") + QString::number(ctr) + " " + QFileInfo(*i).fileName();
		QAction * act = menu.addAction(text);
		act->setData(*i);
		connect(act, SIGNAL(triggered()), this, SLOT(actionTrigger()));
		ctr++;
	}
	if (m_files.isEmpty())
		menu.setEnabled(false);
	else
		menu.setEnabled(true);
}

void RecentFiles::actionTrigger()
{
	QAction * act = qobject_cast<QAction *>(sender());
	if (act)
		emit actionTriggered(act->data().toString());
}

}
