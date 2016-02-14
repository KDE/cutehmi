#ifndef CUTEHMI_LIBBASE_SRC_UTILS_NONCOPYABLE_HPP
#define CUTEHMI_LIBBASE_SRC_UTILS_NONCOPYABLE_HPP

namespace cutehmi {
namespace utils {

/**
 * Non-copyable object. This class just locks copy constructor and assignment operator for
 * derived classes.
 */
class NonCopyable
{
	protected:
		NonCopyable() = default;

	private:
		NonCopyable(const NonCopyable & other) = delete;

		NonCopyable & operator =(const NonCopyable & other) = delete;
};

}
}

#endif
