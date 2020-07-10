#include <cutehmi/dataacquisition/Init.hpp>

#include <cutehmi/dataacquisition/internal/RecencyCollective.hpp>
#include <cutehmi/dataacquisition/internal/EventCollective.hpp>
#include <cutehmi/dataacquisition/internal/HistoryCollective.hpp>

#include <iostream>

namespace cutehmi {
namespace dataacquisition {

Init::Init():
	Initializer<Init>([]() {
	qRegisterMetaType<cutehmi::dataacquisition::internal::RecencyCollective::ColumnValues>();
	qRegisterMetaType<cutehmi::dataacquisition::internal::HistoryCollective::ColumnValues>();
	qRegisterMetaType<cutehmi::dataacquisition::internal::EventCollective::ColumnValues>();
}
)
{
}

}
}
