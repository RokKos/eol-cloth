#include "Node.h"

namespace ARCSim {

	void compute_ws_data() {
		n = normal<WS>(this);
		Mat3x3 C(0), C0(0);
		double sum = 0;
		for (size_t v = 0; v < verts.size(); v++) {
			const vector<Face*>& adjfs = verts[v]->adjf;
			for (size_t i = 0; i < adjfs.size(); i++) {
				Face const* face = adjfs[i];
				C += face->a / 3 * curvature<WS>(face);
				C0 += face->a / 3 * curvature<MS>(face);
				sum += face->a;
			}
		}
		Eig<3> eig = eigen_decomposition((C - C0) / sum);
		for (int i = 0; i < 3; i++)
			eig.l[i] = fabs(eig.l[i]);
		curvature = eig.Q * diag(eig.l) * eig.Q.t();
	}

	void compute_ms_data() {
		a = 0;
		m = 0;
		for (size_t v = 0; v < verts.size(); v++) {
			const vector<Face*>& adjfs = verts[v]->adjf;
			for (size_t i = 0; i < adjfs.size(); i++) {
				Face const* face = adjfs[i];
				a += face->a / 3;
				m += face->m / 3;
			}
		}
	}
}