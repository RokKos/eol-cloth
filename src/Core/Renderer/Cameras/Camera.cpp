#pragma once

#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace Core {
	
	void Camera::RecalculateViewMatrix()
	{
		glm::vec3 camera_up = glm::vec3(0.f, 1.f, 0.f);
		glm::mat4 transform = glm::lookAt(position_, position_ + rotation_, camera_up);

		view_matrix_ = glm::inverse(transform);
		view_projection_matrix_ = projection_matrix_ * view_matrix_;
	}

}