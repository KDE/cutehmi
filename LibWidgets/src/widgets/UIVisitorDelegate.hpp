#ifndef UIDELEGATE_H
#define UIDELEGATE_H

#include "../platform.hpp"

#include <QMenu>

#include <memory>

namespace cutehmi {
namespace widgets {

/**
 * UI visitor delegate.
 */
class CUTEHMI_WIDGETS_API UIVisitorDelegate
{
	public:
		/**
		 * Context menu proxy. This is used to customize context menu in the visited object.
		 */
		class CUTEHMI_WIDGETS_API ContextMenuProxy
		{
			public:
				/**
				 * Constructor.
				 * @param menu reference to a menu pointer. Pointer should probably point to @p nullptr as
				 * visiting object may reset it.
				 */
				ContextMenuProxy(std::unique_ptr<QMenu> & menu);

				/**
				 * Pass the menu from the caller to the visited object.
				 * @param menu menu to be passed.
				 */
				void pass(std::unique_ptr<QMenu> menu);

			private:
				std::unique_ptr<QMenu> & m_menu;
		};

		virtual ~UIVisitorDelegate() = default;

		/**
		 * Visit context menu proxy. Default implementation does nothing.
		 * @param proxy context menu proxy.
		 */
		virtual void visit(ContextMenuProxy & proxy);
};

}
}

#endif // UIDELEGATE_H
