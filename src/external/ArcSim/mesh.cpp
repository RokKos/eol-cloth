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

#include "../../Cloth.h"
#include "mesh.hpp"

using namespace std;

namespace ARCSim {

int uuid_src = 0;


// World-space data

void compute_ws_data(Face* face) {
	const Vec3 &x0 = face->v[0]->node->x,
		&x1 = face->v[1]->node->x,
		&x2 = face->v[2]->node->x;
	face->n = normalize(cross(x1 - x0, x2 - x0));
	// Mat3x2 F = derivative(x0, x1, x2, face);
	// SVD<3,2> svd = singular_value_decomposition(F);
	// Mat3x2 Vt_ = 0;
	// for (int i = 0; i < 2; i++)
	//     for (int j = 0; j < 2; j++)
	//         Vt_(i,j) = svd.Vt(i,j);
	// face->R = svd.U*Vt_;
	// face->F = svd.Vt.t()*diag(svd.s)*svd.Vt;
}

void compute_ws_data(Node* node) {
	node->n = normal<WS>(node);
	Mat3x3 C(0), C0(0);
	double sum = 0;
	for (size_t v = 0; v < node->verts.size(); v++) {
		const vector<Face*> &adjfs = node->verts[v]->adjf;
		for (size_t i = 0; i < adjfs.size(); i++) {
			Face const* face = adjfs[i];
			C += face->a / 3 * curvature<WS>(face);
			C0 += face->a / 3 * curvature<MS>(face);
			sum += face->a;
		}
	}
	Eig<3> eig = eigen_decomposition((C - C0) / sum);
	for (int i = 0; i<3; i++)
		eig.l[i] = fabs(eig.l[i]);
	node->curvature = eig.Q * diag(eig.l) * eig.Q.t();
}

void compute_ws_data(vector<Face*>& faces) {
	for (size_t n = 0; n < faces.size(); n++)
		compute_ws_data(faces[n]);
}

void compute_ws_data(vector<Node*>& nodes) {
	for (size_t n = 0; n < nodes.size(); n++)
		compute_ws_data(nodes[n]);
}

// Material space data

void compute_ms_data(Face* face) {
	Vec3 d0 = face->v[1]->u - face->v[0]->u;
	Vec3 d1 = face->v[2]->u - face->v[0]->u;
	Vec3 d2 = cross(d0, d1);
	double dn = norm(d2);

	Mat3x3 Dm3(d0, d1, d2 / dn);
	face->a = 0.5*dn;
	face->m = face->material ? face->a * face->material->density : 0;

	if (face->a == 0) {
		face->invDm = Mat3x3(0);
	}
	else {
		face->invDm = Dm3.inv();
		// clamp
		//auto parent = face->v[0]->node->mesh->parent;
		//if (parent) {
		//	const double CLAMP = 1000.0 / parent->remeshing.size_min;
		//	SVD<3, 3> svd = singular_value_decomposition(face->invDm);
		//	for (int i = 0; i<3; i++) {
		//		if (svd.s[i] > CLAMP) {
		//			cout << "clamping " << svd.s[i] << " to " << CLAMP << endl;
		//			svd.s[i] = CLAMP;
		//		}
		//	}
		//	face->invDm = svd.U * diag(svd.s) * svd.Vt;
		//}
	}
}

void compute_ms_data(Node* node) {
	node->a = 0;
	node->m = 0;
	for (size_t v = 0; v < node->verts.size(); v++) {
		const vector<Face*> &adjfs = node->verts[v]->adjf;
		for (size_t i = 0; i < adjfs.size(); i++) {
			Face const* face = adjfs[i];
			node->a += face->a / 3;
			node->m += face->m / 3;
		}
	}
}

void compute_ms_data(vector<Face*>& faces) {
	for (size_t n = 0; n < faces.size(); n++)
		compute_ms_data(faces[n]);
	compute_ws_data(faces);
}

void compute_ms_data(vector<Node*>& nodes) {
	for (size_t n = 0; n < nodes.size(); n++)
		compute_ms_data(nodes[n]);
	compute_ws_data(nodes);
}


//// NICK
//double calc_edge_weight(Node* n)
//{
//	Node* node0;
//	Node* node1;
//	bool first = true;
//	bool succeed = false;
//	for (int i = 0; i < n->adje.size(); i++) {
//		if (n->adje[i]->preserve && first) {
//			if (n->adje[i]->n[0] != n) {
//				node0 = n->adje[i]->n[0];
//			}
//			else {
//				node0 = n->adje[i]->n[1];
//			}
//			first = false;
//		}
//		else if (n->adje[i]->preserve && !first) {
//			if (n->adje[i]->n[0] != n) {
//				node1 = n->adje[i]->n[0];
//			}
//			else {
//				node1 = n->adje[i]->n[1];
//			}
//			succeed = true;
//			break;
//		}
//	}
//	if (!succeed) return -1.0;
//	if (node0->on_corner) n->which_edge = node1->which_edge;
//	else n->which_edge = node0->which_edge; // MOVE?
//	double d1 = sqrt(pow(node1->x[0] - node0->x[0], 2) + pow(node1->x[1] - node0->x[1], 2) + pow(node1->x[2] - node0->x[2], 2));
//	double d2 = sqrt(pow(node1->x[0] - n->x[0], 2) + pow(node1->x[1] - n->x[1], 2) + pow(node1->x[2] - n->x[2], 2));
//	double ratio = d2 / d1;
//	double edge_weight0 = node0->verts[0]->egde_weight[0];
//	double edge_weight1 = node1->verts[0]->egde_weight[0];
//	if (node0->on_corner) {
//		if (edge_weight1 >= 0.5) edge_weight0 = 1.0;
//		else edge_weight0 = 0.0;
//	}
//	else if (node1->on_corner) {
//		if (edge_weight0 >= 0.5) edge_weight1 = 1.0;
//		else edge_weight1 = 0.0;
//	}
//	return abs((ratio * (edge_weight1 - edge_weight0)) - edge_weight1);
//}

// Mesh operations

void connect(Vert *vert, Node *node) {
	vert->node = node;
	include(vert, node->verts);
}



void add_edges_if_needed(Mesh &mesh, const Face *face) {
	for (int i = 0; i < 3; i++) {
		Node *n0 = face->v[i]->node, *n1 = face->v[NEXT(i)]->node;
		if (get_edge(n0, n1) == NULL) {
			mesh.add(new Edge(n0, n1, 0, 0));
		}
	}
}

void Mesh::add(Face *face) {
	faces.push_back(face);
    face->index = static_cast<int>(faces.size()) - 1;
	// adjacency
	add_edges_if_needed(*this, face);
	for (int i = 0; i < 3; i++) {
		Vert *v0 = face->v[NEXT(i)], *v1 = face->v[PREV(i)];
		include(face, v0->adjf);
		Edge *e = get_edge(v0->node, v1->node);
		face->adje[i] = e;
		int side = e->n[0] == v0->node ? 0 : 1;
		e->adjf[side] = face;
	}
}

void Mesh::remove(Face* face) {
	exclude(face, faces);
	// adjacency
	for (int i = 0; i < 3; i++) {
		Vert *v0 = face->v[NEXT(i)];
		exclude(face, v0->adjf);
		Edge *e = face->adje[i];
		int side = e->n[0] == v0->node ? 0 : 1;
		e->adjf[side] = NULL;
	}
}

void set_indices(vector<Mesh*>& meshes) {
	int idx_v = 0, idx_f = 0, idx_n = 0, idx_e = 0;
	for (size_t m = 0; m < meshes.size(); m++) {
		Mesh& mesh = *meshes[m];
		for (size_t v = 0; v < mesh.verts.size(); v++)
			mesh.verts[v]->index = idx_v++;
		for (size_t f = 0; f < mesh.faces.size(); f++)
			mesh.faces[f]->index = idx_f++;
		for (size_t n = 0; n < mesh.nodes.size(); n++)
			mesh.nodes[n]->index = idx_n++;
		for (size_t e = 0; e < mesh.edges.size(); e++)
			mesh.edges[e]->index = idx_e++;
	}
}

void mark_nodes_to_preserve(Mesh &mesh) {
	for (int n = 0; n < (int)mesh.nodes.size(); n++) {
		Node *node = mesh.nodes[n];
		if (is_seam_or_boundary(node) || node->label)
			node->preserve = true;
	}
	/*for (int e = 0; e < mesh.edges.size(); e++) {
	Edge *edge = mesh.edges[e];
	if (edge->label) {
	edge->n[0]->preserve = true;
	edge->n[1]->preserve = true;
	}
	}*/
}

// ADDED BY NICK
// Need to check if nodes ever have more than one vert assigned
void reindex_nodes(vector<Node*>& nodes) {
	for (size_t i = 0; i<nodes.size(); i++) {
		nodes[i]->index = static_cast<int>(i);
		nodes[i]->verts[0]->index = static_cast<int>(i);
	}
}

void activate_nodes(vector<Node*>& nodes) {
	for (size_t i = 0; i<nodes.size(); i++) {
		nodes[i]->index = static_cast<int>(i);
		nodes[i]->flag |= Node::FlagActive;
	}
}

void deactivate_nodes(vector<Node*>& nodes) {
	for (size_t i = 0; i<nodes.size(); i++)
		nodes[i]->flag &= ~Node::FlagActive;

}

void apply_transformation_onto(const Mesh &start_state, Mesh &onto,
	const Transformation &tr) {
	for (int n = 0; n < (int)onto.nodes.size(); n++)
		onto.nodes[n]->x = tr.apply(start_state.nodes[n]->x);
	compute_ws_data(onto);
}

void apply_transformation(Mesh& mesh, const Transformation& tr) {
	apply_transformation_onto(mesh, mesh, tr);
}

Mesh deep_copy(Mesh &mesh0) {
	Mesh mesh1;
	set_indices(mesh0);
	for (int v = 0; v < (int)mesh0.verts.size(); v++) {
		const Vert *vert0 = mesh0.verts[v];
		Vert *vert1 = new Vert(vert0->u, vert0->v);
		mesh1.add(vert1);
	}
	for (int n = 0; n < (int)mesh0.nodes.size(); n++) {
		const Node *node0 = mesh0.nodes[n];
		Node *node1 = new Node(node0->y, node0->x, node0->v, node0->label, node0->flag, node0->preserve);
		node1->EoL = node0->EoL; // NICK
		node1->verts.resize(node0->verts.size());
		for (int v = 0; v < (int)node0->verts.size(); v++)
			node1->verts[v] = mesh1.verts[node0->verts[v]->index];
		mesh1.add(node1);
	}
	for (int e = 0; e < (int)mesh0.edges.size(); e++) {
		const Edge *edge0 = mesh0.edges[e];
		Edge *edge1 = new Edge(mesh1.nodes[edge0->n[0]->index],
			mesh1.nodes[edge0->n[1]->index],
			edge0->theta_ideal, edge0->preserve);
		mesh1.add(edge1);
	}
	for (int f = 0; f < (int)mesh0.faces.size(); f++) {
		const Face *face0 = mesh0.faces[f];
		Face *face1 = new Face(mesh1.verts[face0->v[0]->index],
			mesh1.verts[face0->v[1]->index],
			mesh1.verts[face0->v[2]->index],
			face0->Sp_str, face0->Sp_bend, face0->material, face0->damage);
		mesh1.add(face1);
	}
	compute_ms_data(mesh1);
	//if (mesh0.proxy)
	//	mesh1.proxy = mesh0.proxy->clone(mesh1);
	return mesh1;
}

void delete_mesh(Mesh &mesh) {
	for (int v = 0; v < (int)mesh.verts.size(); v++)
		delete mesh.verts[v];
	for (int n = 0; n < (int)mesh.nodes.size(); n++)
		delete mesh.nodes[n];
	for (int e = 0; e < (int)mesh.edges.size(); e++)
		delete mesh.edges[e];
	for (int f = 0; f < (int)mesh.faces.size(); f++)
		delete mesh.faces[f];
	mesh.verts.clear();
	mesh.nodes.clear();
	mesh.edges.clear();
	mesh.faces.clear();
	//if (mesh.proxy)
	//	delete mesh.proxy;
	//mesh.proxy = 0;
}

}  // namespace ARCSim