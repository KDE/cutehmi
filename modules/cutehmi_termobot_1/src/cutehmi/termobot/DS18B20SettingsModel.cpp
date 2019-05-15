#include "../../../include/cutehmi/termobot/DS18B20SettingsModel.hpp"
#include <cutehmi/Worker.hpp>

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlError>

namespace cutehmi {
namespace termobot {

DS18B20SettingsModel::DS18B20SettingsModel(DatabaseThread * databaseThread):
	m(new Members{false, QAbstractListModel::roleNames(), databaseThread, {}, {*databaseThread}, {*databaseThread}, {*databaseThread}, {*databaseThread}, {std::bind(& DS18B20SettingsModel::busyChanged, this)}})
{
	m->roleNames[static_cast<int>(Role::W1Id)] = "w1Id";
	m->roleNames[static_cast<int>(Role::Description)] = "description";
	m->roleNames[static_cast<int>(Role::DescriptiveColor)] = "descriptiveColor";
	m->roleNames[static_cast<int>(Role::DisconnectionTimeThreshold)] = "disconnectionTimeThreshold";
	m->roleNames[static_cast<int>(Role::TemperatureThreshold)] = "temperatureThreshold";
	m->roleNames[static_cast<int>(Role::CrcTimeThreshold)] = "crcTimeThreshold";
	m->roleNames[static_cast<int>(Role::SuspendTime)] = "suspendTime";
	m->roleNames[static_cast<int>(Role::TemperatureTimeThreshold)] = "temperatureTimeThreshold";

	connect(& m->createWorker, & CreateWorker::ready, this, [this]() {
		endInsertRows();
		--m->workingCounter;
	});

	connect(& m->readWorker, & ReadWorker::ready, this, [this]() {
		if (m->settingsContainer.length() != m->readWorker.settings().length()) {
			beginResetModel();
			m->modelIsResetting = true;
			m->settingsContainer = m->readWorker.settings();
			endResetModel();
			m->modelIsResetting = false;
		}
		--m->workingCounter;
	});

	connect(& m->updateWorker, & UpdateWorker::ready, this, [this]() {
		m->settingsContainer.replace(m->updateWorker.changedRow(), m->updateWorker.settings());
		QModelIndex changedIndex = createIndex(m->updateWorker.changedRow(), 1);
		emit dataChanged(changedIndex, changedIndex);
		--m->workingCounter;
	});

	connect(& m->deleteWorker, & DeleteWorker::ready, this, [this]() {
		for (int i = 0; i < m->settingsContainer.length(); ++i) {
			if (m->settingsContainer.at(i).w1Id == m->deleteWorker.w1Id()) {
				m->settingsContainer.removeAt(i);
				break;
			}
		}
		m->deleteWorker.setW1Id(0);
		endRemoveRows();
		--m->workingCounter;
	});

	++m->workingCounter;
	m->readWorker.work();
}

DS18B20SettingsModel::~DS18B20SettingsModel()
{
}

bool DS18B20SettingsModel::busy() const
{
	return static_cast<bool>(m->workingCounter) || !m->databaseThread->isRunning();
}

QVariant DS18B20SettingsModel::data(const QModelIndex & index, int role) const
{
	if (index.isValid()) {
		SettingsTuple settings = m->settingsContainer[index.row()];
		if (role == static_cast<int>(Role::W1Id))
			return settings.w1Id;
		else if (role == static_cast<int>(Role::Description))
			return settings.description;
		else if (role == static_cast<int>(Role::DescriptiveColor))
			return settings.descriptiveColor;
		else if (role == static_cast<int>(Role::DisconnectionTimeThreshold))
			return settings.disconnectionTimeThreshold;
		else if (role == static_cast<int>(Role::TemperatureThreshold))
			return settings.temperatureThreshold;
		else if (role == static_cast<int>(Role::CrcTimeThreshold))
			return settings.crcTimeThreshold;
		else if (role == static_cast<int>(Role::SuspendTime))
			return settings.suspendTime;
		else if (role == static_cast<int>(Role::TemperatureTimeThreshold))
			return settings.temperatureTimeThreshold;
	}
	return QVariant();
}

int DS18B20SettingsModel::rowCount(const QModelIndex & parent) const
{
	Q_UNUSED(parent);

	CUTEHMI_LOG_DEBUG("entering rowCount");


	if (m->readWorker.isWorking())
		CUTEHMI_LOG_WARNING("Ignoring request, because worker has not finished its previous job yet.");
	else if (m->modelIsResetting)
		CUTEHMI_LOG_WARNING("Ignoring request, because model is being reset.");
	else if (!m->databaseThread->isRunning())
		CUTEHMI_LOG_WARNING("Ignoring request, because database thread is not running.");
	else {
		++m->workingCounter;
		m->readWorker.work();
	}

	return m->settingsContainer.count();
}

bool DS18B20SettingsModel::update(const QString & w1Id, const QString & newDescription, const unsigned int & newDisconnectionTimeThreshold, const int & newTemperatureThreshold, const unsigned int & newCrcTimeThreshold, const unsigned int & newSuspendTime, const unsigned int & newTemperatureTimeThreshold)
{
	if (!m->databaseThread->isRunning()) {
		CUTEHMI_LOG_WARNING("Ignoring request, because database thread is not running.");
		return false;
	}

	// Find a row number which changes and oldDescriptiveColor.
	int row = -1;
	QString oldDescriptiveColor;
	for (int i = 0; i < m->settingsContainer.length(); ++i) {
		if (m->settingsContainer.at(i).w1Id == w1Id) {
			row = i;
			oldDescriptiveColor = m->settingsContainer.at(i).descriptiveColor;
			break;
		}
	}
	if (row == -1)
		return false;

	// Create new settings tuple.

	std::unique_ptr<SettingsTuple> settings(new SettingsTuple{w1Id, newDescription, oldDescriptiveColor, newDisconnectionTimeThreshold, newTemperatureThreshold, newCrcTimeThreshold, newSuspendTime, newTemperatureTimeThreshold});

	// Prepare worker to work.
	m->updateWorker.changedRow(row);
	m->updateWorker.settings(std::move(settings));

	// Increment workingCounter by one.
	++m->workingCounter;

	// Start the worker.
	m->updateWorker.work();

	return true;
}

Qt::ItemFlags DS18B20SettingsModel::flags(const QModelIndex &index) const
{
	Q_UNUSED(index);

	Qt::ItemFlags flags;
	if (m->databaseThread->isRunning()) {
		flags.setFlag(Qt::ItemIsEditable);
		flags.setFlag(Qt::ItemIsUserCheckable);
	} else
		flags.setFlag(Qt::NoItemFlags);

	return flags;
}

bool DS18B20SettingsModel::remove(const QString & w1Id)
{
	if (!m->databaseThread->isRunning()) {
		CUTEHMI_LOG_WARNING("Ignoring request, because database thread is not running.");
		return false;
	}

	// Find row number with a proper w1Id.
	int row = -1;
	for (int i = 0; i < m->settingsContainer.length(); ++i) {
		if (m->settingsContainer.at(i).w1Id == w1Id) {
			row = i;
			break;
		}
	}
	if (row == -1)
		return false;

	beginRemoveRows(QModelIndex(), row, row);
	++m->workingCounter;
	m->deleteWorker.setW1Id(w1Id);
	m->deleteWorker.work();

	return true;
}

bool DS18B20SettingsModel::insert(const QString & description, const unsigned int & disconnectionTimeThreshold, const int & temperatureThreshold, const unsigned int & crcTimeThreshold, const unsigned int & suspendTime, const unsigned int & temperatureTimeThreshold)
{
	if (!m->databaseThread->isRunning()) {
		CUTEHMI_LOG_WARNING("Ignoring request, because database thread is not running.");
		return false;
	}

	std::unique_ptr<SettingsTuple> settings(new SettingsTuple{{}, description, {}, disconnectionTimeThreshold, temperatureThreshold, crcTimeThreshold, suspendTime, temperatureTimeThreshold});

	// Append settings to the end of the list.
	int endRow = m->settingsContainer.count();

	++m->workingCounter;
	beginInsertRows(QModelIndex(), endRow, endRow);
	m->createWorker.settings(std::move(settings));
	m->createWorker.work();
	return true;
}

QHash<int, QByteArray> DS18B20SettingsModel::roleNames() const
{
	return m->roleNames;
}

QVariant DS18B20SettingsModel::descriptiveColorFromW1Id(const QString & w1Id) const
{
	for (int i = 0; i < m->settingsContainer.length(); i++) {
		SettingsTuple settings = m->settingsContainer.at(i);
		if (settings.w1Id == w1Id)
			return QVariant(settings.descriptiveColor);
	}

	return QVariant();
}

QVariant DS18B20SettingsModel::descriptionFromW1Id(const QString & w1Id) const
{
	for (int i = 0; i < m->settingsContainer.length(); i++) {
		SettingsTuple settings = m->settingsContainer.at(i);
		if (settings.w1Id == w1Id)
			return QVariant(settings.description);
	}

	return QVariant();
}

QModelIndex DS18B20SettingsModel::indexFromW1Id(const QString & w1Id) const
{
	for (int i = 0; i < m->settingsContainer.length(); i++) {
		SettingsTuple settings = m->settingsContainer.at(i);
		if (settings.w1Id == w1Id)
			return createIndex(i, 0);
	}

	return QModelIndex();
}

int DS18B20SettingsModel::roleId(const QByteArray & name) const
{
	return roleNames().key(name);
}

DS18B20SettingsModel::CreateWorker::CreateWorker(DatabaseThread &databaseThread):
	Worker::Worker(databaseThread),
	m_connectionName(databaseThread.dbData()->connectionName)
{
}

void DS18B20SettingsModel::CreateWorker::job()
{
	CUTEHMI_LOG_DEBUG("Create worker starts its own job...");

	if (m_settings == nullptr) {
		CUTEHMI_LOG_WARNING("Started create worker with empty m_settings.");
		return;
	}

	// Insert contact with email and phone number into three tables in one statement.
	QSqlQuery query(QSqlDatabase::database(m_connectionName, false));
	query.prepare("INSERT INTO ds18b20 (description, disconnection_time_threshold, "
				  "temperature_threshold, crc_time_threshold, suspend_time, temperature_time_threshold) "
				  "VALUES (:description, :disconnection_time_threshold, :temperature_threshold, "
				  ":crc_time_threshold, :suspend_time, :temperature_time_threshold)");
	query.bindValue(":description", m_settings->description);
	query.bindValue(":disconnection_time_threshold", m_settings->disconnectionTimeThreshold);
	query.bindValue(":temperature_threshold", m_settings->temperatureThreshold);
	query.bindValue(":crc_time_threshold", m_settings->crcTimeThreshold);
	query.bindValue(":suspend_time", m_settings->suspendTime);
	query.bindValue(":temperature_time_threshold", m_settings->temperatureTimeThreshold);
	query.exec();

	m_settings.reset(nullptr);

	CUTEHMI_LOG_DEBUG("Create worker finished.");
}

void DS18B20SettingsModel::CreateWorker::settings(std::unique_ptr<SettingsTuple> newSettings)
{
	m_settings.reset(newSettings.release());
}

DS18B20SettingsModel::ReadWorker::ReadWorker(DatabaseThread & databaseThread):
	Worker::Worker(databaseThread),
	m_connectionName(databaseThread.dbData()->connectionName)
{
}

void DS18B20SettingsModel::ReadWorker::job()
{
	CUTEHMI_LOG_DEBUG("Read worker starts its own job...");
	m_settings.clear();

	QSqlQuery settingsQuery(QSqlDatabase::database(m_connectionName, false));
	settingsQuery.exec("SELECT * FROM ds18b20");
	QSqlRecord record = settingsQuery.record();
	while (settingsQuery.next()) {
		m_settings.push_back(SettingsTuple{
								 settingsQuery.value(record.indexOf("w1_id")).toString(),
								 settingsQuery.value(record.indexOf("description")).toString(),
								 settingsQuery.value(record.indexOf("descriptive_color")).toString(),
								 settingsQuery.value(record.indexOf("disconnection_time_threshold")).toUInt(),
								 settingsQuery.value(record.indexOf("temperature_threshold")).toInt(),
								 settingsQuery.value(record.indexOf("crc_time_threshold")).toUInt(),
								 settingsQuery.value(record.indexOf("suspend_time")).toUInt(),
								 settingsQuery.value(record.indexOf("temperature_time_threshold")).toUInt(),
							 });
	}
	CUTEHMI_LOG_DEBUG("Read worker finished.");
}

const DS18B20SettingsModel::SettingsContainer & DS18B20SettingsModel::ReadWorker::settings() const
{
	return m_settings;
}

DS18B20SettingsModel::UpdateWorker::UpdateWorker(DatabaseThread & databaseThread):
	Worker::Worker(databaseThread),
	m_connectionName(databaseThread.dbData()->connectionName)
{
}

void DS18B20SettingsModel::UpdateWorker::job()
{
	CUTEHMI_LOG_DEBUG("Update worker starts its own job...");

	if (m_settings == nullptr) {
		CUTEHMI_LOG_WARNING("Started update worker with empty m_settings.");
		return;
	}

	QSqlDatabase connection = QSqlDatabase::database(m_connectionName, false);

	// Prepare query for updating settings.
	QSqlQuery updateSettingsQuery(connection);
	updateSettingsQuery.prepare("UPDATE ds18b20 SET description = :description, "
							   "descriptive_color = :descriptive_color, "
							   "disconnection_time_threshold = :disconnection_time_threshold, "
							   "temperature_threshold = :temperature_threshold, "
							   "crc_time_threshold = :crc_time_threshold, "
							   "suspend_time = :suspend_time, "
							   "temperature_time_threshold = :temperature_time_threshold "
							   "WHERE w1_id = :w1_id");
	updateSettingsQuery.bindValue(":description", m_settings->description);
	updateSettingsQuery.bindValue(":descriptive_color", m_settings->descriptiveColor);
	updateSettingsQuery.bindValue(":disconnection_time_threshold", m_settings->disconnectionTimeThreshold);
	updateSettingsQuery.bindValue(":temperature_threshold", m_settings->temperatureThreshold);
	updateSettingsQuery.bindValue(":crc_time_threshold", m_settings->crcTimeThreshold);
	updateSettingsQuery.bindValue(":suspend_time", m_settings->suspendTime);
	updateSettingsQuery.bindValue(":temperature_time_threshold", m_settings->temperatureTimeThreshold);
	updateSettingsQuery.bindValue(":w1_id", m_settings->w1Id);

	// Execute all queries in one transaction.
	updateSettingsQuery.exec();

	CUTEHMI_LOG_DEBUG("Update worker finished.");
}

const DS18B20SettingsModel::SettingsTuple & DS18B20SettingsModel::UpdateWorker::settings() const
{
	return *m_settings;
}

void DS18B20SettingsModel::UpdateWorker::settings(std::unique_ptr<SettingsTuple> newSettings)
{
	m_settings.reset(newSettings.release());
}

const int & DS18B20SettingsModel::UpdateWorker::changedRow() const
{
	return m_changedRow;
}

void DS18B20SettingsModel::UpdateWorker::changedRow(const int &newRow)
{
	m_changedRow = newRow;
}

DS18B20SettingsModel::DeleteWorker::DeleteWorker(DatabaseThread & databaseThread):
	Worker::Worker(databaseThread),
	m_connectionName(databaseThread.dbData()->connectionName)
{
}

void DS18B20SettingsModel::DeleteWorker::job()
{
	CUTEHMI_LOG_DEBUG("Delete worker starts its own job...");

	QSqlQuery query(QSqlDatabase::database(m_connectionName, false));
	query.prepare("DELETE FROM ds18b20 WHERE w1_id = :w1_id");
	query.bindValue(":w1_id", m_w1Id);
	query.exec();

	CUTEHMI_LOG_DEBUG("Delete worker finished.");
}

void DS18B20SettingsModel::DeleteWorker::setW1Id(const QString & w1Id)
{
	m_w1Id = w1Id;
}

const QString & DS18B20SettingsModel::DeleteWorker::w1Id() const
{
	return m_w1Id;
}

}
}

//(c)WZ: Copyright © 2018, Wojciech Zygmuntowicz. All rights reserved.
//(c)WZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
