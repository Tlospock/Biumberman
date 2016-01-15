#ifndef _PERSO_H
#define _PERSO_H

#include "map.h"


typedef struct perso{
    short int id;
    Position pos;
    short int vie;

    short int nbBombeTot;
    short int nbBombePos;

    short int poussee;
    int vitesse;
    int radius;
    short int effetBonus;

}Perso;

/* Numero d'identification des effets bonus qui ne modifient pas les caracs
 * 0 Rien
 * 1 Feu
 * 2 Glace
 * 3 Mine
 */

void init_perso(Square **carte, Perso* tab_perso, int nb_perso);
void deplacer(int idJoueur);
void poseBombe(Square** carte, Perso* idJoueur);
void exploser(Square** carte, Position posBombe);
#endif /* _PERSO_H*/
