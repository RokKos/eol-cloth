#include "EOLLayer.h"

#include <imgui.h>
#include "../Core/Renderer/RenderCommand.h"

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

		Core::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Core::RenderCommand::Clear();
	}

	void EOLLayer::OnImGuiRender()
	{
		Core::Layer::OnImGuiRender();

		ImGui::Begin("Settings");
		float col[3];
		ImGui::ColorEdit3("Square Color", col);
		ImGui::End();
	}

	void EOLLayer::OnEvent(Core::Event& e)
	{
		Core::Layer::OnEvent(e);
	}
}