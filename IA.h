#ifndef _IA_H

#define _IA_H

#include "perso.h"

int prochaineCase(Square** carte, Position actuelle, Perso* joueur, SDL_Window* window, SDL_Surface* screenSurface);

void afficherSafety(Square** carte);

#endif // _IA_H
