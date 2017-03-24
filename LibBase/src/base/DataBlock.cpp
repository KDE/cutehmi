#include "../../include/base/DataBlock.hpp"

namespace cutehmi {
namespace base {

DataBlock::DataBlock():
	m(new Members{nullptr})
{
}

DataBlock * DataBlock::child() const
{
	return m->child.get();
}

void DataBlock::append(std::unique_ptr<DataBlock> block)
{
	if (m->child)
		m->child->append(std::move(block));
	else
		m->child = std::move(block);
}

int DataBlock::count() const
{
	int ctr = 0;
	for (const_iterator it = begin(); it != end(); ++it)
		ctr++;
	return ctr;
}

DataBlock::iterator DataBlock::begin()
{
	return iterator(this);
}

DataBlock::const_iterator DataBlock::begin() const
{
	return const_iterator(this);
}

DataBlock::iterator DataBlock::end()
{
	return iterator();
}

DataBlock::const_iterator DataBlock::end() const
{
	return const_iterator();
}


}
}
