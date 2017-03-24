#include "../include/base/CuteHMI.hpp"

namespace cutehmi {
namespace base {

CuteHMI & CuteHMI::Instance()
{
	return *(InstancePtr().get());
}

void CuteHMI::Destroy()
{
	InstancePtr().reset();
}

Project * CuteHMI::project() const
{
	return & m->project;
}

CuteHMI::CuteHMI():
	m(new Members)
{
}

std::unique_ptr<CuteHMI> & CuteHMI::InstancePtr()
{
	static std::unique_ptr<CuteHMI> instance(new CuteHMI);
	return instance;
}

}
}
