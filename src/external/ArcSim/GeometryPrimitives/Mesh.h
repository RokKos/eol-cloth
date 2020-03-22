#ifndef MESH_H
#define MESH_H

#include "Vert.h"
#include "Node.h"
#include "Edge.h"
#include "Face.h"
#include "../referenceshape.hpp"

namespace ARCSim {

	struct Mesh {
		ReferenceShape* ref;

		int EoL_Count;

		std::vector<Vert*> verts;
		std::vector<Node*> nodes;
		std::vector<Edge*> edges;
		std::vector<Face*> faces;
		// These do *not* assume ownership, so no deletion on removal
		void add(Vert* vert);
		void add(Node* node);
		void add(Edge* edge);
		void add(Face* face);
		void remove(Vert* vert);
		void remove(Node* node);
		void remove(Edge* edge);
		void remove(Face* face);

		Mesh() : ref(0), EoL_Count(0) {};

		bool operator==(const Mesh& other) const {
			return ref == other.ref &&
				EoL_Count == other.EoL_Count &&
				verts == other.verts &&
				nodes == other.nodes &&
				edges == other.edges &&
				faces == other.faces;
		}
	};
}

#endif