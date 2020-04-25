#pragma once

#include "Texture.h"

#include "../../Core.h"

namespace Core {

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(uint32_t width, uint32_t height);
		static Ref<Texture2D> Create(const std::string& path);
	};

}