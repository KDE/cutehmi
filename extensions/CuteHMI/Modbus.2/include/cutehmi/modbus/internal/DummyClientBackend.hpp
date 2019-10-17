#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_DUMMYCLIENTBACKEND_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_DUMMYCLIENTBACKEND_HPP

#include "common.hpp"
#include "AbstractClientBackend.hpp"
#include "DummyClientConfig.hpp"

namespace cutehmi {
namespace modbus {
namespace internal {

class CUTEHMI_MODBUS_PRIVATE DummyClientBackend:
	public AbstractClientBackend
{
		Q_OBJECT

	public:
		DummyClientBackend(DummyClientConfig * config, QObject * parent = nullptr);

		~DummyClientBackend() override;

	public slots:
		void ensureClosed();

	signals:
		void opened();

		void closed();

	protected:
		bool proceedRequest(QUuid requestId) override;

		void readCoils(QUuid requestId, quint16 startAddress, quint16 endAddress) override;

		void writeCoil(QUuid requestId, quint16 address, bool value) override;

		void writeMultipleCoils(QUuid requestId, quint16 startAddress, const QVector<quint16> & values) override;

		void readDiscreteInputs(QUuid requestId, quint16 startAddress, quint16 endAddress) override;

		void readHoldingRegisters(QUuid requestId, quint16 startAddress, quint16 endAddress) override;

		void writeHoldingRegister(QUuid requestId, quint16 address, quint16 value) override;

		void writeMultipleHoldingRegisters(QUuid requestId, quint16 startAddress, const QVector<quint16> & values) override;

		void readInputRegisters(QUuid requestId, quint16 startAddress, quint16 endAddress) override;

	protected slots:
		void open() override;

		void close() override;

	private:
		void setState(AbstractClient::State state);

	private:
		typedef typename internal::RegisterTraits<InputRegister>::Container InputRegisterContainer;
		typedef typename internal::RegisterTraits<HoldingRegister>::Container HolidingRegisterContainer;
		typedef typename internal::RegisterTraits<DiscreteInput>::Container DiscreteInputContainer;
		typedef typename internal::RegisterTraits<Coil>::Container CoilContainer;

		struct Members
		{
			DummyClientConfig * config;
			AbstractClient::State state;
			InputRegisterContainer inputRegisters;
			HolidingRegisterContainer holdingRegisters;
			DiscreteInputContainer discreteInputs;
			CoilContainer coils;
		};

		MPtr<Members> m;
};

}
}
}

#endif

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
