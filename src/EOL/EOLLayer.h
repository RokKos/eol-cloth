#pragma once

#include "../Core/Layer/Layer.h"
#include "../Core/TimeStep.h"
#include "../Core/Events/KeyEvent.h"
#include "../Core/Events/MouseEvent.h"
#include "../Core/Renderer/Shader.h"
#include "../Core/Renderer/Buffers/VertexArray.h"
#include "../Core/Controllers/Renderer/Camera/PerspectiveCameraController.h"
#include "../Core/Components/Transform.h"
#include "../Core/Scene/Scene.h"

#include "Settings/GeneralSettings.h"

#include <glm/glm.hpp>

namespace EOL {

	class EOLLayer : public Core::Layer
	{
	public:
		EOLLayer(Core::Ref<GeneralSettings> general_setting);
		virtual ~EOLLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Core::TimeStep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Core::Event& e) override;

	private:
		bool OnKeyPressedEvent(Core::KeyPressedEvent& e);
		bool OnKeyTypedEvent(Core::KeyTypedEvent& e);

	private:
		Core::Ref<GeneralSettings> general_setting_;
		Core::TimeStep prev_time_step_;
		glm::vec4 bg_color_ = { 0.1f, 0.1f, 0.1f, 1 };
		
		Core::ShaderLibrary shader_library_;
		
		Core::PerspectiveCameraController perspective_camera_controller_;

		Core::Ref<Core::VertexArray> vertex_array_;
		Core::Ref<Core::VertexArray> vertex_array_box_;

		Core::Transform transform_box_;

		Core::Scene scene_;
	};
}