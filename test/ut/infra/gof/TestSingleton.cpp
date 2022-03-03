#include "catch2/catch.hpp"
#include "hiccup/infra/gof/Singleton.h"
// #include <iostream>

USING_HICCUP

namespace {
    SINGLETON(DerivedSingleton) {
        int getValue() const {
            return 1;
        }
    };
}

TEST_CASE("Test Singleton") {
    REQUIRE(DerivedSingleton::getInstance().getValue() == 1);

    DerivedSingleton obj1, obj2; // could default construct!
    // DerivedSingleton obj3(obj1);
    // DerivedSingleton obj4(std::move(obj1));
    // obj1 = obj2;
    // obj1 = DerivedSingleton{};    
}