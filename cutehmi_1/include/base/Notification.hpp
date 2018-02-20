#ifndef CUTEHMI_CUTEHMI__BASE__1__LIB_INCLUDE_BASE_NOTIFICATION_HPP
#define CUTEHMI_CUTEHMI__BASE__1__LIB_INCLUDE_BASE_NOTIFICATION_HPP

#include "internal/common.hpp"

#include <utils/MPtr.hpp>

#include <QObject>
#include <QDateTime>

namespace cutehmi {
namespace base {

class CUTEHMI_API Notification:
	public QObject
{
	Q_OBJECT

	public:
		Q_PROPERTY(type_t type READ type WRITE setType NOTIFY typeChanged)
		Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

		enum type_t {
			NOTE = 1,
			WARNING = 2,
			CRITICAL = 3
		};
		Q_ENUM(type_t)

		explicit Notification(type_t type = NOTE, const QString & text = QString(), QObject * parent = 0);

		static void Note(const QString & text);

		static void Warning(const QString & text);

		static void Critical(const QString & text);

		static void Critical(const ErrorInfo & errorInfo);

		type_t type() const;

		void setType(type_t type);

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
			type_t type;
			QString text;
			QDateTime dateTime;
		};

		utils::MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
