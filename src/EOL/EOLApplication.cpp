#include "EOLApplication.h"

#include "../parseParams.h"

namespace EOL {

	void EOLApplication::OnStart(std::string general_settings_file_path, std::string simulation_settings_file_path)
	{
		Application::OnStart();
		general_settings_file_path = general_settings_file_path;
		simulation_settings_file_path = simulation_settings_file_path;

		general_setting_ = Core::CreateRef<GeneralSettings>();
		load_genset(general_setting_, general_settings_file_path);
	}

}


namespace Core {
	Application* CreateApplication() {
		return new EOL::EOLApplication();
	}
}