.pragma library

function taxicabDistance(a, b) {
	return Math.abs(b.x - a.x) + Math.abs(b.y - a.y)
}

function euclideanDistance(a, b) {
	return Math.hypot(b.x - a.x, b.y - a.y)
}
