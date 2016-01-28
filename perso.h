#ifndef _PERSO_H
#define _PERSO_H

#include "map.h"
#include "affichage.h"




/* Numero d'identification des effets bonus qui ne modifient pas les caracs
 * 0 Rien
 * 1 Feu
 * 2 Glace
 * 3 Mine
 */

void init_perso(Square **carte, Perso* tab_perso, int nb_perso);

int deplacer(Square** carte, Perso* joueur);

void check_bomb(Square** carte, Perso* tab_joueur);

void poseBombe(Square** carte, Perso* joueur, SDL_Window* window, SDL_Surface* screenSurface);

void mourir(Square** carte, Perso* joueur);

void exploser(Square** carte, int posBombeX, int posBombeY, Perso* tab_joueur);

#endif /* _PERSO_H*/
