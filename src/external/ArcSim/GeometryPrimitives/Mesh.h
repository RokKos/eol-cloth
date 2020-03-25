#ifndef MESH_H
#define MESH_H

#include "Vert.h"
#include "Node.h"
#include "Edge.h"
#include "Face.h"
#include "../referenceshape.hpp"

namespace ARCSim {
	
	class Mesh {
	public:
		Mesh() : ref(0), EoL_Count(0) {};

		bool operator==(const Mesh& other) const {
			return check_that_pointers_are_sane(other);
		}

		inline const std::vector<Vert*>& GetVert() const { return verts; }
		inline const std::vector<Node*>& GetNodes() const { return nodes; }
		inline const std::vector<Edge*>& GetEdges() const { return edges; }
		inline const std::vector<Face*>& GetFaces() const { return faces; }

		void compute_ms_data(); // call after mesh topology changes
		void compute_ws_data(); // call after vert positions change

		void set_indices();
		void update_x0();

	private:
		bool check_that_pointers_are_sane(const Mesh& mesh) const;
		bool check_that_contents_are_sane(const Mesh& mesh) const;

		// These do *not* assume ownership, so no deletion on removal
		void add(Vert* vert);
		void add(Node* node);
		void add(Edge* edge);
		void add(Face* face);
		void remove(Vert* vert);
		void remove(Node* node);
		void remove(Edge* edge);
		void remove(Face* face);

	private:

		ReferenceShape* ref;

		int EoL_Count;

		std::vector<Vert*> verts;
		std::vector<Node*> nodes;
		std::vector<Edge*> edges;
		std::vector<Face*> faces;
	};
}

#endif