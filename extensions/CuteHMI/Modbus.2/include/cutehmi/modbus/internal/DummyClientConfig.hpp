#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_DUMMYCLIENTCONFIG_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_DUMMYCLIENTCONFIG_HPP

#include "common.hpp"

#include <QObject>
#include <QReadWriteLock>

namespace cutehmi {
namespace modbus {
namespace internal {

class CUTEHMI_MODBUS_PRIVATE DummyClientConfig:
	public QObject
{
		Q_OBJECT

	public:
		static constexpr int INITIAL_OPEN_LATENCY = 1000;
		static constexpr int INITIAL_CLOSE_LATENCY = 1000;
		static constexpr int INITIAL_LATENCY = 1000;

		explicit DummyClientConfig(QObject * parent = nullptr);

		int openLatency() const;

		void setOpenLatency(int openLatency);

		int closeLatency() const;

		void setCloseLatency(int closeLatency);

		int latency() const;

		void setLatency(int latency);

	signals:
		void configChanged();

	private:
		struct Members
		{
			int	openLatency = INITIAL_OPEN_LATENCY;
			int closeLatency = INITIAL_CLOSE_LATENCY;
			int latency = INITIAL_LATENCY;
			mutable QReadWriteLock lock;
		};

		MPtr<Members> m;
};

}
}
}

#endif
