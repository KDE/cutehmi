#include "RunnersRegister.hpp"
#include "IRunner.hpp"

namespace cutehmi {
namespace base {

void RunnersRegister::add(IRunner * runner)
{
	m_runners.append(runner);
}

void RunnersRegister::clear()
{
	m_runners.clear();
}

void RunnersRegister::start()
{
	for (IRunner * runner : m_runners)
		runner->start();
}

void RunnersRegister::stop()
{
	for (IRunner * runner : m_runners)
		runner->stop();
}

}
}
