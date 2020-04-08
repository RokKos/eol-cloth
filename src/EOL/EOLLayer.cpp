#include "EOLLayer.h"

#include "../Core/Renderer/RenderCommand.h"

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
		Core::Layer::OnEvent(e);
	}
}