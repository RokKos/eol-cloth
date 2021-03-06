//
// Copyright : Copyright (c) MOSEK ApS, Denmark. All rights reserved.
//
//  File :      opt_server_sync.cc
//
//  Purpose :   Demonstrates how to use MOSEK OptServer
//              to solve optimization problem synchronously
//
#include <fusion.h>



using namespace mosek::fusion;
using namespace monty;

int main(int argc, char ** argv) {
    if (argc<3) {
        std::cout << "Missing argument, syntax is:" << std::endl;
        std::cout << "  opt_server_sync host port" << std::endl;
        exit(0);
    }

    std::string server(argv[1]);
    std::string port(argv[2]);

    // Setup a simple test problem
    Model::t M = new Model("testOptServer"); auto _M = finally([&]() { M->dispose(); } );
    Variable::t x = M->variable("x", 3, Domain::greaterThan(0.0));
    M->constraint("lc", Expr::dot(new_array_ptr<double, 1>({1.0, 1.0, 2.0}), x), Domain::equalsTo(1.0));
    M->objective("obj", ObjectiveSense::Minimize, Expr::sum(x));

    // Attach log handler
    M->setLogHandler([](const std::string & msg) { std::cout << msg << std::flush; } );

    // Solve the problem on the OptServer
    M->solve(server, port);

    // Get the solution
    std::cout << "x1,x2,x2 = " << *(x->level()) << std::endl;

    return 0;
}