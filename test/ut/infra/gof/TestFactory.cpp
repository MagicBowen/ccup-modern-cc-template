#include "catch2/catch.hpp"
#include "hiccup/infra/gof/Factory.h"

USING_HICCUP

namespace {
    uint32_t resourceOccupied = 0;

    struct Foo {
        Foo(int v) : x{v} {
            resourceOccupied++;
        }

        int getValue() const {
            return x;
        }

        ~Foo() {
            resourceOccupied--;
        }

    private:
        int x{0};
    };

    DEF_FACTORY_OF(Foo) {

    };
}

TEST_CASE("Test Factory") {

    SECTION("should create entity") {
        auto f1 = FACTORY_OF(Foo).create(1);
        REQUIRE(f1->getValue() == 1);

        SECTION("should create more entities") {
            auto f2 = FACTORY_OF(Foo).create(2);
            REQUIRE(f2->getValue() == 2);
            REQUIRE(resourceOccupied == 2);
        }
        REQUIRE(resourceOccupied == 1);
    }
    REQUIRE(resourceOccupied == 0);
}