#include "EOLLayer.h"

#include "../Core/Renderer/RenderCommand.h"
#include "../Core/Core.h"
#include "../Core/Input.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

namespace EOL {
	EOLLayer::EOLLayer()
		: Core::Layer("EOLLayer")
	{
	}

	void EOLLayer::OnAttach()
	{
		Core::Layer::OnAttach();
	}

	void EOLLayer::OnDetach()
	{
		Core::Layer::OnDetach();

	}

	void EOLLayer::OnUpdate(Core::TimeStep ts)
	{
		Core::Layer::OnUpdate(ts);

		prev_time_step_ = ts;

		Core::RenderCommand::SetClearColor(bg_color_);
		Core::RenderCommand::Clear();
	}

	void EOLLayer::OnImGuiRender()
	{
		Core::Layer::OnImGuiRender();

		ImGui::Begin("Settings");
		ImGui::ColorEdit4("BG Color", glm::value_ptr(bg_color_));

		ImGui::Text("This is some useful text. %f", prev_time_step_.GetSeconds());

		ImGui::End();
	}

	void EOLLayer::OnEvent(Core::Event& e)
	{
		Core::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Core::KeyPressedEvent>(BIND_EVENT_FN(EOLLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<Core::KeyTypedEvent>(BIND_EVENT_FN(EOLLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<Core::MouseMovedEvent>(BIND_EVENT_FN(EOLLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<Core::MouseButtonPressedEvent>(BIND_EVENT_FN(EOLLayer::OnMouseButtonPressedEvent));

		Core::Layer::OnEvent(e);
	}

	bool EOLLayer::OnKeyPressedEvent(Core::KeyPressedEvent& e)
	{
		LOG_INFO("EOL LAYER::OnKeyPressedEvent key pressed: {0}", e.GetKeyCode());
		return false;
	}

	bool EOLLayer::OnKeyTypedEvent(Core::KeyTypedEvent& e)
	{
		LOG_INFO("EOLLayer::OnKeyTypedEvent key pressed: {0}", e.GetKeyCode());
		
		switch (e.GetKeyCode()) {
		case Core::KeyCode::H:
			//scene->step(gs->online, gs->exportObjs);
			return true;
		case Core::KeyCode::R:
			//scene->reset();  It was before commented out
			return true;
		case Core::KeyCode::P:
			//scene->partialStep();
			return true;
		case Core::KeyCode::V:
			//camera->toggleFlatView();
			return true;
		}

		return false;
	}

	bool EOLLayer::OnMouseMovedEvent(Core::MouseMovedEvent& e)
	{
		if (Core::Input::IsMouseButtonPressed(Core::MouseCode::Button1)) {
			//camera->mouseMoved(xmouse, ymouse);
			return true;
		}

		return false;
	}

	bool EOLLayer::OnMouseButtonPressedEvent(Core::MouseButtonPressedEvent& e)
	{
		if (e.GetMouseButton() == Core::MouseCode::Button1) {
			double mouse_x = Core::Input::GetMouseX();
			double mouse_y = Core::Input::GetMouseY();

			if (Core::Input::IsKeyPressed(Core::KeyCode::LeftShift) || Core::Input::IsKeyPressed(Core::KeyCode::RightShift)) {
				//Camera->mouseClicked(mouse_x, mouse_y, Camera::TRANSLATE);
				return true;
			}
			else if (Core::Input::IsKeyPressed(Core::KeyCode::LeftControl) || Core::Input::IsKeyPressed(Core::KeyCode::RightControl)) {
				//Camera->mouseClicked(mouse_x, mouse_y, Camera::TRANSLATE);
				return true;
			} 
			else if (Core::Input::IsKeyPressed(Core::KeyCode::LeftAlt) || Core::Input::IsKeyPressed(Core::KeyCode::RightAlt)) {
				//Camera->mouseClicked(mouse_x, mouse_y, Camera::TRANSLATE);
				return true;
			}
			
		}

		return false;
		
	}

}