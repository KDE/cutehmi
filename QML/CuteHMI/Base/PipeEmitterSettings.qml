import QtQuick 2.0

QtObject
{
	property real width: 0.0		///< Emitter width. Particles will be emitted anywhere from the bounding box of the emitter.
	property real height: 0.0		///< Emitter height. Particles will be emitted anywhere from the bounding box of the emitter.
	property real emitRate: 1.0		///< Emit rate [particles/s].
	property real size: 30		///< Size of particles.
}
