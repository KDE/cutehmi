#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_ABSTRACTREGISTERCONTROLLER_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_ABSTRACTREGISTERCONTROLLER_HPP

#include "internal/common.hpp"
#include "AbstractDevice.hpp"

#include <QObject>
#include <QQmlParserStatus>

namespace cutehmi {
namespace modbus {

class CUTEHMI_MODBUS_API AbstractRegisterController:
	public QObject,
	public QQmlParserStatus
{
		Q_OBJECT
		Q_INTERFACES(QQmlParserStatus)

	public:
		enum WriteMode {
			WRITE_DELAYED,
			WRITE_POSTPONED,
			WRITE_IMMEDIATE,
			WRITE_EXPLICIT,
		};
		Q_ENUM(WriteMode)

		static constexpr unsigned int INITIAL_ADDRESS = 0;
		static constexpr WriteMode INITIAL_WRITE_MODE = WRITE_DELAYED;
		static constexpr int INITIAL_WRITE_DELAY = 500;
		static constexpr bool INITIAL_BUSY = true;
		static constexpr bool INITIAL_READ_ON_WRITE = true;

		Q_PROPERTY(AbstractDevice * device READ device WRITE setDevice NOTIFY deviceChanged)
		// Note: unsigned int is guaranteed to be at least 16 bits wide by the standard. Using unsigned int instead of quint16 (aka
		// ushort), because when using quint16 QML throws an error (unsupported type "ushort") for an alias to quint16 property.
		Q_PROPERTY(unsigned int address READ address WRITE setAddress NOTIFY addressChanged)
		Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)
		Q_PROPERTY(bool readOnWrite READ readOnWrite WRITE setReadOnWrite NOTIFY readOnWriteChanged)
		Q_PROPERTY(WriteMode writeMode READ writeMode WRITE setWriteMode NOTIFY writeModeChanged)
		Q_PROPERTY(int writeDelay READ writeDelay WRITE setWriteDelay NOTIFY writeDelayChanged)

		AbstractRegisterController(QObject * parent = nullptr);

		AbstractDevice * device() const;

		void setDevice(AbstractDevice * device);

		unsigned int address() const;

		void setAddress(unsigned int address);

		bool busy() const;

		bool readOnWrite() const;

		void setReadOnWrite(bool readOnWrite);

		WriteMode writeMode() const;

		void setWriteMode(WriteMode writeMode);

		int writeDelay() const;

		void setWriteDelay(int writeDelay);

	signals:
		void deviceChanged();

		void addressChanged();

		void busyChanged();

		void readOnWriteChanged();

		void writeModeChanged();

		void writeDelayChanged();

	protected:
		virtual void requestReadRegisters(quint16 address, quint16 amount, QUuid * requestId) const = 0;

		virtual quint16 bytes() const = 0;

		virtual void onDeviceDestroyed() = 0;

		void classBegin() override;

		void componentComplete() override;

		void setBusy(bool busy);

	protected slots:
		virtual void onRequestCompleted(QJsonObject request, QJsonObject reply) = 0;

	private:
		bool deviceReady() const;

		struct Members
		{
			AbstractDevice * device;
			unsigned int address;
			bool busy;
			bool readOnWrite;
			WriteMode writeMode;
			int writeDelay;
			bool postponedWritePending;
			bool deferRequestRead;

			Members():
				device(nullptr),
				address(INITIAL_ADDRESS),
				busy(INITIAL_BUSY),
				readOnWrite(INITIAL_READ_ON_WRITE),
				writeMode(INITIAL_WRITE_MODE),
				writeDelay(INITIAL_WRITE_DELAY),
				deferRequestRead(false)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
