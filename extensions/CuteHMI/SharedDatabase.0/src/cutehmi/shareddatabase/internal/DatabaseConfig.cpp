#include <cutehmi/shareddatabase/internal/DatabaseConfig.hpp>

#include <cutehmi/shareddatabase/Database.hpp>

#include <QUuid>

namespace cutehmi {
namespace shareddatabase {
namespace internal {

DatabaseConfig::Data::Data():
	type(Database::INITIAL_TYPE),
	host(Database::INITIAL_HOST),
	port(Database::INITIAL_PORT),
	name(Database::INITIAL_NAME),
	user(Database::INITIAL_USER),
	password(Database::INITIAL_PASSWORD),
	connectionName(QUuid::createUuid().toString())
{
}

DatabaseConfig::DatabaseConfig():
	m_data(new Data)
{
}

const DatabaseConfig::DataPtr & DatabaseConfig::data() const
{
	return m_data;
}

DatabaseConfig::DataPtr & DatabaseConfig::data()
{
	return m_data;
}

}
}
}
