#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "IA.h"

int prochaineCase(Square** carte, Position actuelle)
{
    int i,j, chemin = 0, pasFait=0;
    int direction;
    CaseIA** tab_path = (CaseIA**)malloc(longueur_map*sizeof(CaseIA*));
    for(i=0; i<longueur_map; i++)
        tab_path[i] = (CaseIA*)malloc(hauteur_map*sizeof(CaseIA));

     for(i=0; i<longueur_map; ++i)
         for(j=0; j<hauteur_map; ++j)
             tab_path[i][j].hopNb = -1; /*= tab_path[i][j].posCase.x = tab_path[i][j].posCase.y = tab_path[i][j].posCasePrec.x = tab_path[i][j].posCasePrec.y =*/
    i=j=0;
    while(!chemin)
    {
        for(i=0; i<longueur_map; ++i)
        {
            for(j=0; j<hauteur_map; ++j)
            {

            }
        }
        pasFait++;
    }


    for(i=0; i<longueur_map; i++)
        free(tab_path[i]);

    free(tab_path);

    return direction;               /*Retourne BAS, HAUT, GAUCHE, DROITE*/
}
