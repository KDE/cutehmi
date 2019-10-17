#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_REGISTER16CONTROLLER_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_REGISTER16CONTROLLER_HPP

#include "internal/common.hpp"
#include "internal/RegisterControllerMixin.hpp"
#include "Register16.hpp"
#include "AbstractRegisterController.hpp"

#include <QBasicTimer>

namespace cutehmi {
namespace modbus {

/**
 * Register controller for 16 bit registers.
 */
class CUTEHMI_MODBUS_API Register16Controller:
	public AbstractRegisterController,
	protected internal::RegisterControllerMixin<Register16Controller>
{
		Q_OBJECT

		friend class internal::RegisterControllerMixin<Register16Controller>;
		typedef internal::RegisterControllerMixin<Register16Controller> Mixin;

	public:
		enum Encoding {
			INT16,
			UINT16
		};
		Q_ENUM(Encoding)

		static constexpr qreal INITIAL_VALUE = 0.0;
		static constexpr qreal INITIAL_VALUE_SCALE = 1.0;
		static constexpr Encoding INITIAL_ENCODING = UINT16;

		Q_PROPERTY(qreal value READ value WRITE setValue NOTIFY valueChanged)
		Q_PROPERTY(qreal valueScale READ valueScale WRITE setValueScale NOTIFY valueScaleChanged)
		Q_PROPERTY(Encoding encoding READ encoding WRITE setEncoding NOTIFY encodingChanged)

		Register16Controller(QObject * parent = nullptr);

		~Register16Controller() override;

		qreal value() const;

		void setValue(qreal value);

		qreal valueScale() const;

		void setValueScale(qreal valueScale);

		Encoding encoding() const;

		void setEncoding(Encoding encoding);

	public slots:
		void writeValue();

	signals:
		void valueChanged();

		void valueUpdated();

		void valueScaleChanged();

		void encodingChanged();

		void valueWritten();

		void valueFailed();

		void valueMismatch();

	protected:
		virtual AbstractDevice::Function readRegistersFunction() const = 0;

		virtual AbstractDevice::Function writeRegisterFunction() const = 0;

		virtual void requestWriteRegister(quint16 address, quint16 value, QUuid * requestId) const = 0;

		virtual Register16 * registerAt(quint16 address) const = 0;

		void timerEvent(QTimerEvent * event) override;

		quint16 bytes() const override;

		void onDeviceDestroyed() override;

	protected slots:
		void onRequestCompleted(QJsonObject request, QJsonObject reply) override;

		void resetRegister();

	private:
		void updateValue();

		void updateValue(quint16 value);

		void updateValue(const QJsonValue & value);

		static qreal Decode(quint16 value, Encoding encoding);

		static quint16 Encode(qreal value, Encoding encoding);

		static bool ValidateEncoding(qreal value, Encoding encoding);

		void requestWrite(qreal value);

		bool verifyRegisterValue() const;

	private:
		struct Members
		{
			qreal value;
			qreal valueScale;
			Encoding encoding;
			bool postponedWritePending;
			bool adjustingValue;
			qreal requestedValue;
			Register16 * register16;
			QUuid requestId;
			QBasicTimer writeTimer;

			Members():
				value(INITIAL_VALUE),
				valueScale(INITIAL_VALUE_SCALE),
				encoding(INITIAL_ENCODING),
				postponedWritePending(false),
				adjustingValue(false),
				requestedValue(0.0),
				register16(nullptr)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif
