#pragma once

#include "EOLLayer.h"
#include "../Core/Application.h"

#include <string>

namespace EOL {

	class EOLApplication : public Core::Application
	{
	public:
		EOLApplication(std::string general_settings_file_path, std::string simulation_settings_file_path);

		~EOLApplication()
		{
		}
		

		const std::string& GetGeneralSettingFilePath() const {
			return general_settings_file_path_;
		}

		const std::string& GetSimulationSettingFilePath() const {
			return simulation_settings_file_path_;
		}

		const Core::Ref<GeneralSettings>& GetGeneralSettings() const { return general_setting_; }

	private:
		std::string general_settings_file_path_;
		std::string simulation_settings_file_path_;

		Core::Ref<GeneralSettings> general_setting_;
	};



}