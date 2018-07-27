#include "PluginNodeData.hpp"

namespace cutehmi {
namespace termobot {
namespace plugin {

PluginNodeData::PluginNodeData(xml::IBackendPlugin *implementation)
    : m_xmlBackendPlugin(new xml::BackendPlugin(implementation)) {}

xml::BackendPlugin *PluginNodeData::xmlBackendPlugin() const {
  return m_xmlBackendPlugin.get();
}

} // namespace plugin
} // namespace termobot
} // namespace cutehmi

//(c)WZ: Copyright © 2018, Wojciech Zygmuntowicz. All rights reserved.
//(c)WZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
