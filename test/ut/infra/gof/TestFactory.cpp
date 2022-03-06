#include "catch2/catch.hpp"
#include "hiccup/infra/gof/Factory.h"

USING_HICCUP

namespace {
    struct Foo {

    };

    DEF_FACTORY_OF(Foo) {
        
    };
}

TEST_CASE("Test Factory") {

    SECTION("should create entity") {
        auto f1 = FACTORY_OF(Foo).create();
    }
}