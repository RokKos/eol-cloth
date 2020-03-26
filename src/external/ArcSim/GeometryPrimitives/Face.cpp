#include "Face.h"

namespace ARCSim {
	// World-space data

	void compute_ws_data() {
		const Vec3& x0 = v[0]->node->x,
			& x1 = v[1]->node->x,
			& x2 = v[2]->node->x;
		n = normalize(cross(x1 - x0, x2 - x0));
		// Mat3x2 F = derivative(x0, x1, x2, face);
		// SVD<3,2> svd = singular_value_decomposition(F);
		// Mat3x2 Vt_ = 0;
		// for (int i = 0; i < 2; i++)
		//     for (int j = 0; j < 2; j++)
		//         Vt_(i,j) = svd.Vt(i,j);
		// R = svd.U*Vt_;
		// F = svd.Vt.t()*diag(svd.s)*svd.Vt;
	}

	// Material space data

	void compute_ms_data() {
		Vec3 d0 = v[1]->u - v[0]->u;
		Vec3 d1 = v[2]->u - v[0]->u;
		Vec3 d2 = cross(d0, d1);
		double dn = norm(d2);

		Mat3x3 Dm3(d0, d1, d2 / dn);
		a = 0.5 * dn;
		m = material ? a * material->density : 0;

		if (a == 0) {
			invDm = Mat3x3(0);
		}
		else {
			invDm = Dm3.inv();
			// clamp
			//auto parent = v[0]->node->mesh->parent;
			//if (parent) {
			//	const double CLAMP = 1000.0 / parent->remeshing.size_min;
			//	SVD<3, 3> svd = singular_value_decomposition(invDm);
			//	for (int i = 0; i<3; i++) {
			//		if (svd.s[i] > CLAMP) {
			//			cout << "clamping " << svd.s[i] << " to " << CLAMP << endl;
			//			svd.s[i] = CLAMP;
			//		}
			//	}
			//	invDm = svd.U * diag(svd.s) * svd.Vt;
			//}
		}
	}
}