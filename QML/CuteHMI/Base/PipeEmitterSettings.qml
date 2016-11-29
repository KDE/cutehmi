import QtQuick 2.0

QtObject
{
	property real width: 0.0		///< Emitter width. Particles will be emitted anywhere from the bounding box of the emitter.
	property real height: 0.0		///< Emitter height. Particles will be emitted anywhere from the bounding box of the emitter.
	property real emitRate: 1.0		///< Emit rate [particles/s].
	property real size: 30		///< Size of particles.
	property bool enabled: true	///< Indicates whether emitter is enabled.
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
