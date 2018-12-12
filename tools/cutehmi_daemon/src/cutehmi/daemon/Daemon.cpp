#include "Daemon.hpp"
//#include "Settings.hpp"
//#include "Core.hpp"

#include <thread>
#include <chrono>

namespace cutehmi {
namespace daemon {

//constexpr int Daemon::SLEEP_UNIT;

Daemon::Daemon():
	m_terminate(false)
{
	_init();
}

Daemon::~Daemon()
{
	_destroy();
}

void Daemon::terminate()
{
	m_terminate = true;
}

//void Daemon::exec(int maxFails)
//{
//}

}
}
