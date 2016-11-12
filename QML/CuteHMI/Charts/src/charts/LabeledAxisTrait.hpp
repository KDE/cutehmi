#ifndef LABELEDAXISTRAIT_H
#define LABELEDAXISTRAIT_H

namespace cutehmi {
namespace charts {

template <class DERIVED>
class LabeledAxisTrait
{
	public:
		LabeledAxisTrait();

	private:
		const DERIVED & derived() const;

		DERIVED & derived();
};

template <class DERIVED>
LabeledAxisTrait<DERIVED>::LabeledAxisTrait()
{
}

template <class DERIVED>
DERIVED & LabeledAxisTrait<DERIVED>::derived()
{
	return static_cast<DERIVED &>(*this);
}

template <class DERIVED>
const DERIVED & LabeledAxisTrait<DERIVED>::derived() const
{
	return static_cast<const DERIVED &>(*this);
}

}
}

#endif // LABELEDAXISTRAIT_H
