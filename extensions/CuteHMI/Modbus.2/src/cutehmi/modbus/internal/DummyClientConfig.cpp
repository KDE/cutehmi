#include <cutehmi/modbus/internal/DummyClientConfig.hpp>

namespace cutehmi {
namespace modbus {
namespace internal {

constexpr int DummyClientConfig::INITIAL_OPEN_LATENCY;
constexpr int DummyClientConfig::INITIAL_CLOSE_LATENCY;
constexpr int DummyClientConfig::INITIAL_LATENCY;

DummyClientConfig::DummyClientConfig(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

int DummyClientConfig::openLatency() const
{
	QReadLocker locker(& m->lock);
	return m->openLatency;
}

void DummyClientConfig::setOpenLatency(int openLatency)
{
	QWriteLocker locker(& m->lock);
	m->openLatency = openLatency;
	emit configChanged();
}

int DummyClientConfig::closeLatency() const
{
	QReadLocker locker(& m->lock);
	return m->closeLatency;
}

void DummyClientConfig::setCloseLatency(int closeLatency)
{
	QWriteLocker locker(& m->lock);
	m->closeLatency = closeLatency;
	emit configChanged();
}

int DummyClientConfig::latency() const
{
	QReadLocker locker(& m->lock);
	return m->latency;
}

void DummyClientConfig::setLatency(int latency)
{
	QWriteLocker locker(& m->lock);
	m->latency = latency;
	emit configChanged();
}

}
}
}

//(c)C: Copyright © 2019, Michal Policht <michpolicht@gmail.com>, Mr CuteBOT <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
