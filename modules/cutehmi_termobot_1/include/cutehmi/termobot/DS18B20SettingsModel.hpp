#ifndef H_MODULES_CUTEHMI_u_TERMOBOT_u_1_INCLUDE_CUTEHMI_TERMOBOT_DS18B20SETTINGSMODEL_HPP
#define H_MODULES_CUTEHMI_u_TERMOBOT_u_1_INCLUDE_CUTEHMI_TERMOBOT_DS18B20SETTINGSMODEL_HPP

#include "internal/common.hpp"
#include "internal/WorkingCounter.hpp"

#include "../../../src/cutehmi/termobot/DatabaseThread.hpp"

#include <QAbstractListModel>

namespace cutehmi {
namespace termobot {

class CUTEHMI_TERMOBOT_API DS18B20SettingsModel:
	public QAbstractListModel
{
	Q_OBJECT

	public:
		Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)

		DS18B20SettingsModel(DatabaseThread * databaseThread);

		~DS18B20SettingsModel();

		bool busy() const;

		// read implementation
		QVariant data(const QModelIndex & index, int role) const override;

		int rowCount(const QModelIndex & parent) const override;

		// update implementation
		Q_INVOKABLE bool update(const QString & w1Id, const QString & newDescription, const unsigned int & newDisconnectionTimeThreshold, const int & newTemperatureThreshold, const unsigned int & newCrcTimeThreshold, const unsigned int & newSuspendTime, const unsigned int & newTemperatureTimeThreshold);

		Qt::ItemFlags flags(const QModelIndex & index) const override;

		// delete implementation
		Q_INVOKABLE bool remove(const QString & w1Id);

		// create implementation
		Q_INVOKABLE bool insert(const QString & description, const unsigned int & disconnectionTimeThreshold, const int & temperatureThreshold, const unsigned int & crcTimeThreshold, const unsigned int & suspendTime, const unsigned int & temperatureTimeThreshold);

		QHash<int, QByteArray> roleNames() const override;

		// methods implemented for the sake of special use in QML
		Q_INVOKABLE QVariant descriptiveColorFromW1Id(const QString & w1Id) const;

		Q_INVOKABLE QVariant descriptionFromW1Id(const QString & w1Id) const;

	signals:
		void busyChanged();

	private:
		enum Role : int {
			W1Id = Qt::UserRole,
			Description,
			DescriptiveColor,
			DisconnectionTimeThreshold,
			TemperatureThreshold,
			CrcTimeThreshold,
			SuspendTime,
			TemperatureTimeThreshold
		};

		struct SettingsTuple
		{
				QString w1Id;
				QString description;
				QString descriptiveColor;
				unsigned int disconnectionTimeThreshold;
				int temperatureThreshold;
				unsigned int crcTimeThreshold;
				unsigned int suspendTime;
				unsigned int temperatureTimeThreshold;
		};

		typedef QList<SettingsTuple> SettingsContainer;

		class CreateWorker:
				public Worker
		{
			public:
				CreateWorker(DatabaseThread & databaseThread);

				void job() override;

				void settings(std::unique_ptr<SettingsTuple> newSettings);

			private:
				QString m_connectionName;
				std::unique_ptr<SettingsTuple> m_settings;
		};

		class ReadWorker:
				public Worker
		{
			public:
				ReadWorker(DatabaseThread & DatabaseThread);

				void job() override;

				const SettingsContainer & settings() const;

			private:
				QString m_connectionName;
				SettingsContainer m_settings;
		};

		class UpdateWorker:
				public Worker
		{
			public:
				UpdateWorker(DatabaseThread & databaseThread);

				void job() override;

				const SettingsTuple & settings() const;

				void settings(std::unique_ptr<SettingsTuple> newSettings);

				const int & changedRow() const;

				void changedRow(const int & newRow);

			private:
				int m_changedRow;
				QString m_connectionName;
				std::unique_ptr<SettingsTuple> m_settings;
		};

		class DeleteWorker:
				public Worker
		{
			public:
				DeleteWorker(DatabaseThread & databaseThread);

				void job() override;

				void setW1Id(const QString & w1Id);

				const QString & w1Id() const;

			private:
				QString m_connectionName;
				QString m_w1Id;
		};

		struct Members
		{
			bool modelIsResetting;
			QHash<int, QByteArray> roleNames;
			DatabaseThread * databaseThread;
			SettingsContainer settingsContainer;
			mutable CreateWorker createWorker;
			mutable ReadWorker readWorker;
			mutable UpdateWorker updateWorker;
			mutable DeleteWorker deleteWorker;
			mutable internal::WorkingCounter workingCounter;
		};

		MPtr<Members> m;
};

}
}


#endif

//(c)WZ: Copyright © 2018, Wojciech Zygmuntowicz. All rights reserved.
//(c)WZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
