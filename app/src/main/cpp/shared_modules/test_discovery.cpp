#include "catch2/catch_session.hpp"

extern "C" int RunTests(int argc, char *argv[], Catch::Session& session) {
    return session.run(argc, argv);
}

extern "C" int RunTestsv2() {
    static auto session = Catch::Session();
    return session.run();
}
