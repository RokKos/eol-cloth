#include <time.h>

#include "runner.h"
#include "Core/Log.h"
//#include "Core/Application.h"
#include "EOL/EOLApplication.h"

extern Core::Application* Core::CreateApplication();

int main(int argc, char **argv)
{
	Core::Log::Init();

	if (argc < 3) {
		LOG_WARN("\nUsage:\n	{0} <general setting> <simulation settings>\n where the settings arguments are json file\n Refer to the examples and json templates for further details", argv[0]);
		return 0;
	}

	srand(time(NULL));
    
	auto app = static_cast<EOL::EOLApplication*>(Core::CreateApplication());// new EOL::EOLApplication();  // TODO(Rok Kos): Check for proper way to use Core::CreateApplication()
	app->OnStart(argv[1], argv[2]);
	app->Run();
	delete app;

	start_running(argv[1], argv[2]);

    return 0;
}