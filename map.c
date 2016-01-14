#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "map.h"

void init_map(int** carte, int longueur, int largeur) /*Prend en paramètre un pointeur sur un tableau à deux dimensions et le rempli*/
{
    /*
        Generation blocs indestructibles
        Generation blocs air (ne pas oublier les position de départ)
        Completer avec des blocs destructibles
    */
    
    int i, j;
    int quart = longueur*largeur/4, demi = longueur*largeur/2;
    
    /* Remplissage de la carte avec que des blocs destructibles */
    
    for(i=0; i<longueur;++i)
    {
        for(j=0;j<largeur;++j)
            carte[i][j]=(rand() % (IMAXDESTRU - IMINDESTRU + 1)) + IMINDESTRU;
    }
    
    /* Création des blocs indestructibles: random */
    
    
    
    /* Création des blocs air: random*/
    
    /* Création des blocs indestru/air fixe qui doivent toujours être là: position de départ, centre de la map*/
    
}

