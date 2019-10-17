#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_ITERABLETASKS_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_ITERABLETASKS_HPP

#include "common.hpp"
#include "RegisterTraits.hpp"

#include <cutehmi/NonCopyable.hpp>

namespace cutehmi {
namespace modbus {

class AbstractDevice;

namespace internal {

class CUTEHMI_MODBUS_PRIVATE IterableTasks:
	public cutehmi::NonCopyable
{
	public:
		typedef typename RegisterTraits<Coil>::Container CoilDataContainer;
		typedef typename RegisterTraits<DiscreteInput>::Container DiscreteInputDataContainer;
		typedef typename RegisterTraits<HoldingRegister>::Container HoldingRegisterDataContainer;
		typedef typename RegisterTraits<InputRegister>::Container InputRegisterDataContainer;

		virtual ~IterableTasks() = default;

		/**
		 * Run next task.
		 * @return @p false if there are no more tasks to run, @p true otherwise.
		 */
		virtual bool runNext() = 0;

		/**
		 * Reset tasks iterator.
		 */
		virtual void reset() = 0;

		const CoilDataContainer & coilData(const AbstractDevice * device) const;

		const DiscreteInputDataContainer & discreteInputData(const AbstractDevice * device) const;

		const HoldingRegisterDataContainer & holdingRegisterData(const AbstractDevice * device) const;

		const InputRegisterDataContainer & inputRegisterData(const AbstractDevice * device) const;
};

}
}
}

#endif
