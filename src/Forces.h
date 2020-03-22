#pragma once
#ifndef __Forces__
#define __Forces__

#include <Eigen/StdVector>

#include "TypeDefinitions.h"

#ifdef EOLC_ONLINE
#include "online/MatrixStack.h"
#include "online/Program.h"
#endif // EOLC_ONLINE


namespace EOL {

	class Forces
	{
	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW

		Forces() : EoL_cutoff(0) {};
		virtual ~Forces() {};

		Eigen::VectorXd f;
		Eigen::SparseMatrix<double> M;
		Eigen::SparseMatrix<double> MDK;

		int EoL_cutoff;

		void fill(const ARCSim::Mesh& mesh, const Material& mat, const Eigen::Vector3d& grav, double h);

#ifdef EOLC_ONLINE
		void drawSimple(const ARCSim::Mesh& mesh, std::shared_ptr<Rendering::MatrixStack> MV, const std::shared_ptr<Rendering::Program> p) const;
#endif // EOLC_ONLINE
	};

}

#endif