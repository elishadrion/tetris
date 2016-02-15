#include "include/catch.hpp"

#include "server/PlayerInGame.hpp"

TEST_CASE("PlayerInGame reacts to attacks, heal, etc...") {
    PlayerInGame pig;

    SECTION("Player is being attacked with creature") {
	pig.receiveAttack(5);
	REQUIRE(pig.getlifepts() == 15);
    }

    SECTION("Healing player") {
	REQUIRE(pig.getlifepts() == 15);
	pig.heal();
	REQUIRE(pig.getlifepts() == 20);
    }
}
