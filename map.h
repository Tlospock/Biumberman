#ifndef _MAP_H
#define _MAP_H
#ifndef __LINUX__
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>
#elif __WIN32__
    #include <SDL.h>
    #include <SDL_ttf.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define IMINDESTRU 1
#define IMAXDESTRU 3

int hauteur_map;/* Multiple de 3 */
int longueur_map;/* Multiple de 2 */

#define TILE_SIZE 40
#define NB_FRAME_ANIMATION 3
#define NB_PERSONNAGE_MAX 4

#define COMPTE_A_REBOURS 2000

/*Définition des directions*/
#define BAS 0
#define HAUT 1
#define GAUCHE 2
#define DROITE 3

/*Nombre de bonus pour chaque bonus*/

#define RIEN            0
#define FEU              1
#define GLACE         2
#define MINE            3 /*pas implémenté parce que personne ne tombe dans ce piege. Et si on l'affiche pas, ca devient trop dur.*/
#define PRADIUS      4 /*ok*/
#define MRADIUS     5 /*ok*/
#define PVITESSE     6 /*ok*/
#define MVITESSE    7 /*ok*/
#define PBOMBE       8 
#define MBOMBE      9 
#define PVIE             10 /*ok*/
#define POUSSEE     11

#define N_FEU 0
#define N_GLACE 0
#define N_MINE 0
#define N_PRADIUS 5
#define N_MRADIUS 0
#define N_PVITESSE 5
#define N_MVITESSE 0
#define N_PBOMBE 30
#define N_MBOMBE 0
#define N_PVIE 5
#define N_POUSSEE 0


typedef struct position{
    short int x;
    short int y;
}Position;

typedef struct bloc{
    int type; /*-1 Indestructible, 0 air, >1 friable*/
    int numSprite;
}Bloc;

typedef struct bombe{
    int decompte;
    int radius;
    int proprio;
    int aExplose;
}Bombe;

typedef struct caseIA{
    Position posCase;
    Position posCasePrec;
    int hopNb;
}CaseIA;

typedef struct square{
    short int idJoueur;
    Bloc bloc;
    Bombe bombe;
    short int bonus; /*SELON TABLEAU CI DESSOUS*/
    short int danger;
}Square;

typedef struct perso{
    short int id;
    Position pos;
    int direction; /* 0: BAS, 1: HAUT, 2: GAUCHE, 3: DROITE*/
    short int vie;

    short int nbBombeTot;
    short int nbBombePos;

    short int poussee;
    float vitesse;
    int radius;
    short int effetBonus;

    int deplacement; /*BOOLEEN : bouge ou bouge pas*/
    int nbpas;
    SDL_Rect spriteClip[12];
    SDL_Surface* sprite;
    
    short int gagnant;
}Perso;

void init_map(Square** carte, int longueur, int hauteur);

void generationBonus(Square** carte);

void recuperationBonus(Square** carte, Perso* joueur);
void detruire_bloc(SDL_Surface* screenSurface, Square** carte, Position pos);

void getbonus_Bombe(Square** carte, int x, int y, Perso* joueur);
void getbonus_Vie(Square** carte, int x, int y, Perso* joueur);

#endif /* _MAP_H*/

