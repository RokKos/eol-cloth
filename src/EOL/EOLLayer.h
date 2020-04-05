#pragma once

#include "../Core/Layer/Layer.h"
#include "../Core/TimeStep.h"

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

	};
}