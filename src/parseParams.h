#pragma once

#include "Core/Core.h"
#include "EOL/Settings/GeneralSettings.h"
#include "Scene.h"
#include <string>

namespace EOL {

	void load_genset(const Core::Ref<GeneralSettings> general_settings, const std::string& JSON_FILE);

	void load_simset(std::shared_ptr<Scene> scene, const std::string& JSON_FILE);

}