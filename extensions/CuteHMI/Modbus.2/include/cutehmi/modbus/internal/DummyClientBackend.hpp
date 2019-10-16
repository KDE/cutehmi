#ifndef INCLUDECUTEHMIMODBUSINTERNALDUMMYCLIENTBACKEND_HPP
#define INCLUDECUTEHMIMODBUSINTERNALDUMMYCLIENTBACKEND_HPP

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

#endif // INCLUDECUTEHMIMODBUSINTERNALDUMMYCLIENTBACKEND_HPP
