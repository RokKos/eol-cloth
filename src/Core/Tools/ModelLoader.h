#pragma once

#include "tiny_obj_loader.h"

#include <string>
#include <vector>

#include <glm/glm.hpp>

namespace Core {

	struct ModelData
	{
		std::vector<glm::vec3> vertices;
		std::vector<uint32_t> indices;
	};

	class ModelLoader {
	public:
		static ModelData LoadModel(const std::string& model_path);
	};

}