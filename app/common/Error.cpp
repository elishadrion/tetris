#include "Error.hpp"


std::string ErrorAPI::errorToStr(int errorId) {
    std::string msg = "";
    switch(errorId) {

    case Error::NoError:
        msg = "Aucune erreur";
        break;

    case NotEnoughEnergy:
        msg = "Pas assez d'énergie";
        break;

    case NotEnoughPlace:
        msg = "Pas assez de place";
        break;

    case NotHisTurn:
        msg = "Ce n'est pas à votre tour";
        break;

    case MustAttackTaunt:
        msg = "Vous devez attaquer la carte provoquée";
        break;

    case UnknowError:
        msg = "Erreur inconnue";
        break;

    case NotEffectForPlayer:
        msg = "Pas d'effet contre le joueur";
        break;

    case NotEffectForMonster:
        msg = "Pas d'effet contre les monstres";
        break;

    case MaxCardInDeck:
        msg = "Nombre maximum de carte dans le deck";
        break;

    case SameCardMax:
        msg = "Nombre maximum de carte identique";
        break;

    case CollectionFull:
        msg = "Collection complète";
        break;

    case MaxDeck:
        msg = "Nombre maximum de deck atteint";
        break;

    case MustOneDeckMin:
        msg = "Vous devez avoir un deck au minimum";
        break;

    case DeckNotFound:
        msg = "Deck introuvable";
        break;

    case CardNotFound:
        msg = "Carte introuvable";
        break;

    case NOT_FIRST_TURN:
        msg = "Impossible d'attaquer au premier tour";
        break;

    default:
        msg = "Erreur innexistante";
        break;
    }

    return msg;
}

