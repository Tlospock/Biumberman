#ifndef _MAP_H
#define _MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "structure.h"

#define IMINDESTRU 1
#define IMAXDESTRU 2

#define HAUTEUR_MAP 50      /* Multiple de 3 */
#define LONGUEUR_MAP 50     /* Multiple de 2 */

typedef struct position{
    short int x;
    short int y;
}Position;

typedef struct bloc{
    int type; /*-1 Indestructible, 0 air, 1 friable*/
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
}Square;

/* TABLEAU DES BONUS
rien        0
feu         1
glace       2
mine        3
radius++    4
radius--    5
vitesse++   6
vitesse--   7
bombe++     8
bombe--     9
vie++       10
poussee     11
*/

void init_map(int** carte, int longueur, int largeur);


#endif /* _MAP_H*/

