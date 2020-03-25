/*
Copyright ©2013 The Regents of the University of California
(Regents). All Rights Reserved. Permission to use, copy, modify, and
distribute this software and its documentation for educational,
research, and not-for-profit purposes, without fee and without a
signed licensing agreement, is hereby granted, provided that the
above copyright notice, this paragraph and the following two
paragraphs appear in all copies, modifications, and
distributions. Contact The Office of Technology Licensing, UC
Berkeley, 2150 Shattuck Avenue, Suite 510, Berkeley, CA 94720-1620,
(510) 643-7201, for commercial licensing opportunities.

IN NO EVENT SHALL REGENTS BE LIABLE TO ANY PARTY FOR DIRECT,
INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING
LOST PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS
DOCUMENTATION, EVEN IF REGENTS HAS BEEN ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.

REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
FOR A PARTICULAR PURPOSE. THE SOFTWARE AND ACCOMPANYING
DOCUMENTATION, IF ANY, PROVIDED HEREUNDER IS PROVIDED "AS
IS". REGENTS HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT,
UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
*/

#ifndef MESH_HPP
#define MESH_HPP

#include "transformation.hpp"

// material space (not fused at seams)
#include "GeometryPrimitives/Vert.h"
#include "GeometryPrimitives/Face.h"

// world space (fused)
#include "GeometryPrimitives/Node.h"
#include "GeometryPrimitives/Edge.h"
#include "GeometryPrimitives/Mesh.h"
#include "GeometryPrimitives/Plane.h"

