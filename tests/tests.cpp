#include <gtest/gtest.h>
#include "dragon.hpp"
#include "princess.hpp"
#include "knight.hpp"
#include "npc.hpp"
#include "visitor.hpp"
#include "factory.hpp"
#include "observer.hpp"

TEST(NPCTest, IsCloseTest) {
    auto knight = std::make_shared<Knight>("Knight1", 0, 14);
    auto princess = std::make_shared<Princess>("Princess1", 40, 11);
    auto dragon = std::make_shared<Dragon>("Dragon1", 88, 15);

    ASSERT_TRUE(knight->space_check(princess, 50));
    ASSERT_TRUE(princess->space_check(dragon, 100));
    ASSERT_FALSE(dragon->space_check(knight, 25));
}

TEST(NPCTest, opportunityTest) {
    auto knight = std::make_shared<Knight>("Knight1", 0, 14);
    auto princess = std::make_shared<Princess>("Princess1", 40, 11);
    auto dragon = std::make_shared<Dragon>("Dragon1", 88, 15);

    // Princess
    ASSERT_FALSE(knight->opportunity(princess));
    ASSERT_FALSE(dragon->opportunity(princess));
    ASSERT_FALSE(princess->opportunity(princess));

    // DRAGON
    ASSERT_TRUE(knight->opportunity(dragon));
    ASSERT_FALSE(dragon->opportunity(dragon));
    ASSERT_FALSE(princess->opportunity(dragon));

    // KNIGHT
    ASSERT_TRUE(dragon->opportunity(knight));
    ASSERT_FALSE(knight->opportunity(knight));
    ASSERT_FALSE(princess->opportunity(knight));
}

TEST(visitor_test, visit_test) {
    std::shared_ptr<NPC> knight, princess, dragon;
    knight = std::make_shared<Knight>("Knight1", 0, 14);
    princess = std::make_shared<Princess>("Princess1", 40, 11);
    dragon = std::make_shared<Dragon>("Dragon1", 88, 15);
    std::shared_ptr<Visitor> knight_visitor, princess_visitor, dragon_visitor;
    knight_visitor = std::make_shared<KnightV>();
    princess_visitor = std::make_shared<PrincessV>();
    dragon_visitor = std::make_shared<DragonV>();

    // Princess
    ASSERT_FALSE(princess_visitor->visit(knight));
    ASSERT_FALSE(princess_visitor->visit(dragon));
    ASSERT_FALSE(princess_visitor->visit(princess));

    // DRAGON
    ASSERT_TRUE(dragon_visitor->visit(knight));
    ASSERT_FALSE(dragon_visitor->visit(dragon));
    ASSERT_FALSE(dragon_visitor->visit(princess));

    // KNIGHT
    ASSERT_TRUE(knight_visitor->visit(dragon));
    ASSERT_FALSE(knight_visitor->visit(princess));
    ASSERT_FALSE(knight_visitor->visit(knight));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}