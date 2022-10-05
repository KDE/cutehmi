#ifndef ABSTRACTWRITERATTACHEDTYPE_HPP
#define ABSTRACTWRITERATTACHEDTYPE_HPP

#include "internal/common.hpp"

//<CuteHMI.Workarounds.Qt5Compatibility-1.workaround target="Qt" cause="Qt5">
#include <cutehmi/workarounds/qt5compatibility/qsizetype.hpp>
//</CuteHMI.Workarounds.Qt5Compatibility-1.workaround>

#include <cutehmi/dataacquisition/AbstractWriter.hpp>

#include <QObject>
#include <QQmlListProperty>
#include <QQmlEngine>

namespace cutehmi {
namespace dataacquisition {

class CUTEHMI_DATAACQUISITION_API AbstractWriterAttachedType:
	public QObject
{
		Q_OBJECT
		Q_PROPERTY(QQmlListProperty<cutehmi::dataacquisition::AbstractWriter> targets READ targetList CONSTANT)
		QML_ANONYMOUS

	public:
		explicit AbstractWriterAttachedType(QObject * parent = nullptr);

		QQmlListProperty<cutehmi::dataacquisition::AbstractWriter> targetList() const;

	protected:
		typedef QList<cutehmi::dataacquisition::AbstractWriter *> TargetsContainer;

		const TargetsContainer & targets() const;

	private:
		TargetsContainer & targets();

		//<CuteHMI.Workarounds.Qt5Compatibility-1.workaround target="Qt" cause="Qt5">
		static cutehmi::workarounds::qt5compatibility::sizeType TargetListCount(QQmlListProperty<AbstractWriter> * property);

		static AbstractWriter * TargetListAt(QQmlListProperty<AbstractWriter> * property, cutehmi::workarounds::qt5compatibility::sizeType index);
		//</CuteHMI.DataAcquisition-2.workaround target="Qt" cause="Qt5">

		static void TargetListClear(QQmlListProperty<AbstractWriter> * property);

		static void TargetListAppend(QQmlListProperty<AbstractWriter> * property, AbstractWriter * value);

		struct Members {
			TargetsContainer targets;
			QQmlListProperty<cutehmi::dataacquisition::AbstractWriter> targetList;
			cutehmi::dataacquisition::AbstractWriter * target;

			Members(AbstractWriterAttachedType * p_parent):
				targetList(p_parent, & targets, & AbstractWriterAttachedType::TargetListAppend, & AbstractWriterAttachedType::TargetListCount, & AbstractWriterAttachedType::TargetListAt, & AbstractWriterAttachedType::TargetListClear),
				target(nullptr)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif // ABSTRACTWRITERATTACHEDTYPE_HPP
