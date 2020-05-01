#pragma once

#include "../Components/Transform.h"
#include "../Components/Material.h"
#include "ModelData.h"
#include "../Renderer/Buffers/VertexArray.h"

namespace Core {

	class Shape
	{
	public:
		Shape() = default;
		
		Shape(const Ref<Material>& material, const Ref<VertexArray>& vertex_array, const Ref<Transform>& transform, const ModelData& model_data = ModelData(), const std::string& name = "shape");

		const Ref<Material>& GetMaterial() const { return material_; }
		const Ref<VertexArray>& GetVertexArray() const { return vertex_array_; }
		const Ref<Transform>& GetTransform() const { return transform_; }
		const std::string& GetName() const { return name_; }

	private:
		std::string name_ = "shape";

		Ref<Material> material_;
		Ref<VertexArray> vertex_array_;
		ModelData model_data_ = ModelData();
		Ref<Transform> transform_;
	};
}