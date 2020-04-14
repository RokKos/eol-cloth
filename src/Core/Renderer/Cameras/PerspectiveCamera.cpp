#include "PerspectiveCamera.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace Core {


	PerspectiveCamera::PerspectiveCamera() : 
		aspect_ratio_(1.0f), field_of_view_(45.0f), near_clipping_plane_(0.01f), far_clipping_plane_(1000.0f),
		Camera(glm::perspective(field_of_view_, aspect_ratio_, near_clipping_plane_, far_clipping_plane_), glm::mat4(1.0f))

	{
	}

	PerspectiveCamera::PerspectiveCamera(float aspect_ratio, float field_of_view, float near_clipping_plane, float far_clipping_plane) :
		aspect_ratio_(aspect_ratio), field_of_view_(field_of_view), near_clipping_plane_(near_clipping_plane), far_clipping_plane_(far_clipping_plane),
		Camera(glm::perspective(field_of_view, aspect_ratio, near_clipping_plane, far_clipping_plane), glm::mat4(1.0f))
	{
	}

	void PerspectiveCamera::RecalculateProjectionMatrix()
	{
		projection_matrix_ = glm::perspective(field_of_view_, aspect_ratio_, near_clipping_plane_, far_clipping_plane_);
		view_projection_matrix_ = projection_matrix_ * view_matrix_;
	}

}