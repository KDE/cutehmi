#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_ABSTRACTREGISTERCONTROLLER_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_ABSTRACTREGISTERCONTROLLER_HPP

#include "internal/common.hpp"
#include "AbstractDevice.hpp"

#include <QObject>
#include <QQmlParserStatus>

namespace cutehmi {
namespace modbus {

/**
 * Abstract register controller.
 */
class CUTEHMI_MODBUS_API AbstractRegisterController:
	public QObject,
	public QQmlParserStatus
{
		Q_OBJECT
		Q_INTERFACES(QQmlParserStatus)

	public:
		/**
		 * Write mode enum.
		 */
		enum WriteMode {
			WRITE_DELAYED,		///< Writes are delayed. Write will be requested after amount of time specified by @a writeDelay property has passed.
			WRITE_POSTPONED,	///< Writes are postponed, which means that write will not be requested until previous write has finished.
			WRITE_IMMEDIATE,	///< Writes are requested immediately, which may creates a queue of pending writes if they are not proceeded fast enough.
			WRITE_EXPLICIT,		///< Writes are explicit, i.e. write requires an explicit call to write value function.
		};
		Q_ENUM(WriteMode)

		static constexpr unsigned int INITIAL_ADDRESS = 0;
		static constexpr WriteMode INITIAL_WRITE_MODE = WRITE_DELAYED;
		static constexpr int INITIAL_WRITE_DELAY = 500;
		static constexpr bool INITIAL_BUSY = true;
		static constexpr bool INITIAL_READ_ON_WRITE = true;
		static constexpr bool INITIAL_ENABLED = true;

		/**
		  Device associated with controller.
		  */
		Q_PROPERTY(cutehmi::modbus::AbstractDevice * device READ device WRITE setDevice NOTIFY deviceChanged)

		/**
		  Register address.
		  */
		// Note: unsigned int is guaranteed to be at least 16 bits wide by the standard. Using unsigned int instead of quint16 (aka
		// ushort), because when using quint16 QML throws an error (unsupported type "ushort") for an alias to quint16 property.
		Q_PROPERTY(unsigned int address READ address WRITE setAddress NOTIFY addressChanged)

		/**
		  Busy status. Controller indicated that it's busy when there's pending read or write.
		  */
		Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)

		/**
		  Read-on-write. If @p true, then controller requests subsequent read upon write.
		  */
		Q_PROPERTY(bool readOnWrite READ readOnWrite WRITE setReadOnWrite NOTIFY readOnWriteChanged)

		/**
		  Write mode.
		  */
		Q_PROPERTY(WriteMode writeMode READ writeMode WRITE setWriteMode NOTIFY writeModeChanged)

		/**
		  Write delay [ms]. Relevant only when write mode is set to WRITE_DELAYED.
		  */
		Q_PROPERTY(int writeDelay READ writeDelay WRITE setWriteDelay NOTIFY writeDelayChanged)

		/**
		  Determines whether controller is enabled.
		  */
		Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)

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

		bool enabled() const;

		void setEnabled(bool enabled);

	signals:
		void deviceChanged();

		void addressChanged();

		void busyChanged();

		void readOnWriteChanged();

		void writeModeChanged();

		void writeDelayChanged();

		void enabledChanged();

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
			bool enabled;
			bool deferRequestRead;

			Members():
				device(nullptr),
				address(INITIAL_ADDRESS),
				busy(INITIAL_BUSY),
				readOnWrite(INITIAL_READ_ON_WRITE),
				writeMode(INITIAL_WRITE_MODE),
				writeDelay(INITIAL_WRITE_DELAY),
				enabled(INITIAL_ENABLED),
				deferRequestRead(false)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)C: Copyright © 2019-2020, Michał Policht <michal@policht.pl>, Yuri Chornoivan <yurchor@ukr.net>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
