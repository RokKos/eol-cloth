#ifndef EDGE_H
#define EDGE_H

#include "Node.h"

namespace ARCSim {
	struct Face;
}

namespace ARCSim {

	struct Edge {
		Node* n[2]; // nodes
		bool preserve;
		// topological data
		Face* adjf[2]; // adjacent faces
		int index; // position in mesh.edges
				   // plasticity data
		double theta_ideal, damage; // rest dihedral angle, damage parameter
									// constructors
		Edge() : index(-1), theta_ideal(0), damage(0) { n[0] = n[1] = 0; adjf[0] = adjf[1] = 0; }
		explicit Edge(Node* node0, Node* node1, double theta_ideal, bool preserve) :
			preserve(preserve), theta_ideal(theta_ideal), damage(0) {
			n[0] = node0;
			n[1] = node1;
		}

		//void serializer(Serialize& s);
	};

}

#endif