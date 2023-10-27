#define CATCH_CONFIG_MAIN
#include "catch2/catch_session.hpp"

int main(int argc, char *argv[]) {
    static auto session = Catch::Session();
    session.run(argc, argv);
}
