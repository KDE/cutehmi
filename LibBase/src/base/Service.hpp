#ifndef CUTEHMI_LIBBASE_SRC_BASE_SERVICE_HPP
#define CUTEHMI_LIBBASE_SRC_BASE_SERVICE_HPP

#include "../platform.hpp"

#include <QObject>

#include <memory>

namespace cutehmi {
namespace base {

class CUTEHMI_BASE_API Service:
	public QObject
{
	Q_OBJECT

	public:
		Q_PROPERTY(QString name READ name NOTIFY nameChanged)
		Q_PROPERTY(state_t state READ state NOTIFY stateChanged)

		enum state_t : int {
			STOPPED,
			STOPPING,
			STARTED,
			STARTING
		};
		Q_ENUM(state_t)

		static constexpr const char * INITIAL_NAME = "Unnamed service";
		static constexpr state_t INITIAL_STATE = STOPPED;

		Service(const QString & name = INITIAL_NAME, QObject * parent = 0);

		const QString & name() const;

		void setName(const QString & name);

		state_t state() const;

		void start();

		void stop();

	signals:
		void nameChanged();

		void stateChanged(state_t oldState, state_t newState);

	protected:
		/**
		 * Set state.
		 * @param state state of the service.
		 */
		void setState(state_t state);

		/**
		 * Custom start. Default implementation returns @p STARTED value.
		 * Start sequence can be implemented in asynchronous way. In such case function
		 * should return @p STARTING value and appropriate state should be set later.
		 * @return state of the service after calling this function. If start has been succesful
		 * function should return @p STARTED value. If start failed it should return @p STOPPED value.
		 * If start is implemented in asynchronous way function should return @p STARTING value and
		 * appropriate state (@p STARTED or @p STOPPED) should be set later, using setState() function.
		 */
		virtual state_t customStart();

		/**
		 * Custom stop. Default implementation returns @p STOPPED value.
		 * Stop sequence can be implemented in asynchronous way. In such case function
		 * should return @p STOPPING value and @p STOPPED state should be set later.
		 * If service could not be stopped, because it was in the inconsistent state (@p STARTING or @p STOPPING),
		 * when this function has been called, then function should do nothing and return actual state value
		 * (@p STARTING or @p STOPPING).
		 * @return state of the service after calling this function.
		 */
		virtual state_t customStop();

	private:
		struct Members
		{
			QString name;
			state_t state;
		};

		std::unique_ptr<Members> m;
};

}
}

#endif
