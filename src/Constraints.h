#pragma once
#ifndef __Constraints__
#define __Constraints__

#include <Eigen/StdVector>

#include "external/ArcSim/GeometryPrimitives/Mesh.h"

#ifdef EOLC_ONLINE
#include "online/MatrixStack.h"
#include "online/Program.h"
#endif // EOLC_ONLINE

#include "Obstacles.h"
#include "FixedList.h"

namespace EOL {

	class Constraints
	{
	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW

		Constraints();
		virtual ~Constraints() {};

		bool hasFixed;
		bool hasCollisions;

		Eigen::SparseMatrix<double> Aeq;
		Eigen::SparseMatrix<double> Aineq;

		std::vector<Eigen::Vector3d, Eigen::aligned_allocator<Eigen::Vector3d> > drawAineq;
		std::vector<Eigen::Vector3d, Eigen::aligned_allocator<Eigen::Vector3d> > drawAeq;

		Eigen::VectorXd beq;
		Eigen::VectorXd bineq;

		Eigen::MatrixXd constraintTable;

		void init(const std::shared_ptr<Obstacles> obs);
		void updateTable(const std::shared_ptr<Obstacles> obs);
		void fill(const ARCSim::Mesh& mesh,
		const std::shared_ptr<Obstacles> obs,
		const std::shared_ptr<FixedList> fs, double h,
		const bool& online);

#ifdef EOLC_ONLINE
		void drawSimple(std::shared_ptr<Rendering::MatrixStack> MV, const std::shared_ptr<Rendering::Program> p) const;
#endif // EOLC_ONLINE
	};
}

#endif