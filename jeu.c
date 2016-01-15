#include "jeu.h"
#include "map.h"

int jeu(){
    int i;

    /*Déclaration / allocation de la carte de jeu*/
    Square **carte = (Square**)malloc(LONGUEUR_MAP*sizeof(Square*));
    for(i=0; i<LONGUEUR_MAP; i++){
        carte[i] = (Square*)malloc(HAUTEUR_MAP*sizeof(Square));
    }


    /*désallouer le tableau de la carte*/
    for(i=0; i<LONGUEUR_MAP; i++){
        free(carte[i]);
    }
    free(carte);

    return 0;
}
