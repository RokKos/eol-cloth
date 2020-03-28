#include "matlabOutputs.h"

using namespace std;
using namespace Eigen;

#include "external/ArcSim/GeometryPrimitives/Node.h"

namespace EOL {

	// This gets the job done for now
	// TODO:: Traverse sparse structure
	void mat_s2s_file(const SparseMatrix<double>& mat, const string& var_name, const string& file_name, const bool& overwrite)
	{
		ofstream ofs;
		if (overwrite) ofs.open(file_name, ofstream::out | ofstream::trunc);
		else ofs.open(file_name, ofstream::out | ofstream::app);

		MatrixXd dMat = MatrixXd(mat);

		ofs << setprecision(20);

		ofs << "i = [ ";

		for (int i = 0; i < dMat.rows(); i++) {
			for (int j = 0; j < dMat.cols(); j++) {
				if (dMat(i, j) != 0.0) {
					ofs << i + 1 << " ";
				}
			}
		}

		ofs << "]';\n";

		ofs << "j = [ ";

		for (int i = 0; i < dMat.rows(); i++) {
			for (int j = 0; j < dMat.cols(); j++) {
				if (dMat(i, j) != 0.0) {
					ofs << j + 1 << " ";
				}
			}
		}

		ofs << "]';\n";

		ofs << "v = [ ";

		for (int i = 0; i < dMat.rows(); i++) {
			for (int j = 0; j < dMat.cols(); j++) {
				if (dMat(i, j) != 0.0) {
					ofs << setprecision(16) << dMat(i, j) << " ";
				}
			}
		}

		ofs << "]';\n";

		ofs << var_name;
		ofs << " = sparse(i,j,v,";
		ofs << dMat.rows() << "," << dMat.cols() << ");\n\n";

		ofs.close();
	}

	void mat_to_file(const Eigen::MatrixXd& mat, const string& var_name, const string& file_name, const bool& overwrite)
	{
		ofstream ofs;
		if (overwrite) ofs.open(file_name, ofstream::out | ofstream::trunc);
		else ofs.open(file_name, ofstream::out | ofstream::app);

		ofs << setprecision(20);

		ofs << var_name;
		ofs << " = [";
		ofs << mat;
		ofs << "];\n\n";

		ofs.close();
	}

	void mat_to_file(const Eigen::MatrixXi& mat, const string& var_name, const string& file_name, const bool& overwrite)
	{
		ofstream ofs;
		if (overwrite) ofs.open(file_name, ofstream::out | ofstream::trunc);
		else ofs.open(file_name, ofstream::out | ofstream::app);

		ofs << setprecision(20);

		ofs << var_name;
		ofs << " = [";
		ofs << mat;
		ofs << "];\n\n";

		ofs.close();
	}

	void vec_to_file(const Eigen::VectorXd& vec, const string& var_name, const string& file_name, const bool& overwrite)
	{
		ofstream ofs;
		if (overwrite) ofs.open(file_name, ofstream::out | ofstream::trunc);
		else ofs.open(file_name, ofstream::out | ofstream::app);

		ofs << setprecision(20);

		ofs << var_name;
		ofs << " = [\n";
		ofs << vec;
		ofs << "\n];\n\n";

		ofs.close();
	}

	void vec_to_file(const Eigen::VectorXi& vec, const string& var_name, const string& file_name, const bool& overwrite)
	{
		ofstream ofs;
		if (overwrite) ofs.open(file_name, ofstream::out | ofstream::trunc);
		else ofs.open(file_name, ofstream::out | ofstream::app);

		ofs << setprecision(20);

		ofs << var_name;
		ofs << " = [\n";
		ofs << vec;
		ofs << "\n];\n\n";

		ofs.close();
	}

	void mesh2m(const ARCSim::Mesh& mesh, const string& file_name,
		const bool& overwrite) {

		auto nodes = mesh.GetNodes();
		MatrixXd x_X(nodes.size(), 5);
		MatrixXi faces2(3, mesh.GetFaces().size());
		VectorXi isEOL(nodes.size());

		for (int i = 0; i < nodes.size(); i++) {
			ARCSim::Node node = nodes[i];

			if (node.EoL) isEOL(i) = 1;
			else isEOL(i) = 0;
			x_X(i, 0) = node.x[0];
			x_X(i, 1) = node.x[1];
			x_X(i, 2) = node.x[2];
			x_X(i, 3) = node.verts[0]->u[0];
			x_X(i, 4) = node.verts[0]->u[1];
		}

		auto faces = mesh.GetFaces();
		for (int i = 0; i < faces.size(); i++) {
			faces2.col(i) = Vector3i(faces[i].v[0]->node->index, faces[i].v[1]->node->index, faces[i].v[2]->node->index);
		}

		mat_to_file(x_X, "x_X", file_name, overwrite);
		vec_to_file(isEOL, "isEol", file_name, false);
		VectorXi vvv(3);
		vvv << 1, 1, 1;
		mat_to_file(faces2.colwise() += vvv, "faces", file_name, false);
	}

	void double_to_file(double d, const string& var_name, const string& file_name, const bool& overwrite)
	{
		ofstream ofs;
		if (overwrite) ofs.open(file_name, ofstream::out | ofstream::trunc);
		else ofs.open(file_name, ofstream::out | ofstream::app);

		ofs << setprecision(20);

		ofs << var_name;
		ofs << " = ";
		ofs << d;
		ofs << ";\n\n";

		ofs.close();
	}
}