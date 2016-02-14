#ifndef CUTEHMI_APPFULL_SRC_RECENTFILES_HPP
#define CUTEHMI_APPFULL_SRC_RECENTFILES_HPP

#include "Settings.hpp"

#include <QStringList>
#include <QDir>
#include <QMenu>

namespace cutehmi {

class RecentFiles:
	public QObject
{
	Q_OBJECT

	public:
		static const int INITIAL_FILES_NUM = 15;

	public:
		RecentFiles(const QString & id, QObject * parent = 0, int filesNum = INITIAL_FILES_NUM);

		virtual ~RecentFiles();

	signals:
		void actionTriggered(const QString & filePath);

	public:
		void put(const QString & filePath);

		void remove(const QString & filePath);

		QString lastDir(const QString & defaultValue = QDir::currentPath()) const;

		bool empty() const;

		void updateMenu(QMenu & menu);

	private slots:
		void actionTrigger();

	private:
		const QString m_id;
		int m_filesNum;
		Settings m_settings;
		QStringList m_files;
};

}

#endif
