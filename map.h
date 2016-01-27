#ifndef _MAP_H
#define _MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL.h>

#define IMINDESTRU 1
#define IMAXDESTRU 3


int hauteur_map;/* Multiple de 3 */
int longueur_map;/* Multiple de 2 */
#define TILE_SIZE 40
#define NB_FRAME_ANIMATION 3
#define NB_PERSONNAGE_MAX 4

/*Définition des directions*/
#define BAS 0
#define HAUT 1
#define GAUCHE 2
#define DROITE 3

/*Nombre de bonus pour chaque bonus*/

#define N_FEU 2
#define N_GLACE 2
#define N_MINE 1
#define N_PRADIUS 12
#define N_MRADIUS 6
#define N_PVITESSE 10
#define N_MVITESSE 5
#define N_PBOMBE 50
#define N_MBOMBE 10
#define N_PVIE 4
#define N_POUSSEE 6

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
}Bombe;

typedef struct square{
    short int idJoueur;
    Bloc bloc;
    Bombe bombe;
    short int bonus; /*SELON TABLEAU CI DESSOUS*/
    short int danger;
}Square;

/* TABLEAU DES BONUS
rien        0 :
feu         1 : 2
glace       2 : 2
mine        3 : 1
radius++    4 : 12
radius--    5 : 6
vitesse++   6 : 10
vitesse--   7 : 5
bombe++     8 : 30
bombe--     9 : 10
vie++       10 : 4
poussee     11 : 6
*/

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

}Perso;

void init_map(Square** carte, int longueur, int hauteur);

void generationBonus(Square** carte);

void recuperationBonus(Square** carte, Position pos, Perso* tab_perso); /*Appelée quand un joueur se déplace sur une case avec un bonus*/

void detruire_bloc(Square** carte, int posX, int posY);

#endif /* _MAP_H*/

