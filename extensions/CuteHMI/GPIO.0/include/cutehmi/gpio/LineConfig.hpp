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

//(c)C: Copyright © 2019, CuteBOT <michpolicht@gmail.com>, Michal Policht <michpolicht@gmail.com>, Michal Policht <michal@policht.pl>, Mr CuteBOT <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
