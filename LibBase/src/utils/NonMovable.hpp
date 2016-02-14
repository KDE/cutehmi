#ifndef CUTEHMI_LIBBASE_SRC_UTILS_NONMOVABLE_HPP
#define CUTEHMI_LIBBASE_SRC_UTILS_NONMOVABLE_HPP

namespace cutehmi {
namespace utils {

/**
 * Non-movable object. This class just locks move constructor and move assignment operator for
 * derived classes.
 */
class NonMovable
{
	protected:
		NonMovable() = default;

	private:
		NonMovable(NonMovable && other) = delete;

		NonMovable & operator =(NonMovable && other) = delete;
};

}
}

#endif
