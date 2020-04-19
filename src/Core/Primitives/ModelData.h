#pragma once

#include <glm/glm.hpp>

#include <vector>

namespace Core {
	
	struct ModelData
	{
		std::vector<glm::vec3> vertices;
		std::vector<uint32_t> indices;
	};

}