namespace ARCSim {

struct Serialize;

extern int uuid_src;

template <typename Prim> inline const std::vector<Prim*> &get(const Mesh &mesh);
template <typename Prim> inline int count_elements(const std::vector<Mesh*>& meshes);

void connect(Vert *vert, Node *node); // assign vertex to node



void compute_ms_data(std::vector<Face*>& face);
void compute_ms_data(std::vector<Node*>& node);
void compute_ws_data(std::vector<Face*>& face);
void compute_ws_data(std::vector<Node*>& node);
void compute_ms_data(Face* face);
void compute_ms_data(Node* node);

// NICK
//double calc_edge_weight(Node* n);

inline Edge* get_opp_edge(const Face* face, const Node* opp);
inline Vert* get_vert(const Face* face, const Node* node);
inline Vert* get_other_vert(const Face* face, const Vert* vert0, const Vert* vert1);
inline Edge *get_edge(const Node *node0, const Node *node1);
inline Vert *edge_vert(const Edge *edge, int side, int i);
inline Vert *edge_opp_vert(const Edge *edge, int side);
inline Node *other_node(const Edge* edge, const Node* node0);
inline Face *adj_face(const Face* face0, int num);

inline Edge *next_edge_ccw(const Edge* edge, Node* center);
inline Edge *next_edge_cw(const Edge* edge, Node* center);
inline Face *next_face_ccw(const Edge* edge, Node* center);
inline Face *next_face_cw(const Edge* edge, Node* center);


void set_indices(std::vector<Mesh*> &meshes);
void mark_nodes_to_preserve(Mesh &mesh);

inline Vec3 derivative(double a0, double a1, double a2, double az, const Face *face);
inline Mat3x3 derivative(const Vec3& w0, const Vec3& w1,
	const Vec3& w2, const Vec3& dz, const Face *face);

void apply_transformation_onto(const Mesh& start_state, Mesh& onto,
	const Transformation& tr);
void apply_transformation(Mesh& mesh, const Transformation& tr);

void update_x0(Mesh &mesh);

Mesh deep_copy(Mesh &mesh);
void delete_mesh(Mesh &mesh);

// ADDED BY NICK
void reindex_nodes(std::vector<Node*>& nodes);

void activate_nodes(std::vector<Node*>& nodes);
void deactivate_nodes(std::vector<Node*>& nodes);

//
// IMPLEMENTATION OF INLINE FUNCTIONS
//

inline Vec3 derivative(double a0, double a1, double a2, double az, const Face *face) {
	return face->invDm.t() * Vec3(a1 - a0, a2 - a0, az);
}

inline Mat3x3 derivative(const Vec3& w0, const Vec3& w1,
	const Vec3& w2, const Vec3& dz, const Face *face) {
	return Mat3x3(w1 - w0, w2 - w0, dz) * face->invDm;
}

inline Vert* get_vert(const Face* face, const Node* node) {
	if (face->v[0]->node == node) return face->v[0];
	return face->v[1]->node == node ? face->v[1] : face->v[2];
}

inline Vert* get_other_vert(const Face* face, const Vert* vert0, const Vert* vert1) {
	if (face->v[0] != vert0 && face->v[0] != vert1) return face->v[0];
	if (face->v[1] != vert0 && face->v[1] != vert1) return face->v[1];
	return face->v[2];
}

inline Node *other_node(const Edge* edge, const Node* node0) {
	return edge->n[0] == node0 ? edge->n[1] : edge->n[0];
}

inline Face *adj_face(const Face* face0, int num) {
	Edge* e = face0->adje[num];
	return e->adjf[0] == face0 ? e->adjf[1] : e->adjf[0];
}

inline Edge *next_edge_ccw(const Edge* edge, Node* center) {
	Face *f = next_face_ccw(edge, center);
	Node *os = other_node(edge, center);
	for (int i = 0; i<3; i++) {
		Edge *e = f->adje[i];
		if ((e->n[0] == center || e->n[1] == center) && e->n[0] != os && e->n[1] != os)
			return e;
	}
	return NULL;
}

inline Edge *next_edge_cw(const Edge* edge, Node* center) {
	Face *f = next_face_cw(edge, center);
	Node *os = other_node(edge, center);
	for (int i = 0; i<3; i++) {
		Edge *e = f->adje[i];
		if ((e->n[0] == center || e->n[1] == center) && e->n[0] != os && e->n[1] != os)
			return e;
	}
	return NULL;
}

inline Face *next_face_ccw(const Edge* edge, Node* center) {
	return (edge->n[0] == center) ? edge->adjf[0] : edge->adjf[1];
}

inline Face *next_face_cw(const Edge* edge, Node* center) {
	return (edge->n[1] == center) ? edge->adjf[0] : edge->adjf[1];
}

// NICK
inline Edge* get_opp_edge(const Face* face, const Node* opp) {
	for (int e = 0; e < 3; e++) {
		Edge *edge = face->adje[e];
		if (edge->n[0] == opp || edge->n[1] == opp) continue;
		return edge;
	}
	return NULL;
}

inline Edge *get_edge(const Node *n0, const Node *n1) {
	for (int e = 0; e < (int)n0->adje.size(); e++) {
		Edge *edge = n0->adje[e];
		if (edge->n[0] == n1 || edge->n[1] == n1)
			return edge;
	}
	return NULL;
}

inline Vert *edge_vert(const Edge *edge, int side, int i) {
	Face *face = (Face*)edge->adjf[side];
	if (!face)
		return NULL;
	for (int j = 0; j < 3; j++)
		if (face->v[j]->node == edge->n[i])
			return face->v[j];
	return NULL;
}

inline Vert *edge_opp_vert(const Edge *edge, int side) {
	Face *face = (Face*)edge->adjf[side];
	if (!face)
		return NULL;
	for (int j = 0; j < 3; j++)
		if (face->v[j]->node == edge->n[side])
			return face->v[j>0 ? j - 1 : j + 2];
	return NULL;
}

template <typename Prim> inline int count_elements(const std::vector<Mesh*>& meshes) {
	int num = 0;
	for (size_t i = 0; i< meshes.size(); i++)
		num += get<Prim>(*meshes[i]).size();
	return num;
}

}  // namespace ARCSim

#endif
