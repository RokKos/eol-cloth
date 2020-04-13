#pragma once

#include "../../../Renderer/Cameras/PerspectiveCamera.h"
#include "../../../TimeStep.h"

#include "../../../Events/ApplicationEvent.h"
#include "../../../Events/MouseEvent.h"

namespace Core {

	class PerspectiveCameraController
	{
	public:
		PerspectiveCameraController();
		PerspectiveCameraController(float aspect_ratio, float field_of_view, float near_clipping_plane, float far_clipping_plane);

		void OnUpdate(TimeStep ts);
		void OnEvent(Event& e);

		PerspectiveCamera& GetCamera() { return camera_; }
		const PerspectiveCamera& GetCamera() const { return camera_; }

		float GetZoomLevel() const { return zoom_level_; }
		void SetZoomLevel(float level) { zoom_level_ = level; }

		float GetCameraSpeed() const { return camera_speed_; }
		void SetCameraSpeed(float camera_speed) { camera_speed_ = camera_speed; }
		

	private:
		bool OnMouseMove(MouseMovedEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		PerspectiveCamera camera_;

		glm::vec3 camera_front_ = {0.0, 0.0, 5.0f};
		glm::vec3 camera_up_ = {0.0f, 1.0f, 0.0f};

		float zoom_level_ = 1.0f;
		float camera_speed_ = 1.0f;
	};

}