#include "catch2/catch.hpp"
#include "hiccup/infra/gof/Repository.h"

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

        void increase() {
            x++;
        }

        ~Foo() {
            resourceOccupied--;
        }

    private:
        int x{0};
    };

    using FooId = uint32_t;

    DEF_REPO_OF(FooId, Foo) {

    };
    
}

TEST_CASE("Test Repository") {
    REQUIRE(REPO_OF(Foo).isEmpty());
    REQUIRE(REPO_OF(Foo).size() == 0);
}