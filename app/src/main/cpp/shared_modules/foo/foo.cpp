#include "catch2/catch_all.hpp"
#include <iostream>

__attribute__((constructor)) void FooCtor() {
    std::cout << "**FooCtor()\n";
}

__attribute__((destructor)) void FooDtor() {
    std::cout << "**FooDtor()\n";
}

extern "C" int TestFunction() {
    std::cout << "Foo::TestFunction()\n";
    return 0;
}

TEST_CASE("Foo Test") {
    std::cout << "shared foo test\n";
    REQUIRE(true);
}
