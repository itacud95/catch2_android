#include "catch2/catch_all.hpp"
#include <iostream>

__attribute__((constructor)) void BarCtor() {
    std::cout << "**BarCtor()\n";
}

__attribute__((destructor)) void BarDtor() {
    std::cout << "**BarDtor()\n";
}

extern "C" int TestFunction() {
    std::cout << "Bar::TestFunction()\n";
    return 0;
}

TEST_CASE("Bar Test") {
    std::cout << "shared bar test\n";
    REQUIRE(false);
}
