#include "EOLLayer.h"

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
	}

	void EOLLayer::OnImGuiRender()
	{
		Core::Layer::OnImGuiRender();
	}

	void EOLLayer::OnEvent(Core::Event& e)
	{
		Core::Layer::OnEvent(e);
	}
}