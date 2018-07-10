function onCompleted()
{
	delegate[delegateProperty] = controller.value
	controller.valueUpdated.connect(onValueUpdatedFromBackend)
	if (!readOnly)
		p.delegateValueChanged.connect(onValueChangedFromFrontend)
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

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
