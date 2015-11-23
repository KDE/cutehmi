#ifndef PLCMANAGER_H
#define PLCMANAGER_H

#include <utils/Singleton.hpp>

#include <QList>

namespace modbus { namespace widgets { class ClientControlWidget; }}
namespace modbus { class Client; }
class QWidget;

class PLCWidgetFactory:
	public utils::Singleton<PLCWidgetFactory>
{
	friend class utils::Singleton<PLCWidgetFactory>;

	public:
		/**
		 * Create client control widget.
		 * @param client object for which widget should be created.
		 * @return client control widget.
		 *
		 * @note caller is responsible for deleting returned widget.
		 *
		 * @todo temporary modbus::Client type of argument - should be AbstractPLCClient.
		 */
		QWidget * createClientControlWidget(modbus::Client * client) const;

	private:
		/**
		 * Default constructor. This class is a singleton and can't be instantiated directly.
		 */
		PLCWidgetFactory();

		/**
		 * Destructor. This class is a singleton and can't be instantiated directly.
		 */
		~PLCWidgetFactory() override;

		/*
		 * Parent widget. Dummy parent widget to fit into Qt-style memory management model built over composite pattern.
		 * Initially all newly created widgets will have @a m_parentWidget set as a parent. Widgets can be embedded
		 * into other containers and Qt may silently reparent them. Either way all the widgets will have some parent set,
		 * so we don't need to worry, which widgets should be deleted and where.
		 */
//		QWidget * m_parentWidget;
};

#endif // PLCMANAGER_H
