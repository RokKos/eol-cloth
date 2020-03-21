#include "remeshExtension.h"


#include "external\ArcSim\blockvectors.hpp"


ARCSim::RemeshOp split_edgeForced(ARCSim::Edge *edge, double d, double thresh) {
  ARCSim::Mesh &mesh = *edge->n[0]->mesh;
  ARCSim::RemeshOp op;
  ARCSim::Node *node0 = edge->n[0], *node1 = edge->n[1],
               *node = new ARCSim::Node((1 - d) * node0->y + d * node1->y,
                                        (1 - d) * node0->x + d * node1->x,
                                        (1 - d) * node0->v + d * node1->v,
                                        0,  // node0->label & node1->label,
                                        node0->flag & node1->flag, false);
  node->acceleration = (1 - d) * node0->acceleration + d * node1->acceleration;
  op.added_nodes.push_back(node);
  op.removed_edges.push_back(edge);
  op.added_edges.push_back(
      new ARCSim::Edge(node0, node, edge->theta_ideal, edge->preserve));
  op.added_edges.push_back(
      new ARCSim::Edge(node, node1, edge->theta_ideal, edge->preserve));
  ARCSim::Vert *vnew[2] = {NULL, NULL};
  for (int s = 0; s < 2; s++) {
    if (!edge->adjf[s]) continue;
    ARCSim::Vert *v0 = edge_vert(edge, s, s), *v1 = edge_vert(edge, s, 1 - s),
                 *v2 = edge_opp_vert(edge, s);
    if (s == 0 || is_seam_or_boundary(edge)) {
      vnew[s] = new ARCSim::Vert(ARCSim::Vec3(0), ARCSim::Vec3(0));
      project_vertex(vnew[s], edge, s, d);
      connect(vnew[s], node);
      op.added_verts.push_back(vnew[s]);
    } else
      vnew[s] = vnew[0];
    op.added_edges.push_back(new ARCSim::Edge(v2->node, node, 0, 0));
    ARCSim::Face *f = edge->adjf[s];
    op.removed_faces.push_back(f);
    ARCSim::Face *nf0 = new ARCSim::Face(v0, vnew[s], v2, f->Sp_str, f->Sp_bend,
                                         f->material, f->damage);
    ARCSim::Face *nf1 = new ARCSim::Face(vnew[s], v1, v2, f->Sp_str, f->Sp_bend,
                                         f->material, f->damage);

    op.added_faces.push_back(nf0);
    op.added_faces.push_back(nf1);
  }

  bool make_worse = true;
  if (thresh > 0) {
    for (size_t n = 0; n < op.added_nodes.size(); n++) {
      for (int adje = 0; adje < op.added_edges.size(); adje++) {
        if (edge_length(op.added_edges[adje]) < thresh) make_worse = false;
      }
    }
  } else {
    make_worse = false;
  }

  if (make_worse) {
    op.cancel();
  } else {
    op.apply(mesh);
    node->y = (1 - d) * node0->y + d * node1->y;
  }
  return op;
}

