#include "Shape.h"

namespace Core {

	Shape::Shape(const Ref<VertexArray>& vertex_array, const Ref<Transform>& transform, const ModelData& model_data, const std::string& name) :
		vertex_array_(vertex_array),
		model_data_(model_data),
		transform_(transform),
		name_(name)
	{

	}

}