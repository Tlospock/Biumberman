#ifndef _JEU_H
#define _JEU_H

#include "affichage.h"
#include "perso.h"
#include "map.h"
#include "IA.h"

/*retourne le nb de joueurs*/
int menu_joueurs(SDL_Window* window, SDL_Surface* screenSurface, SDL_Event event);
/*retourne la taille de map choisie*/
int menu_taille();

int jeu();


#endif /* _JEU_H*/

