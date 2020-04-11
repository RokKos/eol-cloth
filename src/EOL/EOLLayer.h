#pragma once

#include "../Core/Layer/Layer.h"
#include "../Core/TimeStep.h"
#include "../Core/Events/KeyEvent.h"
#include "../Core/Events/MouseEvent.h"

#include "Settings/GeneralSettings.h"

#include <glm/glm.hpp>

namespace EOL {

	class EOLLayer : public Core::Layer
	{
	public:
		EOLLayer();
		virtual ~EOLLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Core::TimeStep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Core::Event& e) override;

	private:
		bool OnKeyPressedEvent(Core::KeyPressedEvent& e);
		bool OnKeyTypedEvent(Core::KeyTypedEvent& e);
		bool OnMouseMovedEvent(Core::MouseMovedEvent& e);
		bool OnMouseButtonPressedEvent(Core::MouseButtonPressedEvent& e);

	private:
		Core::TimeStep prev_time_step_;
		glm::vec4 bg_color_ = { 0.1f, 0.1f, 0.1f, 1 };
	};
}