#pragma once
#ifndef __Points__
#define __Points__

#ifdef EOLC_ONLINE
#include "online/MatrixStack.h"
#include "online/Program.h"
#endif // EOLC_ONLINE

namespace EOL {

	class Points
	{
	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW

		Points() : num_points(0) {};
		virtual ~Points() {};

		int num_points;
		Eigen::MatrixXd pxyz;
		Eigen::MatrixXd norms;

#ifdef EOLC_ONLINE
		void drawSimple(std::shared_ptr<Rendering::MatrixStack> MV, const std::shared_ptr<Rendering::Program> p) const;
#endif // EOLC_ONLINE

	private:

	};
}

#endif