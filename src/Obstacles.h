#pragma once
#ifndef __Obstacles__
#define __Obstacles__

#include "BrenderManager.h"

#include "Points.h"
#include "Box.h"
#include "Shape.h"

#ifdef EOLC_ONLINE
#include "online/MatrixStack.h"
#include "online/Program.h"
#endif // EOLC_ONLINE

namespace EOL {

	class Obstacles
	{
	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW

		Obstacles();
		virtual ~Obstacles() {};

		int num_boxes;
		double cdthreshold;
		std::shared_ptr<Points> points;
		std::vector<std::shared_ptr<Box> > boxes;
		std::vector<std::shared_ptr<Shape> > shapes;

		void load(const std::string& RESOURCE_DIR);
		void step(double h);

		void addExport(BrenderManager* brender);

#ifdef EOLC_ONLINE
		void draw(std::shared_ptr<Rendering::MatrixStack> MV, const std::shared_ptr<Rendering::Program> p) const;
		void drawSimple(std::shared_ptr<Rendering::MatrixStack> MV, const std::shared_ptr<Rendering::Program> p) const;
		void init();
#endif // EOLC_ONLINE

	private:

	};
}

#endif