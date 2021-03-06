#ifndef _PERSO_H
#define _PERSO_H

#include "map.h"
#include "affichage.h"




/* Numero d'identification des effets bonus qui ne modifient pas les caracs
 * 0 Rien
 * 1 Feu
 * 2 Glace
 * 3 Mine
 * 4 Poussee
 */

void init_perso(Square **carte, Perso* tab_perso, int nb_perso);

int deplacer(Square** carte, Perso* joueur, Mix_Chunk *sonBonus, Mix_Chunk *sonMalus);

void check_bomb(SDL_Surface* screenSurface, Square** carte, Perso* tab_joueur, Mix_Chunk *explosion);
void poseBombe(Square** carte, Perso* joueur, SDL_Window* window, SDL_Surface* screenSurface);

void mourir(Square** carte, Perso* joueur);

void exploser(SDL_Surface* screenSurface, Square** carte, int posBombeX, int posBombeY, Perso* tab_joueur, Mix_Chunk *explosion);

#endif /* _PERSO_H*/
