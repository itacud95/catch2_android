#define CATCH_CONFIG_MAIN
#include "catch2/catch_session.hpp"

#include <iostream>
extern "C" int RunTests(Catch::Session& session) {
    std::cout << "RunTests()\n";
    return session.run();
}
