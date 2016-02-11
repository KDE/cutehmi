#ifndef CUTEHMI_APPFULL_SRC_ABSTRACTQMLWIDGETWRAPPER_HPP
#define CUTEHMI_APPFULL_SRC_ABSTRACTQMLWIDGETWRAPPER_HPP

#include <QStringList>
#include <QUrl>
#include <QObject>

class QQmlEngine;
class QQmlContext;
class QQuickItem;
class QQmlComponent;
class QWidget;

class AbstractQMLWidgetWrapper:
	public QObject
{
	Q_OBJECT

	public:
		/**
		 * Get widget providing QML view.
		 * @return widget providing QML view.
		 */
		virtual QWidget * widget() const = 0;

		/**
		 * Get content item. Content item is a root item for all visual items in the QML scene.
		 * @return content item.
		 */
		virtual QQuickItem * contentItem() const = 0;

		/**
		 * Get root context.
		 * @return root context.
		 */
		virtual QQmlContext * rootContext() const;

		/**
		 * Set visual component source. Visual component is created within project context (projectContext()).
		 * @param url visual component source.
		 */
		virtual void setSource(const QUrl & url);

		/**
		 * Get project context. Project context is created as a child context of root context (rootContext()).
		 * @return project context.
		 */
		QQmlContext * projectContext() const;

		/**
		 * Get proto-visual-component. QQmlComponent class wraps QML component definition.
		 * From this definition visual component may be created.
		 * @return proto-visual-component.
		 */
		QQmlComponent * protoVisualComponent() const;

		/**
		 * Get QML import path list.
		 * @return list of import paths from which QML files can be imported.
		 */
		QStringList importPathList() const;

		/**
		 * Add QML import path.
		 * @param dir QML import path to be added.
		 */
		void addImportPath(const QString & dir);

		/**
		 * Reset visual component.
		 * @param component component to be set in place of an old one or @p nullptr to show empty view.
		 */
		void resetVisualComponent(QQuickItem * component = nullptr);

		/**
		 * Renew project context.
		 */
		void renewProjectContext();

	public slots:
		/**
		 * Show visual component. Visual component is created from proto-visual-component.
		 * This function does nothing if proto-visual-component has no data. After calling this
		 * function a proto-visual-component will be renewed, thus subsequent call of this
		 * function will have no effect without setting data for newly created proto-visual-component.
		 * Proto-visual-component can be obtained using protoVisualComponent() function.
		 */
		void showVisualComponent();

	protected:
		AbstractQMLWidgetWrapper(QQmlEngine * qmlEngine);

		~AbstractQMLWidgetWrapper();

		QQmlEngine * engine() const;

	private:
		/**
		 * Renew proto-visual-component.
		 */
		void renewProtoVisualComponent();

		QQmlEngine * m_qmlEngine;
		QQmlComponent * m_protoVisualComponent;
		QQuickItem * m_visualComponent;
		QQmlContext * m_projectContext;
};

#endif
