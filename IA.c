#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "IA.h"

int prochaineCase(Square** carte, Position actuelle, Perso* joueur, SDL_Window* window, SDL_Surface* screenSurface)
{
    int i,j, dir, hopDone=0, enDanger=0, cpt_caseSafe=0;
    CaseIA caseSafe[61];                                                /*Tableau qui va stocker les cases safe dans le range de pas de l'IA*/
    CaseIA parcourue;                                                   /*On va stocker toutes les cases safes dans un tableau, logiquement les premières seront donc les plus proches */
    for(i=0; i<61; ++i)
        caseSafe[i].hopNb =-1;                                          /*Si le hopNb est à -1, on saura que la case n'a pas été initialisée et n'est pas safe. On utilise un compteur pour savoir où on en est dans le tableau*/

    if(carte[actuelle.x][actuelle.y].danger==1)
        enDanger=1;

    CaseIA** tab_path = (CaseIA**)malloc(longueur_map*sizeof(CaseIA*));     /*Carte des déplacements de l'IA avec un "rayon" de tant de pas*/
    for(i=0; i<longueur_map; i++)
        tab_path[i] = (CaseIA*)malloc(hauteur_map*sizeof(CaseIA));

     for(i=0; i<longueur_map; ++i)                                          /*On rempli le tablea avec les valeurs par défaut*/
         for(j=0; j<hauteur_map; ++j)
         {
             tab_path[i][j].hopNb = -1;
             tab_path[i][j].posCase.x = i;
             tab_path[i][j].posCase.y = j;
             tab_path[i][j].posCasePrec.x = tab_path[i][j].posCasePrec.y = -1;
         }
    i=j=0;
    tab_path[actuelle.x][actuelle.y].hopNb=0;                               /*On met le pas à 0 pour la case où est le joueur*/

    while(hopDone<5)                                                        /*Tant qu'on a pas fait 5 sauts*/
    {
        ++hopDone;
        for(i=0; i<longueur_map; ++i)                                       /*On parcourt la dimension longueur du tableau*/
        {
            dir=0;
            for(j=0; j<hauteur_map; ++j)                                    /*On parcourt la dimension hauteur du tableau*/
            {
                if(tab_path[i][j].hopNb == hopDone-1)                       /*Si la case vaut le nombre de pas auquels on en est -1*/
                {
                    /*printf("i+1: %d, lMap: %d, typeBloc: %d, radius %d", i+1, longueur_map, carte[i+1][j].bloc.type, carte[i+1][j].bombe.radius);*/
                    if(i+1<longueur_map && carte[i+1][j].bloc.type==0 && carte[i+1][j].bombe.radius==0 && tab_path[i+1][j].hopNb==-1) /*On regarde la case de droite et on la stocke dans tab_path: DROITE*/
                    {
                        tab_path[i+1][j].hopNb=hopDone;
                        tab_path[i+1][j].posCasePrec.x=i;
                        tab_path[i+1][j].posCasePrec.y=j;

                        if(carte[i+1][j].danger == 0)           /**/
                        {
                            caseSafe[cpt_caseSafe].hopNb=hopDone;
                            caseSafe[cpt_caseSafe].posCase.x = i+1;
                            caseSafe[cpt_caseSafe].posCase.y = j;
                            caseSafe[cpt_caseSafe].posCasePrec.x=i;
                            caseSafe[cpt_caseSafe].posCasePrec.y=j;
                            ++cpt_caseSafe;
                        }

                    }
                    if(i-1>0 && carte[i-1][j].bloc.type==0 && carte[i-1][j].bombe.radius==0 && tab_path[i-1][j].hopNb==-1) /*On regarde la case de gauche: GAUCHE*/
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
                    if(j+1<longueur_map && carte[i][j+1].bloc.type==0 && carte[i][j+1].bombe.radius==0 && tab_path[i][j+1].hopNb==-1)   /*On regarde la case du dessous: BAS*/
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
                    if(j-1>0 && carte[i][j-1].bloc.type==0 && carte[i][j-1].bombe.radius==0 && tab_path[i][j-1].hopNb==-1)   /*On regarde la case du dessus: HAUT*/
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
    /*printf de test*/
    /*printf("Tableau Path:\n");
    for(i=0; i<hauteur_map; ++i)
    {
        for(j=0; j<longueur_map; ++j)
        {
            if(tab_path[j][i].hopNb==-1)
                printf("%d", tab_path[j][i].hopNb);
            else
                printf(" %d", tab_path[j][i].hopNb);
        }

        printf("\n");
    }
    printf("\nLOLELOLELOL\n");

    afficherSafety(carte);

    printf("\nSUPERCLAPIER\n");
    for(i=0; caseSafe[i].hopNb!=-1; ++i)
        printf("case numero %d: hop %d, XSafe %d, Ysafe %d\n", i, caseSafe[i].hopNb, caseSafe[i].posCase.x, caseSafe[i].posCase.y);*/
    /*fin printf de test*/

    /*On va enfin commencer à chercher la case où on vas se déplacer*/
    hopDone=6; /*Je sais même pas pouquroi je fais ça mais j'ose pas l'enlever vu que ça fonctionne*/

    if(enDanger)       /*Si on est en danger, on cherche la case safe la plus proche*/
    {
        if(caseSafe[0].hopNb!=-1)       /*On va à la case safe la plus proche*/
        {

            parcourue = caseSafe[0];
            while(parcourue.hopNb >=1)
            {
                if(parcourue.hopNb==1) /*On cherche la direction où il faut aller*/
                {
                    if(parcourue.posCase.x == actuelle.x && parcourue.posCase.y == actuelle.y-1)
                        return HAUT;
                    else if(parcourue.posCase.x == actuelle.x && parcourue.posCase.y == actuelle.y+1)
                        return BAS;
                    else if(parcourue.posCase.x == actuelle.x-1 && parcourue.posCase.y == actuelle.y)
                        return GAUCHE;
                    else if(parcourue.posCase.x == actuelle.x+1 && parcourue.posCase.y == actuelle.y)
                        return DROITE;


                }
                parcourue = tab_path[parcourue.posCasePrec.x][parcourue.posCasePrec.y];
            }
        }
        /*Si aucune case safe à moins de 5 cases, l'IA accepte son destin*/
        return -1;
    }
    else /*Si n'est pas en danger*/ /*Gère la pose de bombe*/
    {
        int bCpt=0;
        int caseRand, tRand=0;
        while(caseSafe[tRand].hopNb !=-1 && caseSafe[tRand].hopNb==1)
            ++tRand;

        /*On va chercher si dans le tableau des cases safes, il y a une case qui n'est pas soit sur le même x ni le même y*/
        /*Si il en existe une on va essayer "d'y aller": si on passe par des cases de danger, on break et on fait le mouvement random*/
        if(rand() %4 ==1)   /*Une chance sur 4 de poser une bombe en cas de de possibilité sinon random*/
        {
            while(caseSafe[bCpt].hopNb != -1)
            {
                if(caseSafe[bCpt].posCase.x != actuelle.x && caseSafe[bCpt].posCase.y != actuelle.y)
                {
                    parcourue = caseSafe[bCpt];
                      while(1)
                      {
                            if(carte[parcourue.posCasePrec.x][parcourue.posCasePrec.y].danger == 1)
                                break;

                            if(parcourue.hopNb==1) /*On cherche la direction où il faut aller*/
                            {
                                i=0;
                                j=1;
                                int trucAtaper=0;
                                while(i<4)  /*On va chercher si une des case autour est explosable ou s'il y a un joueur auquel cas trucAtaper vayt 1 et on pose une bombe*/
                                {

                                    while(j<joueur->radius+1)
                                    {
                                        switch(i)
                                        {
                                            case 0:
                                                if(actuelle.y-j <0)
                                                    j=joueur->radius;
                                                else
                                                {
                                                    if(carte[actuelle.x][actuelle.y-j].bloc.type >0 || (carte[actuelle.x][actuelle.y-j].idJoueur!=-1 && carte[actuelle.x][actuelle.y-j].idJoueur!=joueur->id))
                                                    {
                                                        trucAtaper=1;
                                                        j=joueur->radius;
                                                        i=5;
                                                    }

                                                }
                                                break;
                                            case 1:
                                                if(actuelle.y+j >hauteur_map-1)
                                                    j=joueur->radius;
                                                else
                                                {
                                                    if(carte[actuelle.x][actuelle.y+j].bloc.type >0 || (carte[actuelle.x][actuelle.y+j].idJoueur!=-1 && carte[actuelle.x][actuelle.y+j].idJoueur!=joueur->id))
                                                    {
                                                        trucAtaper=1;
                                                        j=joueur->radius;
                                                        i=5;
                                                    }
                                                }
                                                break;
                                            case 2:
                                                if(actuelle.x-j <0)
                                                    j=joueur->radius;
                                                else
                                                {
                                                    if(carte[actuelle.x-j][actuelle.y].bloc.type >0 || (carte[actuelle.x-j][actuelle.y].idJoueur!=-1 && carte[actuelle.x-j][actuelle.y].idJoueur!=joueur->id))
                                                    {
                                                        trucAtaper=1;
                                                        j=joueur->radius;
                                                        i=5;
                                                    }
                                                }
                                                break;
                                            default:
                                                if(actuelle.x+j >longueur_map-1)
                                                    j=joueur->radius;
                                                else
                                                {
                                                    if(carte[actuelle.x+j][actuelle.y].bloc.type >0 || (carte[actuelle.x+j][actuelle.y].idJoueur!=-1 && carte[actuelle.x+j][actuelle.y].idJoueur!=joueur->id))
                                                    {
                                                        trucAtaper=1;
                                                        j=joueur->radius;
                                                        i=5;
                                                    }
                                                }
                                                break;
                                        }
                                        ++j;
                                    }
                                    j=1;
                                    ++i;
                                }

                                if(trucAtaper)
                                    poseBombe(carte, joueur, window, screenSurface);

                                if(parcourue.posCase.x == actuelle.x && parcourue.posCase.y == actuelle.y-1)
                                    return HAUT;
                                else if(parcourue.posCase.x == actuelle.x && parcourue.posCase.y == actuelle.y+1)
                                    return BAS;
                                else if(parcourue.posCase.x == actuelle.x-1 && parcourue.posCase.y == actuelle.y)
                                    return GAUCHE;
                                else if(parcourue.posCase.x == actuelle.x+1 && parcourue.posCase.y == actuelle.y)
                                    return DROITE;
                            }
                            parcourue = tab_path[parcourue.posCasePrec.x][parcourue.posCasePrec.y];
                      }
                }
                ++bCpt;
            }
        }

        /*mouvement random: par défaut*/
        if (tRand !=0)
        {
            caseRand = rand() % (tRand);
            parcourue = caseSafe[caseRand];
        }
        if(parcourue.hopNb==1) /*On cherche la direction où il faut aller*/
        {
            if(parcourue.posCase.x == actuelle.x && parcourue.posCase.y == actuelle.y-1)
                return HAUT;
            else if(parcourue.posCase.x == actuelle.x && parcourue.posCase.y == actuelle.y+1)
                return BAS;
            else if(parcourue.posCase.x == actuelle.x-1 && parcourue.posCase.y == actuelle.y)
                return GAUCHE;
            else if(parcourue.posCase.x == actuelle.x+1 && parcourue.posCase.y == actuelle.y)
                return DROITE;


        }
        return -1;


    }

    for(i=0; i<longueur_map; i++)
        free(tab_path[i]);

    free(tab_path);

    return 0;               /*Retourne BAS, HAUT, GAUCHE, DROITE*/
}



void afficherSafety(Square** carte)
{
    int i, j;
    for(i=0; i<hauteur_map; ++i)
    {
        for(j=0; j<longueur_map; ++j)
        {
            if(carte[j][i].bloc.type == 0)
                printf("%d", carte[j][i].danger);
            else
                printf("B");
        }
        printf("\n");
    }
}
