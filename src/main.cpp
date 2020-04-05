#include <time.h>

#include "runner.h"
#include "Core/Log.h"

int main(int argc, char **argv)
{
	Core::Log::Init();

	if (argc < 3) {
		LOG_WARN("\nUsage:\n	{0} <general setting> <simulation settings>\n where the settings arguments are json file\n Refer to the examples and json templates for further details", argv[0]);
		return 0;
	}

	srand(time(NULL));
    
	start_running(argv[1], argv[2]);

    return 0;
}