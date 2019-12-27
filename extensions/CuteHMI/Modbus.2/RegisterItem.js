function onCompleted()
{
	delegate[delegateProperty] = controller.value
	controller.valueUpdated.connect(onValueUpdatedFromBackend)
	if (!readOnly)
		p.delegateValueChanged.connect(onValueChangedFromFrontend)
}

function onDestruction()
{
	controller.valueUpdated.disconnect(onValueUpdatedFromBackend)
	p.delegateValueChanged.disconnect(onValueChangedFromFrontend)
}

function onReadOnlyChanged()
{
	if (readOnly)
		p.delegateValueChanged.disconnect(onValueChangedFromFrontend)
	else
		p.delegateValueChanged.connect(onValueChangedFromFrontend)
}

function onValueUpdatedFromBackend()
{
	// Value may get updated to a different value than requested or it may get updated by a different controller.
	// This may cause subsequent emission of delegateValueChanged signal, so disconnect it temporarily.
	if (!readOnly)
		p.delegateValueChanged.disconnect(onValueChangedFromFrontend)
	delegate[delegateProperty] = controller.value
	if (!readOnly)
		p.delegateValueChanged.connect(onValueChangedFromFrontend)
}

function onValueChangedFromFrontend()
{
	controller.value = p.delegateValue
}

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
