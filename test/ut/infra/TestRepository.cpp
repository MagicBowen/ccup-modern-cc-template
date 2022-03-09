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

    struct FooValueEqualPred {
        FooValueEqualPred(int v) : value{v} {}
        bool operator()(const Foo& foo) const {
            return foo.getValue() == value;
        }
    private:
        int value;
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

        SECTION("should not add the same entity") {
            auto result = REPO_OF(Foo).add(1, std::make_unique<Foo>(1));
            REQUIRE(status_failed(result));
            REQUIRE(REPO_OF(Foo).size() == 1);
        }

        SECTION("should add more different entities") {
            REPO_OF(Foo).add(2, std::make_unique<Foo>(2));
            REQUIRE(REPO_OF(Foo).size() == 2);
        }

        SECTION("should delete enetity") {
            REPO_OF(Foo).del(1);
            REQUIRE(REPO_OF(Foo).isEmpty());
            REQUIRE(REPO_OF(Foo).size() == 0);
        }

        SECTION("should find existed entity") {
            auto e = REPO_OF(Foo).find(1);
            REQUIRE(e != nullptr);
            REQUIRE(e->getValue() == 1);
        }

        SECTION("should not find unexistent entity") {
            auto e = REPO_OF(Foo).find(2);
            REQUIRE(e == nullptr);
        }

        SECTION("should find by const ussage") {
            const FooRepo& constFooRepo = REPO_OF(Foo);
            auto f = constFooRepo.find(1);
            REQUIRE(f != nullptr);
            // f->increase(); // should compile fail!
        }

        SECTION("shoud find by value") {
            int id = 1;
            auto pred = [id](const auto& foo) {
                return foo.getValue() == id;
            };
            auto f = REPO_OF(Foo).findBy(pred);
            REQUIRE(f != nullptr);
            REQUIRE(f->getValue() == 1);
        }

        SECTION("should find by value functor") {
            FooValueEqualPred pred{1};
            auto f = REPO_OF(Foo).findBy(pred);
            REQUIRE(f != nullptr);
            REQUIRE(f->getValue() == 1);
        }

        SECTION("should not find by nonexistent value") {
            auto f = REPO_OF(Foo).findBy([](const auto& foo){
                return foo.getValue() == 2;
            });
            REQUIRE(f == nullptr);
        }
    }

    REPO_OF(Foo).clear();
    REQUIRE(resourceOccupied == 0);

}