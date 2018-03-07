#ifndef H_MODULES_CUTEHMI__SERVICES__1_INCLUDE_CUTEHMI_SERVICES_SERVICE_HPP
#define H_MODULES_CUTEHMI__SERVICES__1_INCLUDE_CUTEHMI_SERVICES_SERVICE_HPP

#include "internal/common.hpp"

#include <QObject>

#include <memory>

namespace cutehmi {
namespace services {

class CUTEHMI_SERVICES_API Service:
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
			STARTING,
			BROKEN,
			REPAIRING
		};
		Q_ENUM(state_t)

		static constexpr const char * INITIAL_NAME = "Unnamed service";
		static constexpr state_t INITIAL_STATE = STOPPED;

		Service(const QString & name = INITIAL_NAME, QObject * parent = 0);

		const QString & name() const;

		void setName(const QString & name);

		state_t state() const;

	public slots:
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
		 * Custom start. Override this function to provide start procedure.
		 * Start sequence can be implemented in asynchronous way. In such case function
		 * should return @p STARTING value and appropriate state should be set later. This function
		 * can be called only if service is in @p STOPPED state.
		 * @return state of the service after calling this function. If start has been succesful
		 * function should return @p STARTED value. If start failed it should return @p STOPPED value.
		 * If start is implemented in asynchronous way function should return @p STARTING value and
		 * appropriate state (@p STARTED or @p STOPPED) should be set later, using setState() function.
		 * Default implementation returns @p STARTED value.
		 */
		virtual state_t customStart();

		/**
		 * Custom stop. Override this function to provide custom stop procedure.
		 * Stop sequence can be implemented in asynchronous way. In such case function
		 * should return @p STOPPING value and @p STOPPED state should be set later.
		 * This function can be called even if service is not in @p STARTED state.
		 * If it is not possible to stop the service, while it is in incoherent state (@p STARTING or @p STOPPING),
		 * then function should do nothing and return actual state (@p STARTING or @p STOPPING). However, it should
		 * be always possible to stop the service if it is in @p STARTED state.
		 * @return state of the service after calling this function. If stop is implemented in asynchronous way
		 * function should return @p STOPPING value and @p STOPPED state should be set later, using setState() function.
		 * Default implementation returns @p STOPPED value.
		 */
		virtual state_t customStop();

	private:
		struct Members
		{
			QString name;
			state_t state;
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
