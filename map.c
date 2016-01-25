#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "map.h"

void init_map(Square** carte, int longueur, int hauteur)
{
	int i, j, x, y;

	for(i=0; i<longueur; ++i)
	{
		for(j=0; j<hauteur;++j)
        {
            carte[i][j].bloc.type=(rand() % (IMAXDESTRU - IMINDESTRU +1)) + IMINDESTRU;

            /*Initialisation des cases de la map*/

            carte[i][j].bloc.numSprite=carte[i][j].bloc.type;

            carte[i][j].bombe.decompte =-1;
            carte[i][j].bombe.radius = 0;

            carte[i][j].bonus =0;

            carte[i][j].idJoueur =0;

        }
	}

	/* Creation de blocs indestructibles */
	for(i=0; i<hauteur-1; i+=3)
	{
		for(j=0; j<longueur; j=j+2)
		{
			x=rand() % (2);
			y=rand() % (2);
			carte[j+y][i+x].bloc.type = -1;
		}
	}
	for(i=2; i<longueur; i=i+3)
	{
        for(j=1;j<longueur-1;++j)
		{
			if(i<hauteur-1 && carte[j-1][i+1].bloc.type != -1 && carte[j][i+1].bloc.type != -1 && carte[j+1][i+1].bloc.type != -1)
			{

				if(i != 0 && carte[j-1][i-1].bloc.type != -1 && carte[j][i-1].bloc.type != -1 && carte[j+1][i-1].bloc.type != -1 && carte[j-1][i].bloc.type != -1 && carte[j+1][i].bloc.type != -1)
					carte[j][i].bloc.type = -1;
				else if(i == 0)
					carte[j][i].bloc.type = -1;
			}
		}
	}


	/* Creation des blocs d'airs*/
	/*Creation bloc d'air obligatoire*/

	/*Placement joueur en haut à gauche*/
	carte[1][1].bloc.type = carte[1][2].bloc.type = carte[2][1].bloc.type = 0;

	/*Placement joueur en haut à droite*/
	carte[longueur-2][1].bloc.type = carte[longueur-2][2].bloc.type = carte[longueur-3][1].bloc.type = 0;

	/*Placement joueur en bas à gauche*/
	carte[1][hauteur-2].bloc.type = carte[2][hauteur-2].bloc.type = carte[1][hauteur-3].bloc.type = 0;

	/*Placement joueur en haut à gauche*/
	carte[longueur-2][hauteur-2].bloc.type = carte[longueur-2][hauteur-3].bloc.type = carte[longueur-3][hauteur-2].bloc.type = 0;

	/*Création de blocs airs aléatoire (moins du quart de total des blocs)*/
	int nbBlocAir = longueur*hauteur/5;
	int compteur = nbBlocAir;
	while(compteur < 0)
	{
		i=rand() % longueur;
		j=rand() % hauteur;

		if(carte[i][j].bloc.type >0)
		{
			carte[i][j].bloc.type = 0;
			compteur--;
		}
	}


}

void generationBonus(Square** carte)
{
    int x, y;
    int cpt = 1, i=0;
    while(cpt<12)
    {
        x= rand() % (LONGUEUR_MAP);
        y= rand() % (HAUTEUR_MAP);

        if(carte[x][y].bloc.type >0 && carte[x][y].bonus == 0 )
        {
            /*printf(" i: %d, Coord: %d, %d\n", i, x, y);*/

            switch(cpt)
            {
            case 1:
                carte[x][y].bonus = cpt;
                ++i;
                if(i>=N_FEU)
                {
                    cpt++;
                    i=0;
                }
                break;
            case 2:
                carte[x][y].bonus = cpt;
                ++i;
                if(i>=N_GLACE)
                {
                    cpt++;
                    i=0;
                }
                break;
            case 3:
                carte[x][y].bonus = cpt;
                ++i;
                if(i>=N_MINE)
                {
                    cpt++;
                    i=0;
                }
                break;
            case 4:
                carte[x][y].bonus = cpt;
                ++i;
                if(i>=N_PRADIUS)
                {
                    cpt++;
                    i=0;
                }
                break;
            case 5:
                carte[x][y].bonus = cpt;
                ++i;
                if(i>=N_MRADIUS)
                {
                    cpt++;
                    i=0;
                }
                break;
            case 6:
                carte[x][y].bonus = cpt;
                ++i;
                if(i>=N_PVITESSE)
                {
                    cpt++;
                    i=0;
                }
                break;
            case 7:
                carte[x][y].bonus = cpt;
                ++i;
                if(i>=N_MVITESSE)
                {
                    cpt++;
                    i=0;
                }
                break;
            case 8:
                carte[x][y].bonus = cpt;
                ++i;
                if(i>=N_PBOMBE)
                {
                    cpt++;
                    i=0;
                }
                break;
            case 9:
                carte[x][y].bonus = cpt;
                ++i;
                if(i>=N_MBOMBE)
                {
                    cpt++;
                    i=0;
                }
                break;
            case 10:
                carte[x][y].bonus = cpt;
                ++i;
                if(i>=N_PVIE)
                {
                    cpt++;
                    i=0;
                }
                break;
            case 11:
                carte[x][y].bonus = cpt;
                ++i;
                if(i>=N_POUSSEE)
                {
                    cpt++;
                    i=0;
                }
                break;
            }

            i++;
        }
    }
}



void recuperationBonus(Square** carte, Position pos, Perso* tab_perso)
{
    if(carte[pos.x][pos.y].bonus != 0 && carte[pos.x][pos.y].idJoueur >0)
    {
        switch(carte[pos.x][pos.y].bonus)
        {
        case 1:
            tab_perso[carte[pos.x][pos.y].idJoueur].effetBonus =1;
            break;
        case 2:
            tab_perso[carte[pos.x][pos.y].idJoueur].effetBonus =2;
            break;
        case 3:
            tab_perso[carte[pos.x][pos.y].idJoueur].effetBonus =3;
            break;
        case 4:
            tab_perso[carte[pos.x][pos.y].idJoueur].radius++;
            break;
        case 5:
            if(tab_perso[carte[pos.x][pos.y].idJoueur].radius >1)
                tab_perso[carte[pos.x][pos.y].idJoueur].radius--;
            break;
        case 6:
            tab_perso[carte[pos.x][pos.y].idJoueur].vitesse*=2;
            break;
        case 7:
            tab_perso[carte[pos.x][pos.y].idJoueur].vitesse/=2;
            break;
        case 8:
            tab_perso[carte[pos.x][pos.y].idJoueur].radius++;
            break;
        case 9:
            if(tab_perso[carte[pos.x][pos.y].idJoueur].nbBombeTot >1)
                tab_perso[carte[pos.x][pos.y].idJoueur].radius--;
            break;
        case 10:
            tab_perso[carte[pos.x][pos.y].idJoueur].vie++;
            break;
        case 11:
            tab_perso[carte[pos.x][pos.y].idJoueur].poussee=1;
            break;
        }
    }

    carte[pos.x][pos.y].bonus = 0;
}

void detruire_bloc(Square** carte, int posX, int posY)
{
    carte[posX][posY].bloc.type = 0;
    /*Animation de destruction*/
    /*Spawn du bonus*/
}
