#include "Mesh.h"

namespace ARCSim {

	bool Mesh::check_that_pointers_are_sane(const Mesh& mesh) const{
		for (int v = 0; v < (int)mesh.verts.size(); v++) {
			const Vert* vert = mesh.verts[v];
			not_null(vert, vert->node);
			check(vert, vert->node, mesh.nodes);
			if (find((Vert*)vert, vert->node->verts) == -1) {
				cout << "vert " << vert << "'s node " << vert->node
					<< " doesn't contain it" << endl;
				abort();
			}
			for (int i = 0; i < (int)vert->adjf.size(); i++)
				check(vert, vert->adjf[i], mesh.faces);
		}
		for (int n = 0; n < (int)mesh.nodes.size(); n++) {
			const Node* node = mesh.nodes[n];
			for (int i = 0; i < (int)node->verts.size(); i++)
				check(node, node->verts[i], mesh.verts);
			for (int i = 0; i < 2; i++)
				check(node, node->adje[i], mesh.edges);
		}
		for (int e = 0; e < (int)mesh.edges.size(); e++) {
			const Edge* edge = mesh.edges[e];
			for (int i = 0; i < 2; i++)
				check(edge, edge->n[i], mesh.nodes);
			not_any_null(edge, edge->n, 2);
			for (int i = 0; i < 2; i++)
				check(edge, edge->adjf[i], mesh.faces);
			not_all_null(edge, edge->adjf, 2);
		}
		for (int f = 0; f < (int)mesh.faces.size(); f++) {
			const Face* face = mesh.faces[f];
			for (int i = 0; i < 3; i++)
				check(face, face->v[i], mesh.verts);
			not_any_null(face, face->v, 3);
			for (int i = 0; i < 3; i++)
				check(face, face->adje[i], mesh.edges);
			not_any_null(face, face->adje, 3);
		}
		return true;
	}

	bool Mesh::check_that_contents_are_sane(const Mesh& mesh) const {
		// // TODO
		// for (int v = 0; v < mesh.verts.size(); v++) {
		//     const Vert *vert = mesh.verts[v];
		//     if (!isfinite(norm2(vert->x + vert->v + vert->n) + vert->a)) {
		//         cout << "Vertex " << name(vert) << " is " << vert->x << " "
		//              << vert->v << " " << vert->n << " " << vert->a << endl;
		//         return false;
		//     }
		// }
		// for (int f = 0; f < mesh.faces.size(); f++) {
		//     const Face *face = mesh.faces[f];
		//     if (!isfinite(norm2(face->n) + face->a)) {
		//         cout << "Face " << name(face) << " is " << face->n << " "
		//              << face->a << endl;
		//         return false;
		//     }
		// }
		return true;
	}

	void Mesh::add(Vert* vert) {
		verts.push_back(vert);
		vert->node = NULL;
		vert->adjf.clear();
		vert->index = static_cast<int>(verts.size()) - 1;
	}

	void Mesh::remove(Vert* vert) {
		if (!vert->adjf.empty()) {
			cout << "Error: can't delete vert " << vert << " as it still has "
				<< vert->adjf.size() << " faces attached to it." << endl;
			return;
		}
		exclude(vert, verts);
	}

	void Mesh::add(Node* node) {
		nodes.push_back(node);
		node->index = static_cast<int>(nodes.size()) - 1;
		node->adje.clear();
		for (size_t v = 0; v < node->verts.size(); v++) {
			node->verts[v]->node = node;
		}
		node->mesh = this;
	}

	void Mesh::remove(Node* node) {
		if (!node->adje.empty()) {
			cout << "Error: can't delete node " << node << " as it still has "
				<< node->adje.size() << " edges attached to it." << endl;
			return;
		}
		exclude(node, nodes);
	}

	void Mesh::add(Edge* edge) {
		edges.push_back(edge);
		edge->adjf[0] = edge->adjf[1] = NULL;
		edge->index = static_cast<int>(edges.size()) - 1;
		include(edge, edge->n[0]->adje);
		include(edge, edge->n[1]->adje);
	}

	void Mesh::remove(Edge* edge) {
		if (edge->adjf[0] || edge->adjf[1]) {
			cout << "Error: can't delete edge " << edge
				<< " as it still has a face (" << edge->adjf[0] << "|" << edge->adjf[1]
				<< ") attached to it." << endl;
			return;
		}
		exclude(edge, edges);
		exclude(edge, edge->n[0]->adje);
		exclude(edge, edge->n[1]->adje);
	}

