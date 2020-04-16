#include "ModelLoader.h"

#include "../Core.h"
#include "../Log.h"

#include <unordered_map>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

namespace Core {

	ModelData ModelLoader::LoadModel(const std::string& model_path)
	{
		ModelData model_data;
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn, err;

		bool is_object_not_loaded = !tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, model_path.c_str());
		if (is_object_not_loaded) {
			LOG_WARN("{0}", warn);
			LOG_ERROR("{0}", err);
			CORE_ASSERT(false, "Object {0} was not loaded succesfully", model_path.c_str())
		}

		LOG_WARN("{0}", warn);

		std::unordered_map<glm::vec3, uint32_t> unique_vertices = {};

		for (const auto& shape : shapes) {
			for (const auto& index : shape.mesh.indices) {
				glm::vec3 vertex = { 
					attrib.vertices[3 * index.vertex_index + 0],
					attrib.vertices[3 * index.vertex_index + 1],
					attrib.vertices[3 * index.vertex_index + 2] 
				};

				if (unique_vertices.count(vertex) == 0) {
					unique_vertices[vertex] = static_cast<uint32_t>(model_data.vertices.size());
					model_data.vertices.push_back(vertex);
				}

				model_data.indices.push_back(unique_vertices[vertex]);
			}
		}

		return model_data;
	}

}

