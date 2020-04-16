#include "VertexBuffer.h"

#include "../Renderer.h"
#include "../../../Platform/OpenGL/Buffers/OpenGLVertexBuffer.h"

namespace Core {
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<Platform::OpenGLVertexBuffer>(size);
		}

		CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(glm::vec3* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<Platform::OpenGLVertexBuffer>(vertices, size);
		}

		CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}