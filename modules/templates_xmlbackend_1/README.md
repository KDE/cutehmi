# XML Backend Template

Minimal XML plugin, that can be used as a template for writing plugins.

CuteHMI uses XML project files to specify, which plugins to load. A plugin will
typically want to read some configuration itself. The project file can be used
to store the configuration of a plugin.

This template builds on [templates_projectplugin_1](../templates_projectplugin_1/).
Only added XML capabilities will be briefly described.

## Files

There aren't any new files, only modifications to existing one.

### [templates_xmlbackend_1.qbs]

```qbs
Depends { name: "cutehmi_xml_1" }
cutehmi_xml_1.reqMinor: 0
```
Dependency on [cutehmi_xml_1](../cutehmi_xml_1/) module has been added.


### [src/templates/projectplugin/plugin/ProjectPlugin.hpp]

```cpp
    public cutehmi::xml::IBackendPlugin
```
ProjectPlugin has been modified to implement cutehmi::xml::IBackendPlugin
interface.

```cpp
        void readXML(QXmlStreamReader & xmlReader, cutehmi::ProjectNode & node) override;

        void writeXML(QXmlStreamWriter & xmlWriter, cutehmi::ProjectNode & node) const noexcept(false) override;
```
There are two additional functions, which belong to cutehmi::xml::IBackendPlugin
interface.


### [src/templates/projectplugin/plugin/ProjectPlugin.cpp]

```cpp
void ProjectPlugin::init(cutehmi::ProjectNode & node)
{
        std::unique_ptr<PluginNodeData> pluginNodeData(new PluginNodeData(this));
        node.registerExtension(pluginNodeData->xmlBackendPlugin());
        node.data().append(std::move(pluginNodeData));
}
```
ProjectPlugin implements cutehmi::xml::IBackendPlugin interface, so `this`
pointer is passed to an instance of PluginNodeData. PluginNodeData will create
wrapping object belonging to cutehmi::xml::BackendPlugin class. This object can
be retrieved via PluginNodeData::xmlBackendPlugin() function. The object is
registered as an extension and classes belonging to
[cutehmi_xml_1](../cutehmi_xml_1/) module will recognize this extension and a
portion of XML document will be given to the plugin to parse.

PluginNodeData object is stored inside the node, which takes ownership of the
object.


```cpp
        CUTEHMI_LOG_DEBUG("Plugin " TEMPLATES_XMLBACKEND_NAME " starts parsing its own portion of document...");	// Edit! Replace 'TEMPLATES_XMLBACKEND_NAME' with 'VENDOR_MODULE_NAME'.

        QStringList supportedVersions;
        supportedVersions << "http://michpolicht.github.io/CuteHMI/templates_xmlbackend_1/xsd/1.0/";   // Edit! Replace 'templates_xmlbackend_1' with 'vendor_module'.
```
Plugins could use XML schema file as a mean of version control for an XML
document, a namespace specifier and a validation tool. Because XML document
format is not stable, this has never been implemented yet. For now it is enough
to specify an URL, where XML schema file should be. This URL
specifies version of supported XML format and a namespace.

```cpp
        cutehmi::xml::ParseHelper helper(& xmlReader, supportedVersions);
        helper << cutehmi::xml::ParseElement("templates_xmlbackend_1", 1, 1);    // Edit! Replace 'templates_xmlbackend_1' with 'vendor_module'.
```
A class called cutehmi::xml::ParseHelper can be used to make it easier to parse
XML.


```cpp
void ProjectPlugin::writeXML(QXmlStreamWriter & xmlWriter, cutehmi::ProjectNode & node) const noexcept(false)
{
        Q_UNUSED(xmlWriter);
        Q_UNUSED(node);
        throw cutehmi::Exception("cutehmi::xml::IBackendPlugin::writeXML() not implemented yet.");
}
```
At this point XML project files have to be edited by hand, so we only throw an
exception.



### [src/templates/projectplugin/plugin/ProjectNodeData.hpp]

```cpp
public:
        PluginNodeData(cutehmi::xml::IBackendPlugin * implementation);

        cutehmi::xml::BackendPlugin * xmlBackendPlugin() const;

private:
        std::unique_ptr<cutehmi::xml::BackendPlugin> m_xmlBackendPlugin;
```
Plugin node data stores extension object.

### [src/templates/projectplugin/plugin/ProjectNodeData.cpp]

```cpp
PluginNodeData::PluginNodeData(cutehmi::xml::IBackendPlugin * implementation):
        m_xmlBackendPlugin(new cutehmi::xml::BackendPlugin(implementation))
{
}

cutehmi::xml::BackendPlugin * PluginNodeData::xmlBackendPlugin() const
{
        return m_xmlBackendPlugin.get();
}
```
Notice that a wrapping object cutehmi::xml::BackendPlugin is created in the
constructor to keep `implementation`.
