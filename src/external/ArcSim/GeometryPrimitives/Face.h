#ifndef FACE_H
#define FACE_H

#include "../../../TypeDefinitions.h"
#include "../vectors.hpp"
#include "Vert.h"

namespace ARCSim {
	struct Edge;
}

namespace ARCSim {

	struct Face {
		Vert* v[3]; // verts
		EOL::Material* material;
		int flag;
		// topological data
		Edge* adje[3]; // adjacent edges
		int index; // position in mesh.faces
				   // derived world-space data that changes every frame
		Vec3 n; // local normal, exact
				// derived material-space data that only changes with remeshing
		double a, m; // area, mass
		Mat3x3 Dm, invDm; // finite element matrix
						  // plasticity data
		Mat3x3 Sp_bend; // plastic bending strain
		Mat3x3 Sp_str; // plastic stretching
		Mat3x3 sigma;
		double damage; // accumulated norm of S_plastic/S_yield
					   // constructors
		Face() : material(0), flag(0), index(-1), a(0), m(0), damage(0) {
			for (int i = 0; i < 3; i++) { v[i] = 0; adje[i] = 0; }
		}
		explicit Face(Vert* vert0, Vert* vert1, Vert* vert2, const Mat3x3& ps,
			const Mat3x3& pb, EOL::Material* mat, double damage) :
			material(mat), flag(0), a(0), m(0), Sp_bend(pb), Sp_str(ps), sigma(0), damage(damage) {
			v[0] = vert0;
			v[1] = vert1;
			v[2] = vert2;
		}

		//void serializer(Serialize& s);
	};
}
#endif