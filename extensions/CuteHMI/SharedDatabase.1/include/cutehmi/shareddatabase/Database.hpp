#ifndef H_EXTENSIONS_CUTEHMI_SHAREDDATABASE_1_INCLUDE_CUTEHMI_SHAREDDATABASE_DATABASE_HPP
#define H_EXTENSIONS_CUTEHMI_SHAREDDATABASE_1_INCLUDE_CUTEHMI_SHAREDDATABASE_DATABASE_HPP

#include "internal/common.hpp"
#include "internal/DatabaseConfig.hpp"
#include "internal/DatabaseConnectionHandler.hpp"
#include "internal/DatabaseThread.hpp"

#include <cutehmi/services/Serviceable.hpp>
#include <cutehmi/macros.hpp>

#include <QObject>
#include <QQmlEngine>

namespace cutehmi {
namespace shareddatabase {

/**
 * Database. This class stores databse configuration and manages database connection, which is established in dedicated thread.
 */
class CUTEHMI_SHAREDDATABASE_API Database:
	public QObject,
	public cutehmi::services::Serviceable
{
		Q_OBJECT
		QML_NAMED_ELEMENT(Database)

	public:
		static const char * INITIAL_TYPE;
		static const char * INITIAL_HOST;
		static constexpr int INITIAL_PORT = 5432;
		static const char * INITIAL_NAME;
		static const char * INITIAL_USER;
		static const char * INITIAL_PASSWORD;
		static constexpr bool INITIAL_THREADED = true;

		/**
		  Database type. Use Qt [driver name](https://doc.qt.io/qt-5/qsqldatabase.html#addDatabase-1) to specify the type.
		  */
		Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)

		Q_PROPERTY(QString host READ host WRITE setHost NOTIFY hostChanged)

		Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)

		Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

		Q_PROPERTY(QString user READ user WRITE setUser NOTIFY userChanged)

		Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)

		Q_PROPERTY(QString connectionName READ connectionName WRITE setConnectionName NOTIFY connectionNameChanged)

		Q_PROPERTY(bool threaded READ threaded WRITE setThreaded NOTIFY threadedChanged)

		static bool IsConnected(const QString & connectionName);

		Database(QObject * parent = nullptr);

		~Database() override;

		/**
		 * Get database type.
		 * @return database type.
		 */
		QString type() const;

		/**
		 * Set database type.
		 * @param type database type.
		 */
		void setType(const QString & type);

		/**
		 * Get host.
		 * @return host name.
		 */
		QString host() const;

		/**
		 * Set host.
		 * @param host host name.
		 */
		void setHost(const QString & host);

		/**
		 * Get port.
		 * @return port number.
		 */
		int port() const;

		/**
		 * Set port.
		 * @param port port number.
		 */
		void setPort(int port);

		/**
		 * Get database name.
		 * @return database name.
		 */
		QString name() const;

		/**
		 * Set database name.
		 * @param name database name.
		 */
		void setName(const QString & name);

		/**
		 * Get databse user.
		 * @return user name.
		 */
		QString user() const;

		/**
		 * Set databse user.
		 * @param user user name.
		 */
		void setUser(const QString & user);

		/**
		 * Get database password.
		 * @return password.
		 */
		QString password() const;

		/**
		 * Set database password.
		 * @param password password.
		 */
		void setPassword(const QString & password);

		/**
		 * Get connection name.
		 * @return connection name.
		 */
		QString connectionName() const;

		/**
		 * Set connection name.
		 * @param connectionName connection name.
		 */
		void setConnectionName(const QString & connectionName);

		/**
		 * Get threaded status. Threaded status determines whether connection is threaded, i.e. it is established in a separate
		 * thread.
		 * @return @p true when connection should be established in separate thread, @p false otherwise.
		 */
		bool threaded() const;

		/**
		 * Set threaded status. Threaded connection is established
		 * @param threaded determines whether connection should be established in a separate thread.
		 */
		void setThreaded(bool threaded);

		void configureStarted(QState * active, const QState * idling, const QState * yielding, AssignStatusFunction assignStatus) override;

		void configureStarting(QState * starting, AssignStatusFunction assignStatus) override;

		void configureStopping(QState * stopping, AssignStatusFunction assignStatus) override;

		void configureBroken(QState * broken, AssignStatusFunction assignStatus) override;

		void configureRepairing(QState * repairing, AssignStatusFunction assignStatus) override;

		void configureEvacuating(QState * evacuating, AssignStatusFunction assignStatus) override;

		std::unique_ptr<QAbstractTransition> transitionToStarted() const override;

		std::unique_ptr<QAbstractTransition> transitionToStopped() const override;

		std::unique_ptr<QAbstractTransition> transitionToBroken() const override;

		std::unique_ptr<QAbstractTransition> transitionToYielding() const override;

		std::unique_ptr<QAbstractTransition> transitionToIdling() const override;

	signals:
		void typeChanged();

		void hostChanged();

		void portChanged();

		void nameChanged();

		void userChanged();

		void passwordChanged();

		void connectionNameChanged();

		void threadedChanged();

		void connected();

		void disconnected();

		void errored(cutehmi::InplaceError error);

	private slots:
		void initializeConnection();

		void closeConnection();

		void onHandlerConnected(QString connectionName);

		void onHandlerDisconnected(QString connectionName);

	private:
		struct Members {
			internal::DatabaseConfig config;
			internal::DatabaseThread thread;
			std::unique_ptr<internal::DatabaseConnectionHandler> connectionHandler;
			bool threaded = INITIAL_THREADED;
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)C: Copyright © 2022-2024, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