	void Mesh::add(Face* face) {
		faces.push_back(face);
		face->index = static_cast<int>(faces.size()) - 1;
		// adjacency
		add_edges_if_needed(*this, face);
		for (int i = 0; i < 3; i++) {
			Vert* v0 = face->v[NEXT(i)], * v1 = face->v[PREV(i)];
			include(face, v0->adjf);
			Edge* e = get_edge(v0->node, v1->node);
			face->adje[i] = e;
			int side = e->n[0] == v0->node ? 0 : 1;
			e->adjf[side] = face;
		}
	}

	void Mesh::remove(Face* face) {
		exclude(face, faces);
		// adjacency
		for (int i = 0; i < 3; i++) {
			Vert* v0 = face->v[NEXT(i)];
			exclude(face, v0->adjf);
			Edge* e = face->adje[i];
			int side = e->n[0] == v0->node ? 0 : 1;
			e->adjf[side] = NULL;
		}
	}

	void Mesh::compute_ms_data() {
		compute_ms_data_faces();
		compute_ms_data_nodes();
	}

	void Mesh::compute_ws_data() {
		compute_ws_data_faces();
		compute_ws_data_nodes(nodes);
	}


	void Mesh::set_indices() {
		for (size_t v = 0; v < verts.size(); v++) {
			verts[v]->index = static_cast<int>(v);
		}
			
		for (size_t f = 0; f < faces.size(); f++) {
			faces[f]->index = static_cast<int>(f);
		}

		int eoli = 0; // Added by Nick to index EoL nodes
		for (size_t n = 0; n < nodes.size(); n++) {
			nodes[n]->index = static_cast<int>(n);
			// Reset EoL indices as well
			if (nodes[n]->EoL) {
				nodes[n]->EoL_index = eoli;
				eoli++;
			}
			else {
				nodes[n]->EoL_index = -1;
			}
		}
		
		EoL_Count = eoli; // Update the number of EoL nodes in a mesh
		for (size_t e = 0; e < edges.size(); e++) {
			edges[e]->index = static_cast<int>(e);
		}
	}

	void Mesh::update_x0() {
		for (int n = 0; n < (int)nodes.size(); n++) {
			nodes[n]->x0 = nodes[n]->x;
		}
	}

	void Mesh::compute_ms_data_faces() {
		for (size_t n = 0; n < faces.size(); n++)
			faces[n]->compute_ms_data();
		compute_ws_data_faces();
	}

	void Mesh::compute_ms_data_nodes() {
		for (size_t n = 0; n < nodes.size(); n++)
			nodes[n]->compute_ms_data();
		compute_ws_data_nodes();
	}

	void Mesh::compute_ws_data_faces() {
		for (size_t n = 0; n < faces.size(); n++)
			faces[n]->compute_ws_data();
	}

	void Mesh::compute_ws_data_nodes() {
		for (size_t n = 0; n < nodes.size(); n++)
			nodes[n]->compute_ws_data();
	}

	// ADDED BY NICK
	// Need to check if nodes ever have more than one vert assigned
	void Mesh::reindex_nodes() {
		for (size_t i = 0; i < nodes.size(); i++) {
			nodes[i]->index = static_cast<int>(i);
			nodes[i]->verts[0]->index = static_cast<int>(i);
		}
	}

	void Mesh::activate_nodes() {
		for (size_t i = 0; i < nodes.size(); i++) {
			nodes[i]->index = static_cast<int>(i);
			nodes[i]->flag |= Node::FlagActive;
		}
	}

	void Mesh::deactivate_nodes() {
		for (size_t i = 0; i < nodes.size(); i++)
			nodes[i]->flag &= ~Node::FlagActive;

	}

	void Mesh::mark_nodes_to_preserve()	{
		for (int n = 0; n < (int)mesh.nodes.size(); n++) {
			Node* node = mesh.nodes[n];
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


	void Mesh::add_edges_if_needed(const Face* face) {
		for (int i = 0; i < 3; i++) {
			Node* n0 = face->v[i]->node, * n1 = face->v[NEXT(i)]->node;
			if (get_edge(n0, n1) == NULL) {
				add(new Edge(n0, n1, 0, 0));
			}
		}
	}

	void apply_transformation(const Transformation& tr) {
		for (int n = 0; n < (int)nodes.size(); n++)
			nodes[n]->x = tr.apply(nodes[n]->x);
		compute_ws_data();
	}
}