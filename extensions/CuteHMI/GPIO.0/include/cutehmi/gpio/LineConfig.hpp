#ifndef H_EXTENSIONS_CUTEHMI_GPIO_0_INCLUDE_CUTEHMI_GPIO_LINECONFIG_HPP
#define H_EXTENSIONS_CUTEHMI_GPIO_0_INCLUDE_CUTEHMI_GPIO_LINECONFIG_HPP


#include "internal/common.hpp"

#include <gpiod.h>

#include <QObject>

namespace cutehmi {
namespace gpio {

class CUTEHMI_GPIO_API LineConfig:
	public QObject
{
	Q_OBJECT

	public:
		enum Direction: int {
			DIRECTION_INPUT = GPIOD_LINE_DIRECTION_INPUT,
			DIRECTION_OUTPUT = GPIOD_LINE_DIRECTION_OUTPUT
		};
		Q_ENUM(Direction)

		enum ActiveState: int {
			ACTIVE_STATE_HIGH = GPIOD_LINE_ACTIVE_STATE_HIGH,
			ACTIVE_STATE_LOW = GPIOD_LINE_ACTIVE_STATE_LOW
		};
		Q_ENUM(ActiveState)

		Q_PROPERTY(Direction direction READ direction WRITE setDirection NOTIFY directionChanged)
		Q_PROPERTY(ActiveState activeState READ activeState WRITE setActiveState NOTIFY activeStateChanged)
		Q_PROPERTY(bool openDrain READ openDrain WRITE setOpenDrain NOTIFY openDrainChanged)
		Q_PROPERTY(bool openSource READ openSource WRITE setOpenSource NOTIFY openSourceChanged)

		explicit LineConfig(QObject * parent = nullptr);

		Direction direction() const;

		void setDirection(Direction direction);

		ActiveState activeState() const;

		void setActiveState(ActiveState activeState);

		bool openDrain() const;

		void setOpenDrain(bool openDrain);

		bool openSource() const;

		void setOpenSource(bool openSource);

	signals:
		void directionChanged();

		void activeStateChanged();

		void openDrainChanged();

		void openSourceChanged();

	private:
		struct Members
		{
			Direction direction;
			ActiveState activeState;
			bool openDrain;
			bool openSource;	// yes :)

			Members():
				direction(LineConfig::DIRECTION_OUTPUT),
				activeState(LineConfig::ACTIVE_STATE_HIGH),
				openDrain(false),
				openSource(false)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
