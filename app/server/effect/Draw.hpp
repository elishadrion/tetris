#ifndef DRAW_HPP
#define	DRAW_HPP

#include "server/CardMonster.hpp"
#include "server/Effect.hpp"
#include "server/Game.hpp"

class Draw : public Effect{

    unsigned int _nDraw;
public:
    Draw(unsigned int nDraw):_nDraw(nDraw){};
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
