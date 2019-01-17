#ifndef H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_NOTIFICATION_HPP
#define H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_NOTIFICATION_HPP

#include "internal/platform.hpp"
#include "ErrorInfo.hpp"
#include "MPtr.hpp"

#include <QObject>
#include <QDateTime>

namespace cutehmi {

/**
 * %Notification.
 */
class CUTEHMI_API Notification:
	public QObject
{
	Q_OBJECT

	public:
		Q_PROPERTY(Type type READ type WRITE setType NOTIFY typeChanged)
		Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

		enum Type {
			NOTE = 1,
			WARNING = 2,
			CRITICAL = 3
		};
		Q_ENUM(Type)

		explicit Notification(Type type = NOTE, const QString & text = QString(), QObject * parent = nullptr);

		static void Info(const QString & text);

		static void Warning(const QString & text);

		static void Critical(const QString & text);

		static void Critical(const ErrorInfo & errorInfo);

		Type type() const;

		void setType(Type type);

		QString text() const;

		void setText(const QString & text);

		const QDateTime & dateTime() const;

		std::unique_ptr<Notification> clone() const;

	signals:
		void typeChanged();

		void textChanged();

	private:
		struct Members
		{
			Type type;
			QString text;
			QDateTime dateTime;
		};

		MPtr<Members> m;
};

}

#endif

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
