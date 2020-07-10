#ifndef H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_SRC_CUTEHMI_DATAACQUISITION_INTERNAL_HELPERS_HPP
#define H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_SRC_CUTEHMI_DATAACQUISITION_INTERNAL_HELPERS_HPP

#include <QList>

namespace cutehmi {
namespace dataacquisition {
namespace internal {

/**
 * Merge column values into single @a COLUMN_VALUES structure, so that elements are stored in particular order.
 * @tparam COLUMN_VALUES column values type.
 * @tparam SIZE size of @a columnValues array.
 * @param mergedValues reference to a structure where results shall be stored.
 * @param columnValues column values arrays. Arrays should be sorted as if they were sorted by @a compare function in descending(!)
 * order (thus typically some sort of "less than" compare function shall be used to maintain descending order).
 * @param compare function which compares
 */
template <typename COLUMN_VALUES, std::size_t SIZE>
void mergeColumnValues(COLUMN_VALUES & result, const COLUMN_VALUES * columnValues, std::function<bool(const COLUMN_VALUES & a, int aIndex, const COLUMN_VALUES & b, int bIndex)> compare)
{

	// Let's introduce a queue, which keeps indices of tables from which elements should be added to the resulting table.
	QList<int> queue;
	for (int i = 0; i < SIZE; i++)
		if (!columnValues[i].tagName.isEmpty())
			queue.append(i);

	// Sort the queue so that elements belonging to a table with highest close time appear first.
	std::sort(queue.begin(), queue.end(), [& columnValues, compare](int a, int b) -> bool {
		return compare(columnValues[a], 0, columnValues[b], 0);
	});
	std::reverse(queue.begin(), queue.end());	// Turn to descending order.

	int indices[SIZE] = {0};	// This array keeps actual elements index for each individual table.
	while (!queue.isEmpty()) {
		int appended = queue.takeFirst();	// First element of queue denotes a table from which values should be taken.
		result.append(columnValues[appended], indices[appended]);
		indices[appended]++;

		// If there are more elements in the table which has been appended, they should find their place in queue.
		if (indices[appended] < columnValues[appended].tagName.count()) {
			int insertIndex = 0;
			while (insertIndex < queue.count()
					&& compare(columnValues[appended], indices[appended], columnValues[queue.at(insertIndex)], indices[queue.at(insertIndex)]))
				insertIndex++;
			queue.insert(insertIndex, appended);
		}
	}
}

}
}
}

#endif
