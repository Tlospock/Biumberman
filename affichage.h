#ifndef _AFFICHAGE_H
#define _AFFICHAGE_H

/*#include<SDL_image.h>*/

#include "jeu.h"
#include "map.h"

#define DECALAGE_X 0
#define DECALAGE_Y 0

#define LIMITFRAME 20


int initierSDL(SDL_Window** window, SDL_Surface** screensurface);

void quitter(SDL_Window* window, SDL_Surface* screenSurface);

void refresh_map(SDL_Window* window, SDL_Surface* screenSurface, Square** carte);
/*void refresh_map(SDL_Window* window, SDL_Surface* screenSurface, Square** carte, SpriteBombe* spritebomb);*/

void refresh_perso(SDL_Surface* screenSurface, Perso* joueur);


int inputNbPersos(SDL_Window* window, SDL_Surface* screenSurface);
int inputNbJoueurs(SDL_Window* window, SDL_Surface* screenSurface, int nbPerso);
int inputTailleMap(SDL_Window* window, SDL_Surface* screenSurface);

void animbombe(SDL_Surface* screenSurface, Bombe* bombe, SDL_Rect pos);
/*void animbombe(SDL_Surface* screenSurface, Bombe *bombe, SDL_Rect pos, SpriteBombe* sprB);*/

/*void initSpritesBombe(SDL_Surface* screenSurface, SpriteBombe* spriteBomb);*/

int test(Square** carte);
/*SDL_Texture* loadTexture(char* path, SDL_Renderer *ren, SDL_Surface* screenSurface);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
*/

#endif /* _AFFICHAGE_H*/
