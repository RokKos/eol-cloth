#include <iostream>
#include <time.h>

#ifdef EOLC_MOSEK
#include "external\SolverWrappers\Mosek\QuadProgMosek.h"
#endif

#ifdef EOLC_GUROBI
#include "external\SolverWrappers\Gurobi\Gurobi.h"
#endif

#include "conversions.h"

#include "runner.h"
#include "Core/Log.h"

using namespace std;
using namespace Eigen;

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