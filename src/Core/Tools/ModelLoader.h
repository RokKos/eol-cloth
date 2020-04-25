#pragma once

#include "../Primitives/ModelData.h"

#include "tiny_obj_loader.h"

#include <string>

namespace Core {

	class ModelLoader {
	public:
		static ModelData LoadModel(const std::string& model_path);
	};

}