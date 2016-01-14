#ifndef __STRUCTURE_H
#define _STRUCTURE_H

#define TRUE 1
#define FALSE 0

typedef struct position{
    short int x;
    short int y;
}Position;

typedef struct perso{
    short int id;
    Position pos;
    short int vie;

    short int nbBombeTot;
    short int nbBombePos;

    short int poussee;
    int vitesse;
    int rayonBombe;
    short int effetBonus;

}Perso;

/* Numero d'identification des effets bonus qui ne modifient pas les caracs
 * 0 Rien
 * 1 Feu
 * 2 Glace
 * 3 Mine
 */

typedef struct Bloc{
    int type; /*-1 Indestructible, 0 air, 1 friable*/
    int numSprite;
}Bloc;

typedef struct bombe{
    short int proprio;
    int decompte;
    Position pos;
}Bombe;

#endif // __STRUCTURE_H
