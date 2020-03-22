#pragma once
#ifndef __Box__
#define __Box__

#include "Brenderable.h"

#ifdef EOLC_ONLINE
#include "online/MatrixStack.h"
#include "online/Program.h"
#endif // EOLC_ONLINE

#include "Shape.h"
#include "Rigid.h"

namespace EOL {

	class Box : public Brenderable
	{
	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW

		std::shared_ptr<Rigid> rigid;

		Box(const std::shared_ptr<Shape> shape, std::string en);
		virtual ~Box();
		void step(const double h);

#ifdef EOLC_ONLINE
		void draw(std::shared_ptr<Rendering::MatrixStack> MV, const std::shared_ptr<Rendering::Program> p) const;
		void drawSimple(std::shared_ptr<Rendering::MatrixStack> MV, const std::shared_ptr<Rendering::Program> p) const;
		void init();
#endif // EOLC_ONLINE

		int num_points;
		int num_edges;

		Eigen::Vector3d dim;
		Eigen::Vector3d rot;
		Eigen::Vector3d x;  // position
		Eigen::Matrix4d E1;
		Eigen::Matrix4d E1inv;
		Eigen::VectorXd v;
		Eigen::MatrixXd adjoint;

		// These are used for constraints
		Eigen::MatrixXd faceNorms;
		Eigen::MatrixXi edgeFaces;
		Eigen::VectorXi edgeTan;
		Eigen::MatrixXi vertEdges1;


		// Export
		std::string exportName;
		int getBrenderCount() const;
		std::vector<std::string> getBrenderNames() const;
		void exportBrender(std::vector< std::shared_ptr< std::ofstream > > outfiles) const;

	private:
		void generateConstraints();

		const std::shared_ptr<Shape> boxShape;
	};
}

#endif
