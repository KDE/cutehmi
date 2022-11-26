#ifndef H_EXTENSIONS_CUTEHMI_DATAACQUISITION_1_SRC_CUTEHMI_DATAACQUISITION_INTERNAL_HELPERS_HPP
#define H_EXTENSIONS_CUTEHMI_DATAACQUISITION_1_SRC_CUTEHMI_DATAACQUISITION_INTERNAL_HELPERS_HPP

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
template <typename COLUMN_VALUES, int SIZE>
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

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
