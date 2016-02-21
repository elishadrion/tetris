#ifndef DRAW_HPP
#define	DRAW_HPP

#include "server/Card.hpp"
#include "server/CardCreature.hpp"
#include "server/Effect.hpp"
#include "server/Game.hpp"

class Draw : public Effect{

    std::size_t _nDraw;
public:
    Draw(std::size_t nDraw):_nDraw(nDraw){};
    ~Draw(){};

    //Soit on suit le meme principe que Taunt avec une fonction isDraw qui est gérée dans le jeu
    //Soit on peut peut-etre include Game (la fonction qui pioche)
    //et apply lancerait la fonction comme ci-dessous

    virtual void apply(CardMonster*) override;
};

void Draw::apply(CardMonster* target){
    for (std::size_t i=0; i<_nDraw; i++){
        // Game::draw();
        // @Rémy
    }
}

#endif	/* DRAW_HPP */
