#pragma once
#ifndef __Scene__
#define __Scene__

#include "boxTriCollision.h"
#include "BrenderManager.h"

#include "Cloth.h"
#include "Obstacles.h"
#include "Shape.h"
#include "Constraints.h"
#include "GeneralizedSolver.h"

#ifdef EOLC_ONLINE
#include "online/MatrixStack.h"
#include "online/Program.h"
#endif // EOLC_ONLINE

namespace EOL {

	class Scene
	{
	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW

		Scene();
		virtual ~Scene() {};

		void load(const std::string& RESOURCE_DIR);
		void init(const bool& online, const bool& exportObjs, const std::string& OUTPUT_DIR);
		void reset();
		void step(const bool& online, const bool& exportObjs);
		void partialStep();

#ifdef EOLC_ONLINE
		void draw(std::shared_ptr<Rendering::MatrixStack> MV, const std::shared_ptr<Rendering::Program> p) const;
		void drawSimple(std::shared_ptr<Rendering::MatrixStack> MV, const std::shared_ptr<Rendering::Program> p) const;
#endif // EOLC_ONLINE



	public:
		Eigen::Vector3d grav;
		std::shared_ptr<GeneralizedSolver> GS;
		std::shared_ptr<Cloth> cloth;
		std::shared_ptr<Obstacles> obs;
		std::vector<std::shared_ptr<btc::Collision> > cls;

		double h;
		bool EOLon;
		bool REMESHon;

		int part;

	private:

		double t;

		// Export
		BrenderManager* brender;

	};
}

#endif
