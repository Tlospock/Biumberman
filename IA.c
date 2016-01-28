#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "IA.h"

int prochaineCase(Square** carte, Position actuelle)
{
    int i,j, dir, chemin = 0, hopDone=0, enDanger=0, cpt_caseSafe=0;
    CaseIA caseSafe[61];                                /*On va stocker toutes les cases safes dans un tableau, logiquement les premières seront donc les plus proches */
    for(i=0; i<61; ++i)
        caseSafe[i].hopNb =-1;                          /*Si le hopNb est à -1, on saura que la case n'a pas été initialisée et n'est pas safe. On utilise un compteur pour savoir où on en est dans le tableau*/

    if(carte[actuelle.x][actuelle.y].danger==1)
        enDanger=1;

    int direction;
    CaseIA** tab_path = (CaseIA**)malloc(longueur_map*sizeof(CaseIA*));
    for(i=0; i<longueur_map; i++)
        tab_path[i] = (CaseIA*)malloc(hauteur_map*sizeof(CaseIA));

     for(i=0; i<longueur_map; ++i)
         for(j=0; j<hauteur_map; ++j)
         {
             tab_path[i][j].hopNb = -1;
             tab_path[i][j].posCase.x = i;
             tab_path[i][j].posCase.y = j;
             tab_path[i][j].posCasePrec.x = tab_path[i][j].posCasePrec.y = -1;
         }
    i=j=0;
    tab_path[actuelle.x][actuelle.y].hopNb=0;

    while(hopDone<6)
    {
        ++hopDone;
        for(i=0; i<longueur_map; ++i)
        {
            dir=0;
            for(j=0; j<hauteur_map; ++j)
            {
                if(tab_path[i][j].hopNb == hopDone)
                {
                    if(i+1<longueur_map && carte[i+1][j].bloc.type==0 && carte[i+1][j].bombe.radius==0) /*On regarde la case de droite: DROITE*/
                    {
                        tab_path[i+1][j].hopNb=hopDone;
                        tab_path[i+1][j].posCasePrec.x=i;
                        tab_path[i+1][j].posCasePrec.y=j;

                        if(carte[i+1][j].danger == 0)
                        {
                            caseSafe[cpt_caseSafe].hopNb=hopDone;
                            caseSafe[cpt_caseSafe].posCase.x = i+1;
                            caseSafe[cpt_caseSafe].posCase.y = j;
                            caseSafe[cpt_caseSafe].posCasePrec.x=i;
                            caseSafe[cpt_caseSafe].posCasePrec.y=j;
                            ++cpt_caseSafe;
                        }

                    }
                    else if(i-1<longueur_map && carte[i-1][j].bloc.type==0 && carte[i-1][j].bombe.radius==0) /*On regarde la case de gauche: GAUCHE*/
                    {
                        tab_path[i-1][j].hopNb=hopDone;
                        tab_path[i-1][j].posCasePrec.x=i;
                        tab_path[i-1][j].posCasePrec.y=j;

                        if(carte[i-1][j].danger == 0)
                        {
                            caseSafe[cpt_caseSafe].hopNb=hopDone;
                            caseSafe[cpt_caseSafe].posCase.x = i-1;
                            caseSafe[cpt_caseSafe].posCase.y = j;
                            caseSafe[cpt_caseSafe].posCasePrec.x=i;
                            caseSafe[cpt_caseSafe].posCasePrec.y=j;
                            ++cpt_caseSafe;
                        }
                    }
                    else if(j+1<longueur_map && carte[i][j+1].bloc.type==0 && carte[i][j+1].bombe.radius==0)   /*On regarde la case du dessous: BAS*/
                    {
                        tab_path[i][j+1].hopNb=hopDone;
                        tab_path[i][j+1].posCasePrec.x=i;
                        tab_path[i][j+1].posCasePrec.y=j;

                        if(carte[i][j+1].danger == 0)
                        {
                            caseSafe[cpt_caseSafe].hopNb=hopDone;
                            caseSafe[cpt_caseSafe].posCase.x = i;
                            caseSafe[cpt_caseSafe].posCase.y = j+1;
                            caseSafe[cpt_caseSafe].posCasePrec.x=i;
                            caseSafe[cpt_caseSafe].posCasePrec.y=j;
                            ++cpt_caseSafe;
                        }
                    }
                    else if(j-1<longueur_map && carte[i][j-1].bloc.type==0 && carte[i][j-1].bombe.radius==0)   /*On regarde la case du dessus: HAUT*/
                    {
                        tab_path[i][j-1].hopNb=hopDone;
                        tab_path[i][j-1].posCasePrec.x=i;
                        tab_path[i][j-1].posCasePrec.y=j;

                        if(carte[i][j-1].danger == 0)
                        {
                            caseSafe[cpt_caseSafe].hopNb=hopDone;
                            caseSafe[cpt_caseSafe].posCase.x = i;
                            caseSafe[cpt_caseSafe].posCase.y = j-1;
                            caseSafe[cpt_caseSafe].posCasePrec.x=i;
                            caseSafe[cpt_caseSafe].posCasePrec.y=j;
                            ++cpt_caseSafe;
                        }
                    }

                }
            }
        }
    }

    /*On a fini de remplir les deux tableaux */
    printf("Tableau Path:\n");
    for(i=0; i<hauteur_map; ++i)
    {
        for(j=0; j<longueur_map; ++j)
            printf("%d", tab_path[j][i].hopNb);
        printf("\n");
    }
    printf("\nLOLELOLELOL\n");
    for(i=0; caseSafe[i].hopNb!=-1; ++i)
        printf("numero %d: XSafe %d, Ysafe %d\n", i, caseSafe[i].posCase.x, caseSafe[i].posCase.y);


    for(i=0; i<longueur_map; i++)
        free(tab_path[i]);

    free(tab_path);

    return 0;               /*Retourne BAS, HAUT, GAUCHE, DROITE*/
}

void afficherSafety(Square* carte)
{
    int i, j;


}
