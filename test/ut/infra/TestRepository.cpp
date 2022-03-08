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

    SECTION("should add & del & find & clear entities") {
        auto result = REPO_OF(Foo).add(1, std::make_unique<Foo>(1));
        REQUIRE(!status_failed(result));
        REQUIRE(!REPO_OF(Foo).isEmpty());
        REQUIRE(REPO_OF(Foo).size() == 1);

        //SECTION("should not add the same entity") {
        {
            auto result = REPO_OF(Foo).add(1, std::make_unique<Foo>(1));
            REQUIRE(status_failed(result));
            REQUIRE(REPO_OF(Foo).size() == 1);
        }

        //SECTION("should add more different entities")
        {
            REPO_OF(Foo).add(2, std::make_unique<Foo>(2));
            REQUIRE(REPO_OF(Foo).size() == 2);
        }

        // should delete enetity
        {
            REPO_OF(Foo).del(1);
            REPO_OF(Foo).del(2);
            REQUIRE(REPO_OF(Foo).isEmpty());
            REQUIRE(REPO_OF(Foo).size() == 0);
        }
    }


}