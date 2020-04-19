#pragma once

#include "../Primitives/Shape.h"
#include "../Primitives/Point.h"

#include <vector>

namespace Core {
	class Scene
	{
	public:
		Scene() = default;

		void AddShape(const Ref<Shape>& shape) { shapes_.push_back(shape); }
		const std::vector<Ref<Shape>>& GetShapes() const { return shapes_; }

		void AddPoint(const Ref<Point>& point) { points_.push_back(point); }
		const std::vector<Ref<Point>>& GetPoints() const { return points_; }

	private:
		std::vector<Ref<Shape>> shapes_;  // TODO(Rok Kos): Think if it can be without ref
		std::vector<Ref<Point>> points_;
	};
}