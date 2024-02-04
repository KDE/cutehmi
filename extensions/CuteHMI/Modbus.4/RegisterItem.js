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
