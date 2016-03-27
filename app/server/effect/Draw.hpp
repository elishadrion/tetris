#ifndef DRAW_HPP
#define	DRAW_HPP

#include "server/CardMonster.hpp"
#include "server/Effect.hpp"
#include "server/Game.hpp"

class Draw : public Effect{

    unsigned int _nDraw;
public:
    Draw(unsigned int nDraw):_nDraw(nDraw){}
    ~Draw() = default;
    
    virtual void apply(CardMonster*, Game*) override;
};

/**
 * Make draw the current player of the game
 *
 * @param target : the monster who get the effect
 * @param game : the game where the effect will be apply
 */
void Draw::apply(CardMonster* target, Game* game) {
    for (std::size_t i=0; i<_nDraw; i++){
        game->draw();
        usleep(100);
    }
}

#endif	/* DRAW_HPP */
