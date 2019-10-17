#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_REGISTER1CONTROLLER_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_REGISTER1CONTROLLER_HPP

#include "internal/common.hpp"
#include "internal/RegisterControllerMixin.hpp"
#include "AbstractDevice.hpp"
#include "Register1.hpp"
#include "AbstractRegisterController.hpp"

#include <QObject>
#include <QBasicTimer>

namespace cutehmi {
namespace modbus {

/**
 * Register controller for 1 bit registers.
 */
class CUTEHMI_MODBUS_API Register1Controller:
	public AbstractRegisterController,
	protected internal::RegisterControllerMixin<Register1Controller>
{
		Q_OBJECT

		friend class internal::RegisterControllerMixin<Register1Controller>;
		typedef internal::RegisterControllerMixin<Register1Controller> Mixin;

	public:
		static constexpr bool INITIAL_VALUE = false;

		Q_PROPERTY(bool value READ value WRITE setValue NOTIFY valueChanged)

		Register1Controller(QObject * parent = nullptr);

		~Register1Controller() override;

		bool value() const;

		void setValue(bool value);

	public slots:
		void writeValue();

	signals:
		void valueChanged();

		void valueUpdated();

		void valueWritten();

		void valueFailed();

		void valueMismatch();

	protected:
		virtual Register1 * registerAt(quint16 address) const = 0;

		virtual AbstractDevice::Function readRegistersFunction() const = 0;

		virtual AbstractDevice::Function writeRegisterFunction() const = 0;

		virtual void requestWriteRegister(quint16 address, bool value, QUuid * requestId) const = 0;

		void timerEvent(QTimerEvent * event) override;

		quint16 bytes() const override;

		void onDeviceDestroyed() override;

	protected slots:
		void onRequestCompleted(QJsonObject request, QJsonObject reply) override;

		void resetRegister();

	private:
		void updateValue();

		void updateValue(bool value);

		void updateValue(const QJsonValue & value);

		void requestWrite(bool value);

		bool verifyRegisterValue() const;

	private:
		struct Members {
			bool value;
			bool postponedWritePending;
			bool adjustingValue;
			bool requestedValue;
			Register1 * register1;
			QUuid requestId;
			QBasicTimer writeTimer;

			Members():
				value(INITIAL_VALUE),
				postponedWritePending(false),
				adjustingValue(false),
				requestedValue(0.0),
				register1(nullptr)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