ARCSim::RemeshOp collapse_edgeForced(ARCSim::Edge *edge, int i) {
  /*if (is_seam_or_boundary(edge)) {
  Annotation::add(edge);
  cout << "collapse" << endl;
  cout << edge->n[i]->preserve << endl;
  wait_key();
  }*/
  ARCSim::Mesh &mesh = *edge->n[0]->mesh;
  ARCSim::RemeshOp op;
  ARCSim::Node *node0 = edge->n[i], *node1 = edge->n[1 - i];
  op.removed_nodes.push_back(node0);
  for (size_t e = 0; e < node0->adje.size(); e++) {
    ARCSim::Edge *edge1 = node0->adje[e];
    op.removed_edges.push_back(edge1);
    ARCSim::Node *node2 = (edge1->n[0] != node0) ? edge1->n[0] : edge1->n[1];
    if (node2 != node1 && !get_edge(node1, node2))
      op.added_edges.push_back(
          new ARCSim::Edge(node1, node2, edge1->theta_ideal, edge1->preserve));
    // Preserve in weird situations
    // if (node2 != node1 && (get_edge(node1, node2) != NULL && get_edge(node0,
    // node2) != NULL)) { 	if (get_edge(node0, node2)->preserve) {
    // get_edge(node1,
    // node2)->preserve = true;
    //	}
    //}
  }
  for (int s = 0; s < 2; s++) {
    ARCSim::Vert *vert0 = edge_vert(edge, s, i),
                 *vert1 = edge_vert(edge, s, 1 - i);
    if (!vert0 || (s == 1 && vert0 == edge_vert(edge, 0, i))) continue;
    op.removed_verts.push_back(vert0);
    for (size_t f = 0; f < vert0->adjf.size(); f++) {
      ARCSim::Face *face = vert0->adjf[f];
      op.removed_faces.push_back(face);
      if (!is_in(vert1, face->v)) {
        ARCSim::Vert *verts[3] = {face->v[0], face->v[1], face->v[2]};
        replace(vert0, vert1, verts);
        ARCSim::Face *new_face =
            new ARCSim::Face(verts[0], verts[1], verts[2], face->Sp_str,
                             face->Sp_bend, face->material, face->damage);
        op.added_faces.push_back(new_face);
        // inversion test
        if (dot(ARCSim::normal<ARCSim::MS>(face),
                ARCSim::normal<ARCSim::MS>(new_face)) < 0) {
          op.cancel();
          return ARCSim::RemeshOp();
        }
        if (area(new_face) == 0) {
          op.cancel();
          return ARCSim::RemeshOp();
        }
      }
    }
  }
  op.apply(mesh);
  return op;
}

ARCSim::RemeshOp split_face(ARCSim::Face *face, ARCSim::Vec3 b) {
  ARCSim::Mesh &mesh = *face->v[0]->node->mesh;
  ARCSim::RemeshOp op;
  ARCSim::Node *node0 = face->v[0]->node, *node1 = face->v[1]->node,
               *node2 = face->v[2]->node,
               *node = new ARCSim::Node(
                   b[0] * node0->y + b[1] * node1->y + b[2] * node2->y,
                        b[0] * node0->x + b[1] * node1->x + b[2] * node2->x,
                        b[0] * node0->v + b[1] * node1->v + b[2] * node2->v, 0,
                        node0->flag & node1->flag & node2->flag, false);
  node->acceleration = b[0] * node0->acceleration + b[1] * node1->acceleration +
                       b[2] * node2->acceleration;
  op.added_nodes.push_back(node);
  op.added_edges.push_back(new ARCSim::Edge(node0, node, 0.0, false));
  op.added_edges.push_back(new ARCSim::Edge(node1, node, 0.0, false));
  op.added_edges.push_back(new ARCSim::Edge(node2, node, 0.0, false));
  ARCSim::Vert *v0 = face->v[0], *v1 = face->v[1], *v2 = face->v[2];
  ARCSim::Vert *v =
      new ARCSim::Vert(b[0] * v0->u + b[1] * v1->u + b[2] * v2->u,
                     b[0] * v0->v + b[1] * v1->v + b[2] * v2->v);
  v->sizing = b[0] * v0->sizing + b[1] * v1->sizing + b[2] * v2->sizing;
  connect(v, node);
  op.added_verts.push_back(v);
  op.removed_faces.push_back(face);
  ARCSim::Face *nf0 = new ARCSim::Face(v0, v1, v, face->Sp_str, face->Sp_bend,
                                       face->material, face->damage);
  ARCSim::Face *nf1 = new ARCSim::Face(v1, v2, v, face->Sp_str, face->Sp_bend,
                                       face->material, face->damage);
  ARCSim::Face *nf2 = new ARCSim::Face(v2, v0, v, face->Sp_str, face->Sp_bend,
                                       face->material, face->damage);

	op.added_faces.push_back(nf0);
	op.added_faces.push_back(nf1);
	op.added_faces.push_back(nf2);

	op.apply(mesh);
	return op;
}