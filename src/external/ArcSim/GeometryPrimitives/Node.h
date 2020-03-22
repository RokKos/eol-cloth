#ifndef NODE_H
#define NODE_H

#include "Vert.h"
#include "../vectors.hpp"

namespace ARCSim {
	struct Mesh;
	struct Edge;
}

namespace ARCSim {

	struct Node {
		enum NodeFlags {
			FlagNone = 0, FlagActive = 1, FlagMayBreak = 2,
			FlagResolveUni = 4, FlagResolveMax = 8
		};
		enum NodeEOLState {
			IsLAG = 0,
			NewEOL = 1, NewEOLFromSplit = 2, IsEOL = 3, WasEOL = 4
		};

		//int uuid;

		Mesh* mesh;

		bool EoL;
		int EoL_index;
		int EoL_state;
		int cornerID;
		std::vector<int> cdEdges;

		int label;
		int flag;
		std::vector<Vert*> verts;
		Vec3 y; // plastic embedding
		Vec3 x, x0, v; // position, old (collision-free) position, velocity
		bool preserve; // don't remove this node
					   // topological data
		int index; // position in mesh.nodes
		std::vector<Edge*> adje; // adjacent edges
								 // derived world-space data that changes every frame
		Vec3 n; // local normal, approximate
				// derived material-space data that only changes with remeshing
		double a, m; // area, mass
		Mat3x3 curvature; // filtered curvature for bending fracture
						  // pop filter data
		Vec3 acceleration;
		Node() :  label(0), flag(0), preserve(false), index(-1), a(0), m(0) {}  //uuid(uuid_src++),
		explicit Node(const Vec3& y, const Vec3& x, const Vec3& v, int label, int flag,
			bool preserve) :
			EoL(false), EoL_index(-1), EoL_state(0), cornerID(-1), // EoL specifics
			mesh(0), label(label), flag(flag), y(y), x(x), x0(x), v(v), preserve(preserve),  //uuid(uuid_src++),
			curvature(0) {}

		inline bool active() const { return flag & FlagActive; }

		//void serializer(Serialize& s);
	};
}

#endif