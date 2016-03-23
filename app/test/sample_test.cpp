#include "include/catch.hpp"

#include "server/PlayerInGame.hpp"
#include "server/Player.hpp"
#include "server/PlayerManager.hpp"
#include "server/Game.hpp"

TEST_CASE("PlayerInGame reacts to attacks, heal, etc...") {

    Player * p1 = PlayerManager::logIn("carlos", "carlos", 1);
    Player * p2 = PlayerManager::logIn("remy", "remy", 2);
    Game * g = new Game();

    PlayerInGame pig(*p1, g);

    SECTION("Player is being attacked with creature") {
    	pig.takeDamage(5);
    	REQUIRE(pig.getHeal() == 15);
    }

    // SECTION("Healing player") {
    // 	REQUIRE(pig.getlifepts() == 15);
    // 	pig.heal();
    // 	REQUIRE(pig.getlifepts() == 20);
    // }
}
