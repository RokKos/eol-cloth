#pragma once

#include "../../Core/Renderer/RendererAPI.h"

namespace Platform {

	class OpenGLRendererAPI : public Core::RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void Clear() override;
	};


}