#ifndef VERT_H
#define VERT_H

#include "../vectors.hpp"

//TODO(Rok Kos): Change this to class
namespace ARCSim {
	struct Node;
	struct Face;
}

namespace ARCSim {

	struct Vert {
		Vec3 u; // material space
		// NICK
		Vec3 v; // material velocity
		Node* node; // world space
					// topological data
		std::vector<Face*> adjf; // adjacent faces
		int index; // position in mesh.verts
				   // derived material-space data that only changes with remeshing
				   // remeshing data
		Mat3x3 sizing;
		// constructors
		Vert() : node(0), index(-1) {}
		explicit Vert(const Vec3& u, const Vec3& v) :
			u(u), v(v) {}

		//void serializer(Serialize& s);
	};

}

#endif