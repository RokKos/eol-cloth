#include <time.h>

#ifdef EOLC_MOSEK
#include "external/SolverWrappers/Mosek/QuadProgMosek.h"
#endif

#ifdef EOLC_GUROBI
#include "external/SolverWrappers/Gurobi/Gurobi.h"
#endif

#include "conversions.h"
#include "runner.h"

int main(int argc, char **argv)
{
	if (argc < 3) {
		std::cout << "Usage: " << std::endl;
		std::cout << "	" << argv[0] << "<general setting> <simulation settings>" << std::endl;
		std::cout << "where the settings arguments are json file" << std::endl;
		std::cout << std::endl << "Refer to the examples and json templates for further details" << std::endl;
		return 0;
	}

	srand(time(NULL));
    
	EOL::start_running(argv[1], argv[2]);

    return 0;
}