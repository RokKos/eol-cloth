#include "EOLApplication.h"

#include "../parseParams.h"

namespace EOL {

	EOLApplication::EOLApplication(std::string general_settings_file_path, std::string simulation_settings_file_path) :
		general_settings_file_path_(general_settings_file_path), simulation_settings_file_path_(simulation_settings_file_path)
	{
		general_setting_ = Core::CreateRef<GeneralSettings>();
		load_genset(general_setting_, general_settings_file_path);

		PushLayer(new EOLLayer(general_setting_));
	}
	

}


namespace Core {
	Application* CreateApplication(std::string general_settings_file_path, std::string simulation_settings_file_path) {
		return new EOL::EOLApplication(general_settings_file_path, simulation_settings_file_path);
	}
}