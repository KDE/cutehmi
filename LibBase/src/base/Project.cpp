#include "Project.hpp"

namespace cutehmi {
namespace base {

QString Project::Error::str() const
{
	switch (code()) {
		case FILE_NOT_EXISTS:
			return tr("File does not exist.");
		case FILE_UNABLE_TO_OPEN:
			return tr("Could not open file.");
		case FILE_EMPTY_NAME:
			return tr("Empty file name.");
		default:
			return base::Error::str();
	}
}

Project::Project()
{
}

}
}
