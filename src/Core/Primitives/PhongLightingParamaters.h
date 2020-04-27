#pragma once

#include "glm/glm.hpp"
namespace Core {
	struct PhongLightingParameters
	{
		glm::vec3 diffuse_color_;
		glm::vec3 specular_color_;
		float specular_scatering_;
		glm::vec3 ambient_color_;
		glm::vec3 ambient_intensity_;

		bool operator==(const PhongLightingParameters& other) const {
			return diffuse_color_ == other.diffuse_color_ && specular_color_ == other.specular_color_ && specular_scatering_ == other.specular_scatering_ && ambient_color_ == other.ambient_color_ && ambient_intensity_ == other.ambient_intensity_;
		}

	};
}