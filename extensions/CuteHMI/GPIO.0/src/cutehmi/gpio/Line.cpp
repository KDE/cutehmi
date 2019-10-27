#include <cutehmi/gpio/Line.hpp>

namespace cutehmi {
namespace gpio {

Line::Line(gpiod_line * line, QObject * parent):
	QObject(parent),
	m(new Members(line))
{
	readLineInfo();
	connect(& m->monitorThread, & internal::LineEventMonitorThread::eventDetected, this, & Line::handleLineEvent);
}

Line::~Line()
{
	releaseLine();
}

int Line::value() const
{
	return m->value;
}

void Line::setValue(int value)
{
	if (m->value != value) {
		m->value = value;
		emit valueChanged();
	}
}

QString Line::name() const
{
	return m->name;
}

LineConfig * Line::config() const
{
	return m->config;
}

void Line::setConfig(LineConfig * config)
{
	if (m->config != config) {
		m->config = config;
		if (m->config)
			requestLine();
		else
			releaseLine();
		emit configChanged();
	}
}

QString Line::consumer() const
{
	CUTEHMI_WARNING("line consumer " << m->consumer);
	return m->consumer;
}

void Line::setConsumer(const QString & consumer)
{
	if (m->consumer != consumer) {
		m->consumer = consumer.toUtf8();
		if (m->config)
			requestLine();
		emit consumerChanged();
	}
}

bool Line::used() const
{
	return m->used;
}

void Line::requestLine()
{
	CUTEHMI_ASSERT(m->config != nullptr, "config must not be nullptr");


	// Release line (if it was acquired).

	releaseLine();


	// Set consumer.

	// Overcome weird behavior of libgpiod, which sets consumer to "?", if empty string is provided in the request.
	if (m->consumer.isEmpty())
		m->consumer = "Unnamed Consumer";

	m->requestConfig.consumer = m->consumer.data();


	// Configure reuest type.

	switch (m->config->direction()) {
		case LineConfig::DIRECTION_OUTPUT:
			m->requestConfig.request_type = GPIOD_LINE_REQUEST_DIRECTION_OUTPUT;
			// Set Qt::DirectConnection explicitly, because it is important to deliver all valueChanged() signals.
			connect(this, & Line::valueChanged, this, & Line::requestValue, Qt::DirectConnection);
			break;
		case LineConfig::DIRECTION_INPUT:
			m->requestConfig.request_type = GPIOD_LINE_REQUEST_EVENT_BOTH_EDGES;
			break;
		default:
			CUTEHMI_CRITICAL("Unrecognized line direction code (" << m->config->direction() << ").");
	}


	// Configure flags.

	m->requestConfig.flags = 0;

	if (m->config->openDrain())
		m->requestConfig.flags |= GPIOD_LINE_REQUEST_FLAG_OPEN_DRAIN;

	if (m->config->openSource())
		m->requestConfig.flags |= GPIOD_LINE_REQUEST_FLAG_OPEN_SOURCE;

	switch (m->config->activeState()) {
		case LineConfig::ACTIVE_STATE_LOW:
			m->requestConfig.flags |= GPIOD_LINE_REQUEST_FLAG_ACTIVE_LOW;
			break;
		case LineConfig::ACTIVE_STATE_HIGH:
			// High is default (i.e. flags = 0).
			break;
		default:
			CUTEHMI_CRITICAL("Unrecognized active state code (" << m->config->activeState() << ").");
	}


	// Request line.

	gpiod_line_request(m->line, & m->requestConfig, 0);


	// Verify if config settings have been successfully set.
	///@todo Turn CUTEHMI_DIE macros to exceptions.

	switch (m->config->direction()) {
		case LineConfig::DIRECTION_OUTPUT:
			if (gpiod_line_direction(m->line) != GPIOD_LINE_DIRECTION_OUTPUT)
				CUTEHMI_DIE("Requested direction and the one that line has been set to do not match.");
			break;
		case LineConfig::DIRECTION_INPUT:
			if (gpiod_line_direction(m->line) != GPIOD_LINE_DIRECTION_INPUT)
				CUTEHMI_DIE("Requested direction and the one that line has been set to do not match.");
			break;
		default:
			CUTEHMI_CRITICAL("Unrecognized line direction code (" << m->config->direction() << ").");
	}

	switch (m->config->activeState()) {
		case LineConfig::ACTIVE_STATE_LOW:
			if (gpiod_line_active_state(m->line) != GPIOD_LINE_ACTIVE_STATE_LOW)
				CUTEHMI_DIE("Requested active state and the one that line has been set to do not match.");
			break;
		case LineConfig::ACTIVE_STATE_HIGH:
			if (gpiod_line_active_state(m->line) != GPIOD_LINE_ACTIVE_STATE_HIGH)
				CUTEHMI_DIE("Requested active state and the one that line has been set to do not match.");
			break;
		default:
			CUTEHMI_CRITICAL("Unrecognized active state code (" << m->config->activeState() << ").");
	}

	if (m->config->openDrain() && (!gpiod_line_is_open_drain(m->line)))
		CUTEHMI_DIE("Could not set requested open drain configuration.");

	if (m->config->openSource() && (!gpiod_line_is_open_source(m->line)))
		CUTEHMI_DIE("Could not set requested open source configuration.");

	if (m->consumer != gpiod_line_consumer(m->line))
		CUTEHMI_DIE("Requested consumer name ('%s') and the one that has been assigned to the line ('%s') do not match", m->consumer.data(), gpiod_line_consumer(m->line));


	// Update line info.

	readLineInfo();


	// Start monitoring thread for input direction.

	if (m->config->direction() == LineConfig::DIRECTION_INPUT) {
		m->monitorThread.setLine(m->line);
		m->monitorThread.start();
	}
}

void Line::releaseLine()
{
	if (gpiod_line_is_requested(m->line)) {
		m->monitorThread.requestInterruption();
		m->monitorThread.wait();

		disconnect(this, & Line::valueChanged, this, & Line::requestValue);

		gpiod_line_release(m->line);

		readLineInfo();
	}
}

void Line::requestValue()
{
	gpiod_line_set_value(m->line, m->value);
}

void Line::handleLineEvent(gpiod_line_event event)
{
	switch (event.event_type) {
		case GPIOD_LINE_EVENT_RISING_EDGE:
			setValue(1);
			break;
		case GPIOD_LINE_EVENT_FALLING_EDGE:
			setValue(0);
			break;
		default:
			CUTEHMI_WARNING("Unrecognized line event type (" << event.event_type << ").");
	}
}

void Line::readLineInfo()
{
	if (gpiod_line_needs_update(m->line))
		gpiod_line_update(m->line);
	m->name = gpiod_line_name(m->line);
	m->consumer = gpiod_line_consumer(m->line);
	m->used = gpiod_line_is_used(m->line);
}

}
}

//(c)C: Copyright © 2019, CuteBOT <michpolicht@gmail.com>, Michal Policht <michal@policht.pl>, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
