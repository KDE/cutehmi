#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_4_INCLUDE_CUTEHMI_MODBUS_ABSTRACTDEVICE_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_4_INCLUDE_CUTEHMI_MODBUS_ABSTRACTDEVICE_HPP

#include "internal/common.hpp"
#include "internal/RegisterTraits.hpp"
#include "InputRegister.hpp"
#include "internal/HoldingRegister.hpp"
#include "internal/InputRegister.hpp"
#include "DiscreteInput.hpp"
#include "Coil.hpp"

#include <cutehmi/InplaceError.hpp>
#include <cutehmi/services/Serviceable.hpp>

#include <QObject>
#include <QUuid>
#include <QJsonObject>
#include <QJsonArray>
#include <QQmlListProperty>
#include <QModbusPdu>
#include <QQmlEngine>

#include <list>

namespace cutehmi {
namespace modbus {

namespace internal {
class IterableTasks;
}

/**
 * Abstract Modbus device.
 */
class CUTEHMI_MODBUS_API AbstractDevice:
	public QObject,
	public services::Serviceable
{
		Q_OBJECT
		QML_NAMED_ELEMENT(AbstractDevice)
		QML_UNCREATABLE("AbstractDevice is an abstract class")

		friend class test_AbstractDevice;
		friend class test_AbstractServer;
		friend class internal::IterableTasks;

	public:
		enum State {
			OPENING,
			OPENED,
			CLOSING,
			CLOSED
		};
		Q_ENUM(State)

		enum Function {
			FUNCTION_INVALID = QModbusPdu::Invalid,
			FUNCTION_READ_COILS = QModbusPdu::ReadCoils,
			FUNCTION_READ_DISCRETE_INPUTS = QModbusPdu::ReadDiscreteInputs,
			FUNCTION_READ_HOLDING_REGISTERS = QModbusPdu::ReadHoldingRegisters,
			FUNCTION_READ_INPUT_REGISTERS = QModbusPdu::ReadInputRegisters,
			FUNCTION_WRITE_COIL = QModbusPdu::WriteSingleCoil,
			FUNCTION_WRITE_HOLDING_REGISTER = QModbusPdu::WriteSingleRegister,
			FUNCTION_READ_EXCEPTION_STATUS = QModbusPdu::ReadExceptionStatus,
			FUNCTION_DIAGNOSTICS = QModbusPdu::Diagnostics,
			FUNCTION_FETCH_COMM_EVENT_COUNTER = QModbusPdu::GetCommEventCounter,
			FUNCTION_FETCH_COMM_EVENT_LOG = QModbusPdu::GetCommEventLog,
			FUNCTION_WRITE_MULTIPLE_COILS = QModbusPdu::WriteMultipleCoils,
			FUNCTION_WRITE_MULTIPLE_HOLDING_REGISTERS = QModbusPdu::WriteMultipleRegisters,
			FUNCTION_REPORT_SLAVE_ID = QModbusPdu::ReportServerId,
			FUNCTION_READ_FILE_RECORD = QModbusPdu::ReadFileRecord,
			FUNCTION_WRITE_FILE_RECORD = QModbusPdu::WriteFileRecord,
			FUNCTION_MASK_WRITE_HOLDING_REGISTER = QModbusPdu::MaskWriteRegister,
			FUNCTION_READ_WRITE_MULTIPLE_HOLDING_REGISTERS = QModbusPdu::ReadWriteMultipleRegisters,
			FUNCTION_READ_FIFO_QUEUE = QModbusPdu::ReadFifoQueue,
			// FUNCTION_ENCAPSULATED_INTERFACE_TRANSPORT = QModbusPdu::EncapsulatedInterfaceTransport, // Currently not implemented.
			FUNCTION_UNDEFINED = QModbusPdu::UndefinedFunctionCode,
			FUNCTION_WRITE_DISCRETE_INPUT,
			FUNCTION_WRITE_MULTIPLE_DISCRETE_INPUTS,
			FUNCTION_WRITE_INPUT_REGISTER,
			FUNCTION_WRITE_MULTIPLE_INPUT_REGISTERS,
			FUNCTION_RAW
		};
		Q_ENUM(Function)

		enum DiagnosticsSubfunction : quint16 {
			DIAGNOSTICS_RETURN_QUERY_DATA = 0x00,
			DIAGNOSTICS_RESTART_COMM_OPTION = 0x01,
			DIAGNOSTICS_RETURN_DIAGNOSTICS_REGISTER = 0x02,
			DIAGNOSTICS_CHANGE_ASCII_INPUT_DELIMITER = 0x03,
			DIAGNOSTICS_FORCE_LISTEN_ONLY_MODE = 0x04,
			DIAGNOSTICS_CLEAR_COUNTERS_AND_DIAGNOSTICS_REGISTER = 0x0A,
			DIAGNOSTICS_RETURN_BUS_MESSAGE_COUNT = 0x0B,
			DIAGNOSTICS_RETURN_BUS_COMM_ERROR_COUNT = 0x0C,
			DIAGNOSTICS_RETURN_BUS_EXCEPTION_ERROR_COUNT = 0x0D,
			DIAGNOSTICS_RETURN_SLAVE_MESSAGE_COUNT = 0x0E,
			DIAGNOSTICS_RETURN_SLAVE_NO_RESPONSE_COUNT = 0x0F,
			DIAGNOSTICS_RETURN_SLAVE_NAK_COUNT = 0x10,
			DIAGNOSTICS_RETURN_SLAVE_BUSY_COUNT = 0x11,
			DIAGNOSTICS_RETURN_BUS_CHARACTER_OVERRUN_COUNT = 0x12,
			DIAGNOSTICS_RETURN_IOP_OVERRUN_COUNT = 0x13,
			DIAGNOSTICS_CLEAR_OVERRUN_COUNTER_AND_FLAG = 0x14,
			DIAGNOSTICS_GET_CLEAR_MODBUS_PLUS_STATISTICS = 0x15
		};
		Q_ENUM(DiagnosticsSubfunction)

		/**
		 * @anchor cutehmi-modbus-AbstractDevice-query_limits
		 * @name Query limits.
		 *
		 * Modbus protocol imposes following restriction on amount of data that can be read or write at once.
		 *
		 * > "The quantity of registers to be read, combined with all other fields in the expected response, must not exceed the
		 * >  allowable length of Modbus messages: 256 bytes."
		 *                                                    @quote{-- Modicon Modbus Protocol Reference Guide PI–MBUS–300  Rev. J}
		 *
		 * This means that Modbus message must not exceed 256 octets in size. In Modbus over TCP, device address and CRC (3 octets)
		 * are traded for 6 octet header and 1 octet unit identifier, which gives 4 octets less to store values. Theoretical maximal
		 * amounts of values for given Modbus register types, that can be queried within a single message, are defined by constants
		 * below, however particular PLCs may impose further restrictions.
		 */
		///@{
		/**
		 * Maximal amount of coils that can be read at once through TCP.
		 */
		static constexpr int MAX_READ_TCP_COILS = 1976;

		/**
		 * Maximal amount of coils that can be read at once through RTU.
		 */
		static constexpr int MAX_READ_RTU_COILS = 2008;

		/**
		 * Maximal amount of coils that can be written at once through TCP.
		 */
		static constexpr int MAX_WRITE_TCP_COILS = 1944;

		/**
		 * Maximal amount of coils that can be written at once through RTU.
		 */
		static constexpr int MAX_WRITE_RTU_COILS = 1976;

		/**
		 * Maximal amount of discrete inputs that can be read at once through TCP.
		 */
		static constexpr int MAX_READ_TCP_DISCRETE_INPUTS = 1976;

		/**
		 * Maximal amount of discrete inputs that can be read at once through RTU.
		 */
		static constexpr int MAX_READ_RTU_DISCRETE_INPUTS = 2008;

		/**
		 * Maximal amount of holding registers that can be read at once through TCP.
		 */
		static constexpr int MAX_READ_TCP_HOLDING_REGISTERS = 123;

		/**
		 * Maximal amount of holding registers that can be read at once through RTU.
		 */
		static constexpr int MAX_READ_RTU_HOLDING_REGISTERS = 125;

		/**
		 * Maximal amount of holding registers that can be written at once through TCP.
		 */
		static constexpr int MAX_WRITE_TCP_HOLDING_REGISTERS = 123;

		/**
		 * Maximal amount of holding registers that can be written at once through RTU.
		 */
		static constexpr int MAX_WRITE_RTU_HOLDING_REGISTERS = 125;

		/**
		 * Maximal amount of input registers that can be read at once through TCP.
		 */
		static constexpr int MAX_READ_TCP_INPUT_REGISTERS = 123;

		/**
		 * Maximal amount of input  registers that can be read at once through RTU.
		 */
		static constexpr int MAX_READ_RTU_INPUT_REGISTERS = 125;
		///@}

		static constexpr quint16 MIN_ADDRESS = 0;
		static constexpr quint16 MAX_ADDRESS = 65535;

		static constexpr int INITIAL_MAX_READ_COILS = 16;				// Max RTU: 2008, Max TCP: 1976
		static constexpr int INITIAL_MAX_WRITE_COILS = 16;				// Max RTU: 1976, Max TCP: 1944
		static constexpr int INITIAL_MAX_READ_DISCRETE_INPUTS = 16;		// Max RTU: 2008, Max TCP: 1976
		static constexpr int INITIAL_MAX_WRITE_DISCRETE_INPUTS = 16;	// Max RTU: N/A,  Max TCP: N/A
		static constexpr int INITIAL_MAX_READ_HOLDING_REGISTERS = 16;	// Max RTU: 125, Max TCP: 123
		static constexpr int INITIAL_MAX_WRITE_HOLDING_REGISTERS = 16;	// Max RTU: 123, Max TCP: 121
		static constexpr int INITIAL_MAX_READ_INPUT_REGISTERS = 16;		// Max RTU: 125, Max TCP: 123
		static constexpr int INITIAL_MAX_WRITE_INPUT_REGISTERS = 16;    // Max RTU: N/A, Max TCP: N/A
		static constexpr int INITIAL_MAX_REQUESTS = 1000;
		static constexpr State INITIAL_STATE = CLOSED;
		static constexpr bool INITIAL_READY = false;

		Q_PROPERTY(State state READ state NOTIFY stateChanged)

		Q_PROPERTY(bool ready READ ready NOTIFY readyChanged)

		Q_PROPERTY(int maxReadCoils READ maxReadCoils WRITE setMaxReadCoils NOTIFY maxReadCoilsChanged)

		Q_PROPERTY(int maxWriteCoils READ maxWriteCoils WRITE setMaxWriteCoils NOTIFY maxWriteCoilsChanged)

		Q_PROPERTY(int maxReadDiscreteInputs READ maxReadDiscreteInputs WRITE setMaxReadDiscreteInputs NOTIFY maxReadDiscreteInputsChanged)

		Q_PROPERTY(int maxWriteDiscreteInputs READ maxWriteDiscreteInputs WRITE setMaxWriteDiscreteInputs NOTIFY maxWriteDiscreteInputsChanged)

		Q_PROPERTY(int maxReadHoldingRegisters READ maxReadHoldingRegisters WRITE setMaxReadHoldingRegisters NOTIFY maxReadHoldingRegistersChanged)

		Q_PROPERTY(int maxWriteHoldingRegisters READ maxWriteHoldingRegisters WRITE setMaxWriteHoldingRegisters NOTIFY maxWriteHoldingRegistersChanged)

		Q_PROPERTY(int maxReadInputRegisters READ maxReadInputRegisters WRITE setMaxReadInputRegisters NOTIFY maxReadInputRegistersChanged)

		Q_PROPERTY(int maxWriteInputRegisters READ maxWriteInputRegisters WRITE setMaxWriteInputRegisters NOTIFY maxWriteInputRegistersChanged)

		Q_PROPERTY(int maxRequests READ maxRequests WRITE setMaxRequests NOTIFY maxRequestsChanged)

		State state() const;

		/**
		 * Get readiness status. Indicates whether device is ready for handling requests.
		 * @return readiness status. If device is ready to handle requests function returns @p true, otherwise it returns @p false.
		 */
		bool ready() const;

		int maxReadCoils() const;

		void setMaxReadCoils(int maxReadCoils);

		int maxWriteCoils() const;

		void setMaxWriteCoils(int maxWriteCoils);

		int maxReadDiscreteInputs() const;

		void setMaxReadDiscreteInputs(int maxReadDiscreteInputs);

		int maxWriteDiscreteInputs() const;

		void setMaxWriteDiscreteInputs(int maxWriteDiscreteInputs);

		int maxReadHoldingRegisters() const;

		void setMaxReadHoldingRegisters(int maxReadHoldingRegisters);

		int maxWriteHoldingRegisters() const;

		void setMaxWriteHoldingRegisters(int maxWriteHoldingRegisters);

		int maxReadInputRegisters() const;

		void setMaxReadInputRegisters(int maxReadInputRegisters);

		int maxWriteInputRegisters() const;

		void setMaxWriteInputRegisters(int maxWriteInputRegisters);

		int maxRequests() const;

		void setMaxRequests(int maxRequests);

		Coil * coilAt(quint16 address);

		DiscreteInput * discreteInputAt(quint16 address);

		HoldingRegister * holdingRegisterAt(quint16 address);

		InputRegister * inputRegisterAt(quint16 address);

		/**
		 * Read coils request. Convenient function that prepares request payload and calls request() with FUNCTION_READ_COILS
		 * function code.
		 * @param address starting address.
		 * @param amount number of coils to query. Note that Modbus specification expects it to be 16 bit unsigned value, so 65535
		 * is maximal number of coils that can be queried at once (Modbus address range 0-65535 contains 65536 addresses). Modbus
		 * message size imposes further restriction - see @ref cutehmi-modbus-AbstractDevice-query_limits "query limits".
		 * @param requestId request id. If not @p nullptr, function will set pointee to generated request id before handling the
		 * request.
		 */
		Q_INVOKABLE void requestReadCoils(quint16 address, quint16 amount = 1, QUuid * requestId = nullptr);

		/**
		 * Write coils request. Convenient function that prepares request payload and calls request(FUNCTION_WRITE_COIL, payload).
		 * @param address address of the coil.
		 * @param value value to be set.
		 * @param requestId request id. If not @p nullptr, function will set pointee to generated request id before handling the
		 * request.
		 */
		Q_INVOKABLE void requestWriteCoil(quint16 address, bool value, QUuid * requestId = nullptr);

		/**
		 * Write multiple coils request. Convenient function that prepares request payload and calls request() with
		 * FUNCTION_WRITE_MULTIPLE_COILS function code.
		 * @param address address of the first coil.
		 * @param values array containing values to be set.
		 * @param requestId request id. If not @p nullptr, function will set pointee to generated request id before handling the
		 * request.
		 */
		Q_INVOKABLE void requestWriteMultipleCoils(quint16 address, QJsonArray values, QUuid * requestId = nullptr);

		/**
		 * Read discrete inputs request. Convenient function that prepares request payload and calls request() with
		 * FUNCTION_READ_DISCRETE_INPUTS function code.
		 * @param address starting address.
		 * @param amount number of inputs to query. Note that Modbus specification expects it to be 16 bit unsigned value, so
		 * 65535 is maximal number of inputs that can be queried at once (Modbus address range 0-65535 contains 65536 addresses).
		 * Modbus message size imposes further restriction - see @ref cutehmi-modbus-AbstractDevice-query_limits "query limits".
		 * @param requestId request id. If not @p nullptr, function will set pointee to generated request id before handling the
		 * request.
		 */
		Q_INVOKABLE void requestReadDiscreteInputs(quint16 address, quint16 amount = 1, QUuid * requestId = nullptr);

		/**
		 * Write discrete input request. Convenient function that prepares request payload and calls request() with
		 * FUNCTION_WRITE_DISCRETE_INPUT function code.
		 * @param address address of the discrete input.
		 * @param value value to be set.
		 * @param requestId request id. If not @p nullptr, function will set pointee to generated request id before handling the
		 * request.
		 */
		Q_INVOKABLE void requestWriteDiscreteInput(quint16 address, bool value, QUuid * requestId = nullptr);

		/**
		 * Write multiple discrete inputs request. Convenient function that prepares request payload and calls request() with
		 * FUNCTION_WRITE_MULTIPLE_DISCRETE_INPUTS function code.
		 * @param address address of the first discrete input.
		 * @param values array containing values to be set.
		 * @param requestId request id. If not @p nullptr, function will set pointee to generated request id before handling the
		 * request.
		 */
		Q_INVOKABLE void requestWriteMultipleDiscreteInputs(quint16 address, QJsonArray values, QUuid * requestId = nullptr);

		/**
		 * Read holding registers request. Convenient function that prepares request payload and calls
		 * request() with FUNCTION_READ_HOLDING_REGISTERS function code.
		 * @param address starting address.
		 * @param amount number of registers to query. Note that Modbus specification expects it to be 16 bit unsigned value, so
		 * 65535 is maximal number of registers  that can be queried at once (Modbus address range 0-65535 contains 65536
		 * addresses). Modbus message size imposes further restriction - see
		 * @ref cutehmi-modbus-AbstractDevice-query_limits "query limits".
		 * @param requestId request id. If not @p nullptr, function will set pointee to generated request id before handling the
		 * request.
		 */
		Q_INVOKABLE void requestReadHoldingRegisters(quint16 address, quint16 amount = 1, QUuid * requestId = nullptr);

		/**
		 * Write holding register request. Convenient function that prepares request payload and calls request() with
		 * FUNCTION_WRITE_HOLDING_REGISTER function code.
		 * @param address address of the coil.
		 * @param value value to be set.
		 * @param requestId request id. If not @p nullptr, function will set pointee to generated request id before handling the
		 * request.
		 */
		Q_INVOKABLE void requestWriteHoldingRegister(quint16 address, quint16 value, QUuid * requestId = nullptr);

		/**
		* Write multiple holding registers request. Convenient function that prepares request payload and calls request() with
		* FUNCTION_WRITE_MULTIPLE_HOLDING_REGISTERS function code.
		* @param address address of the first holding register.
		* @param values array containing values to be set.
		 * @param requestId request id. If not @p nullptr, function will set pointee to generated request id before handling the
		 * request.
		*/
		Q_INVOKABLE void requestWriteMultipleHoldingRegisters(quint16 address, QJsonArray values, QUuid * requestId = nullptr);

		/**
		 * Read input registers request. Convenient function that prepares request payload and calls request() with
		 * FUNCTION_READ_INPUT_REGISTERS function code.
		 * @param address starting address.
		 * @param amount number of registers to query. Note that Modbus specification expects it to be 16 bit unsigned value, so
		 * 65535 is maximal number of registers  that can be queried at once (Modbus address range 0-65535 contains 65536
		 * addresses). Modbus message size imposes further restriction - see
		 * @ref cutehmi-modbus-AbstractDevice-query_limits "query limits".
		 * @param requestId request id. If not @p nullptr, function will set pointee to generated request id before handling the
		 * request.
		 */
		Q_INVOKABLE void requestReadInputRegisters(quint16 address, quint16 amount = 1, QUuid * requestId = nullptr);

		/**
		 * Write input register request. Convenient function that prepares request payload and calls
		 * request(FUNCTION_WRITE_INPUT_REGISTER).
		 * @param address address of the input register.
		 * @param value value to be set.
		 * @param requestId request id. If not @p nullptr, function will set pointee to generated request id before handling the
		 * request.
		 */
		Q_INVOKABLE void requestWriteInputRegister(quint16 address, quint16 value, QUuid * requestId = nullptr);

		/**
		* Write multiple input registers request. Convenient function that prepares request payload and calls request() with
		* FUNCTION_WRITE_MULTIPLE_INPUT_REGISTERS function code.
		* @param address address of the first input register.
		* @param values array containing values to be set.
		 * @param requestId request id. If not @p nullptr, function will set pointee to generated request id before handling the
		 * request.
		*/
		Q_INVOKABLE void requestWriteMultipleInputRegisters(quint16 address, QJsonArray values, QUuid * requestId = nullptr);

		/**
		 * Diagonistics request. Convenient function that prepares payload and calls request() with FUNCTION_DIAGNOSTICS function
		 * code.
		 * @param subfunction diagnostics function.
		 * @param data data to be passed to diagnostics function.
		 * @param requestId request id. If not @p nullptr, function will set pointee to generated request id before handling the
		 * request.
		 */
		Q_INVOKABLE void requestDiagnostics(cutehmi::modbus::AbstractDevice::DiagnosticsSubfunction subfunction, quint16 data, QUuid * requestId = nullptr);

		/**
		 * Report slave id request. Convenient function that calls request() with FUNCTION_READ_EXCEPTION_STATUS function code.
		 * @param requestId request id. If not @p nullptr, function will set pointee to generated request id before handling the
		 * request.
		 */
		Q_INVOKABLE void requestReadExceptionStatus(QUuid * requestId = nullptr);

		/**
		 * Report slave id request. Convenient function that calls request() with FUNCTION_FETCH_COMM_EVENT_COUNTER function code.
		 * @param requestId request id. If not @p nullptr, function will set pointee to generated request id before handling the
		 * request.
		 */
		Q_INVOKABLE void requestFetchCommEventCounter(QUuid * requestId = nullptr);

		/**
		 * Report slave id request. Convenient function that calls request() with FUNCTION_FETCH_COMM_EVENT_COUNTER function code.
		 * @param requestId request id. If not @p nullptr, function will set pointee to generated request id before handling the
		 * request.
		 */
		Q_INVOKABLE void requestFetchCommEventLog(QUuid * requestId = nullptr);

		/**
		 * Report slave id request. Convenient function that calls request() with FUNCTION_REPORT_SLAVE_ID function code.
		 * @param requestId request id. If not @p nullptr, function will set pointee to generated request id before handling the
		 * request.
		 */
		Q_INVOKABLE void requestReportSlaveId(QUuid * requestId = nullptr);

		/**
		 * Mask write holding register request. Convenient function that prepares payload and calls request() with
		 * FUNCTION_MASK_WRITE_HOLDING_REGISTER function code. As a result a holding register is modified according to the following
		 * formula: holdingRegister[@a address] = (holdingRegister[@a address] AND @a andMask) OR ( @a orMask AND ! @a andMask).
		 * @param address address of the holding register to mask.
		 * @param andMask mask to be used as AND mask.
		 * @param orMask mask to be used as OR mask.
		 * @param requestId request id. If not @p nullptr, function will set pointee to generated request id before handling the
		 * request.
		 */
		Q_INVOKABLE void requestMaskWriteHoldingRegister(quint16 address, quint16 andMask, quint16 orMask, QUuid * requestId = nullptr);

		/**
		 * Read/write multiple holding registers request. Convenient function that prepares payload and calls request() with
		 * FUNCTION_READ_WRITE_MULTIPLE_HOLDING_REGISTERS function code.
		 * @param readAddress starting address of registers to be read from.
		 * @param amount amount of registers to be read.
		 * @param writeAddress starting address of registers to be written to.
		 * @param values values to be written.
		 * @param requestId request id. If not @p nullptr, function will set pointee to generated request id before handling the
		 * request.
		 */
		Q_INVOKABLE void requestReadWriteMultipleHoldingRegisters(quint16 readAddress, quint16 amount, quint16 writeAddress, QJsonArray values, QUuid * requestId = nullptr);

		/**
		 * Read FIFO queue request. Convenient function that prepares payload and calls request() with FUNCTION_READ_FIFO_QUEUE
		 * function code.
		 * @param address starting address to be read from FIFO queue.
		 * @param requestId request id. If not @p nullptr, function will set pointee to generated request id before handling the
		 * request.
		 */
		Q_INVOKABLE void requestReadFIFOQueue(quint16 address, QUuid * requestId = nullptr);

		/**
		 * Generate read file record subrequest. Helper function that creates JSON object for readFileRecord() function.
		 * @param file file number.
		 * @param address starting address.
		 * @param amount amount of registers to be read.
		 * @return JSON object representing read file record subrequest.
		 *
		 * @see readFileRecord().
		 */
		Q_INVOKABLE QJsonObject readFileRecordSubrequest(quint16 file, quint16 address, quint16 amount);

		/**
		 * Read file record request. Convenient function that prepares payload and calls request() with FUNCTION_READ_FILE_RECORD
		 * function code.
		 * @param subrequests array of subrequests. Each array element should be a JSON object, which can be created with
		 * readFileRecordSubrequest() function.
		 * @param requestId request id. If not @p nullptr, function will set pointee to generated request id before handling the
		 * request.
		 *
		 * @see readFileRecordSubrequest().
		 */
		Q_INVOKABLE void requestReadFileRecord(QJsonArray subrequests, QUuid * requestId = nullptr);

		/**
		 * Generate write file record subrequest. Helper function that creates JSON object for writeFileRecord() function.
		 * @param file file number.
		 * @param address starting address.
		 * @param values values to be written.
		 * @return JSON object representing write file record subrequest.
		 *
		 * @see writeFileRecord().
		 */
		Q_INVOKABLE QJsonObject writeFileRecordSubrequest(quint16 file, quint16 address, QJsonArray values);

		/**
		 * Write file record request. Convenient function that prepares payload and calls request() with FUNCTION_WRITE_FILE_RECORD
		 * function code.
		 * @param subrequests array of subrequests. Each array element should be a JSON object, which can be created with
		 * writeFileRecordSubrequest() function.
		 * @param requestId request id. If not @p nullptr, function will set pointee to generated request id before handling the
		 * request.
		 *
		 * @see writeFileRecordSubrequest().
		 */
		Q_INVOKABLE void requestWriteFileRecord(QJsonArray subrequests, QUuid * requestId = nullptr);

		/**
		 * Modbus function request.
		 * @param function Modbus function code.
		 * @param payload request payload. Payload is specific to each @a function code. Typically it is more convenient to use one
		 * of the helper slots (requestXYZ()) rather than prepare raw payload.
		 * @param requestId request id. If not @p nullptr, function will set pointee to generated request id before handling the
		 * request.
		 *
		 * @internal QJsonObject has been picked as a data structure that represents requests. Several are reasons for this.
		 *		- QJsonObject is implicitly shared, so it can be passed by value through signals/slots mechanism.
		 *		- It naturally fits into QML.
		 *		- It allows for lightweight implementation without the need of creating additionial classes.
		 *		- Derived classes may implement functionality gradually.
		 */
		Q_INVOKABLE void request(cutehmi::modbus::AbstractDevice::Function function, QJsonObject payload, QUuid * requestId = nullptr);

	public slots:
		virtual void open() = 0;

		virtual void close() = 0;

	signals:
		void errored(cutehmi::InplaceError error);

		void stateChanged();

		void readyChanged();

		void maxReadCoilsChanged();

		void maxWriteCoilsChanged();

		void maxReadDiscreteInputsChanged();

		void maxWriteDiscreteInputsChanged();

		void maxReadHoldingRegistersChanged();

		void maxWriteHoldingRegistersChanged();

		void maxReadInputRegistersChanged();

		void maxWriteInputRegistersChanged();

		void maxRequestsChanged();

		void requestCompleted(QJsonObject request, QJsonObject reply);

	protected:
		typedef typename internal::RegisterTraits<internal::Coil>::Container CoilDataContainer;
		typedef typename internal::RegisterTraits<internal::DiscreteInput>::Container DiscreteInputDataContainer;
		typedef typename internal::RegisterTraits<internal::HoldingRegister>::Container HoldingRegisterDataContainer;
		typedef typename internal::RegisterTraits<internal::InputRegister>::Container InputRegisterDataContainer;

		AbstractDevice(QObject * parent = nullptr);

		/**
		  * Destructor.
		  *
		  * @warning References to coils, discrete inputs, holding registers and input registers become invalid before QObject
		  * emits destroyed() signal.
		  */
		~AbstractDevice() override;

		/**
		 * Handle request.
		 *
		 * This function acts as request handler, that derived class must implement. Internally request() function creates request
		 * object and passes it to request handler of derived class. Request object is added to pending requests queue. Derived
		 * class should start processing request. Once request completes derived class is expected to prepare reply and call
		 * handleReply() function. Otherwise it has to remove request from queue by calling takePendingRequest() function and emit
		 * requestCompleted() signal.
		 * @param request request object containing request header and payload.
		 */
		virtual void handleRequest(const QJsonObject & request) = 0;

		const CoilDataContainer & coilData() const;

		CoilDataContainer & coilData();

		const DiscreteInputDataContainer & discreteInputData() const;

		DiscreteInputDataContainer & discreteInputData();

		const HoldingRegisterDataContainer & holdingRegisterData() const;

		HoldingRegisterDataContainer & holdingRegisterData();

		const InputRegisterDataContainer & inputRegisterData() const;

		InputRegisterDataContainer & inputRegisterData();

		QJsonObject pendingRequest(QUuid requestId) const;

		QJsonObject takePendingRequest(QUuid requestId);

	protected slots:
		/**
		 * Reply handler.
		 * @param requestId request id.
		 * @param reply reply data.
		 */
		virtual void handleReply(QUuid requestId, QJsonObject reply);

		void setState(cutehmi::modbus::AbstractDevice::State state);

		void setReady(bool ready);

		void handleError(cutehmi::InplaceError error);

	protected:
		Q_SIGNAL void broke();

		Q_SIGNAL void stopped();

		Q_SIGNAL void started();

	private:
		typedef std::list<QJsonObject> PendingRequestsContainer;

		static void ValidatePayloadAddressKey(const QJsonObject & json, const QString & key = "address");

		static void ValidatePayloadAmountKey(const QJsonObject & json, int max);

		static void ValidatePayloadValueKeyInt(const QJsonObject & json);

		static void ValidatetPayloadValueKeyBool(const QJsonObject & json);

		static void ValidatePayloadReadFileRecordSubrequestsKey(const QJsonObject & json);

		static void ValidatePayloadWriteFileRecordSubrequestsKey(const QJsonObject & json);

		static void ValidateBoolKey(const QJsonObject & json, const QString & key, const QString & path = "");

		static void ValidateNumberKey(const QJsonObject & json, const QString & key, const QString & path = "");

		static void ValidateArrayKey(const QJsonObject & json, const QString & key, const QString & path = "");

		static void ValidateNumberArrayKey(const QJsonObject & json, const QString & key, const QString & path = "");

		static void ValidateBoolArrayKey(const QJsonObject & json, const QString & key, const QString & path = "");

		static void ValidateObjectArrayKey(const QJsonObject & json, const QString & key, const QString & path = "", std::function<void(const QJsonObject & json, const QString & path)> filter = nullptr);

		static void ValidateReadFileRecordSubresponsesKey(const QJsonObject & json, const QString & path = "");

		static void ValidateWriteFileRecordSubresponsesKey(const QJsonObject & json, const QString & path = "");

		bool validateRequest(const QJsonObject & request);

		bool validateReply(const QJsonObject & request, const QJsonObject & reply);

		struct Members
		{
			State state;
			bool ready;
			int maxReadCoils;
			int maxWriteCoils;
			int maxReadDiscreteInputs;
			int maxWriteDiscreteInputs;
			int maxReadHoldingRegisters;
			int maxWriteHoldingRegisters;
			int maxReadInputRegisters;
			int maxWriteInputRegisters;
			int maxRequests;
			InputRegisterDataContainer inputRegisters;
			HoldingRegisterDataContainer holdingRegisters;
			DiscreteInputDataContainer discreteInputs;
			CoilDataContainer coils;
			PendingRequestsContainer pendingRequests;

			Members():
				state(INITIAL_STATE),
				ready(INITIAL_READY),
				maxReadCoils(INITIAL_MAX_READ_COILS),
				maxWriteCoils(INITIAL_MAX_WRITE_COILS),
				maxReadDiscreteInputs(INITIAL_MAX_READ_DISCRETE_INPUTS),
				maxWriteDiscreteInputs(INITIAL_MAX_WRITE_DISCRETE_INPUTS),
				maxReadHoldingRegisters(INITIAL_MAX_READ_HOLDING_REGISTERS),
				maxWriteHoldingRegisters(INITIAL_MAX_WRITE_HOLDING_REGISTERS),
				maxReadInputRegisters(INITIAL_MAX_READ_INPUT_REGISTERS),
				maxWriteInputRegisters(INITIAL_MAX_WRITE_INPUT_REGISTERS),
				maxRequests(INITIAL_MAX_REQUESTS)
			{
			}
		};

		MPtr<Members> m;
};

}
}

Q_DECLARE_METATYPE(cutehmi::modbus::AbstractDevice::State)	// Must use this macro despite using Q_ENUM to register metatype inside Init.

#endif

//(c)C: Copyright © 2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
