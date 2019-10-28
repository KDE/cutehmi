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
			INFO = 1,
			WARNING = 2,
			CRITICAL = 3
		};
		Q_ENUM(Type)

		explicit Notification(Type type = INFO, const QString & text = QString(), QObject * parent = nullptr);

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

//(c)C: Copyright © 2018-2019, Michal Policht <michpolicht@gmail.com>, CuteBOT <michpolicht@gmail.com>, Mr CuteBOT <michpolicht@gmail.com>, Michal Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
