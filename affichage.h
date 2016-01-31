#ifndef _AFFICHAGE_H
#define _AFFICHAGE_H

#include "map.h"
#include "string.h"

#define DECALAGE_X 0
#define DECALAGE_Y 0

#define LIMITFRAME 20

int initierSDL(SDL_Window** window, SDL_Surface** screensurface);

void quitter(SDL_Window* window, SDL_Surface* screenSurface);

void refresh_map(SDL_Window* window, SDL_Surface* screenSurface, Square** carte, Perso* tabJoueur);

void refresh_perso(SDL_Surface* screenSurface, Perso* joueur);


int inputNbPersos(SDL_Window* window, SDL_Surface* screenSurface);
int inputNbJoueurs(SDL_Window* window, SDL_Surface* screenSurface, int nbPerso);
int inputTailleMap(SDL_Window* window, SDL_Surface* screenSurface);

void animbombe(SDL_Surface* screenSurface, Bombe* bombe, SDL_Rect pos);
void animexplosion(SDL_Surface* screenSurface, Bombe *bombe, SDL_Rect pos, Square** carte, int radius);
int timer(SDL_Surface* screenSurface, int start);
int finjeu(SDL_Window* window, SDL_Surface* screenSurface, Perso* tab_joueurs, int nbjoueurs);

int test(Square** carte);

void affichebonus(SDL_Surface* screenSurface, short int bonus, SDL_Rect *pos);

#endif /* _AFFICHAGE_H*/
