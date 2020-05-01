#include "ShaderStorageArray.h"

#include "../Renderer.h"
#include "../../../Platform/OpenGL/Buffers/OpenGLShaderStorageArray.h"

namespace Core {
	Ref<ShaderStorageArray> ShaderStorageArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<Platform::OpenGLShaderStorageArray>();
		}

		CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}