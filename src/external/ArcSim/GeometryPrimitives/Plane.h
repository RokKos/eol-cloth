#ifndef PLANE_H
#define PLANE_H

namespace ARCSim {

	struct Plane {
		Plane() {}
		Plane(const Vec3& x0, const Vec3& n) : x0(x0), n(n) {}
		Vec3 x0, n;
	};
}

#endif