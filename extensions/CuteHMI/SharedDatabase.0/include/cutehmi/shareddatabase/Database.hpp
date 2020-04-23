#ifndef DATABASECONNECTION_HPP
#define DATABASECONNECTION_HPP

#include "internal/common.hpp"
#include "internal/DatabaseConfig.hpp"
#include "internal/DatabaseConnectionHandler.hpp"
#include "internal/DatabaseThread.hpp"

#include <cutehmi/services/Serviceable.hpp>
#include <cutehmi/macros.hpp>

#include <QObject>

namespace cutehmi {
namespace shareddatabase {

/**
 * Database. This class stores databse configuration and manages database connection, which is established in dedicated thread.
 */
class CUTEHMI_SHAREDDATABASE_API Database:
	public QObject,
	public services::Serviceable

{
		Q_OBJECT

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

		virtual std::unique_ptr<ServiceStatuses> configureStarted(QState * active, const QState * idling, const QState * yielding) override;

		virtual std::unique_ptr<ServiceStatuses> configureStarting(QState * starting) override;

		virtual std::unique_ptr<ServiceStatuses> configureStopping(QState * stopping) override;

		virtual std::unique_ptr<ServiceStatuses> configureBroken(QState * broken) override;

		virtual std::unique_ptr<ServiceStatuses> configureRepairing(QState * repairing) override;

		virtual std::unique_ptr<ServiceStatuses> configureEvacuating(QState * evacuating) override;

		virtual std::unique_ptr<QAbstractTransition> transitionToStarted() const override;

		virtual std::unique_ptr<QAbstractTransition> transitionToStopped() const override;

		virtual std::unique_ptr<QAbstractTransition> transitionToBroken() const override;

		virtual std::unique_ptr<QAbstractTransition> transitionToYielding() const override;

		virtual std::unique_ptr<QAbstractTransition> transitionToIdling() const override;

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

		void errored(InplaceError error);

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

#endif // DATABASECONNECTION_HPP
