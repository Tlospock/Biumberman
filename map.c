#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "map.h"

void init_map(Square** carte, int longueur, int hauteur)
{
	int i, j, x, y;
	
	for(i=0; i<hauteur; ++i)
	{
		for(j=0; j<longueur;++j)
			carte[i][j].bloc.type=(rand() % (IMAXDESTRU - IMINDESTRU +1)) + IMINDESTRU;
	}	
	/* Creation de blocs indestructibles */
	for(i=0; i<hauteur-1; ++i)
	{
		for(j=1;j<longueur-1;++j)
		{
			if(i>hauteur-1 && carte[j-1][i+1].bloc.type != -1 && carte[j][i+1].bloc.type != -1 && carte[j+1][i+1].bloc.type != -1)
			{
				if(i != 0 && carte[j-1][i-1].bloc.type != -1 && carte[j][i-1].bloc.type != -1 && carte[j+1][i-1].bloc.type != -1 && carte[j-1][i].bloc.type != -1 && carte[j+1][i].bloc.type != -1)
					carte[j][i].bloc.type = -1;
				else if(i == 0)
					carte[j][i].bloc.type = -1;
			}
		}
		++i;
		for(j=0; j<longueur; j=j+2)
		{
			x=rand() % (2);
			y=rand() % (2);
			carte[j+y][i+x].bloc.type = -1;
		}	
	}
	
	/* Creation des blocs d'airs*/
	/*Creation bloc d'air obligatoire*/
	carte[1][1].bloc.type = carte[1][2].bloc.type = carte[2][1].bloc.type = 0; /*Placement joueur en haut à gauche*/
	carte[longueur-2][1].bloc.type = carte[longueur-2][2].bloc.type = carte[longueur-3][1].bloc.type = 0; /*Placement joueur en haut à droite*/
	carte[1][hauteur-2].bloc.type = carte[hauteur-2][2].bloc.type = carte[hauteur-3][1].bloc.type = 0; /*Placement joueur en bas à gauche*/
	carte[longueur-2][hauteur-2].bloc.type = carte[longueur-2][hauteur-3].bloc.type = carte[longueur-3][hauteur-2].bloc.type = 0; /*Placement joueur en haut à gauche*/
	
	/*Création de blocs airs aléatoires (moins du quart de total des blocs)*/
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

