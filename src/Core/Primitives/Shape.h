#pragma once

#include "../Components/Transform.h"
#include "ModelData.h"
#include "../Renderer/Buffers/VertexArray.h"

namespace Core {

	class Shape
	{
	public:
		Shape() = default;
		
		Shape(const Ref<VertexArray>& vertex_array, const Ref<Transform>& transform, const ModelData& model_data = ModelData(), const std::string& name = "shape");

		const Ref<VertexArray>& GetVertexArray() const { return vertex_array_; }
		const Ref<Transform>& GetTransform() const { return transform_; }

	private:
		std::string name_ = "shape";

		Ref<VertexArray> vertex_array_;
		ModelData model_data_ = ModelData();
		Ref<Transform> transform_;
	};
}