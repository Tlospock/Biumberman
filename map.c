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
            carte[i][j].bombe.proprio = -1;
            carte[i][j].bombe.aExplose = -1;
            carte[i][j].bombe.nbpas = 0;

            carte[i][j].bonus =0;
            carte[i][j].idJoueur =-1;
            carte[i][j].danger=0;

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

    generationBonus(carte);
}

void generationBonus(Square** carte)
{
    int x, y;
    int i=1, j=0;

    int tab_nbBonus[11] = {N_FEU, N_GLACE, N_MINE, N_PRADIUS, N_MRADIUS, N_PVITESSE, N_MVITESSE, N_PBOMBE, N_MBOMBE, N_PVIE, N_POUSSEE};

    for(i= 1 ; i<12 ; i++){
        j=0;
        while(j<tab_nbBonus[i-1]) {
            x= rand() % (longueur_map);
            y= rand() % (hauteur_map);
            if(carte[x][y].bloc.type > 0 && carte[x][y].bonus == 0 ){
                carte[x][y].bonus = i;
                j++;
            }
        }
    }

    /**
    int x, y;
    int cpt = 1, i=0;

    while(cpt<12)
    {
        x= rand() % (longueur_map);
        y= rand() % (hauteur_map);

        if(carte[x][y].bloc.type >0 && carte[x][y].bonus == 0 )
        {
            switch(cpt)
            {
            case 1:
                carte[x][y].bonus = FEU;
                ++i;
                if(i>=N_FEU)
                {
                    cpt++;
                    i=0;
                }
                break;
            case 2:
                carte[x][y].bonus = GLACE;
                ++i;
                if(i>=N_GLACE)
                {
                    cpt++;
                    i=0;
                }
                break;
            case 3:
                carte[x][y].bonus = MINE;
                ++i;
                if(i>=N_MINE)
                {
                    cpt++;
                    i=0;
                }
                break;
            case 4:
                carte[x][y].bonus = PRADIUS;
                ++i;
                if(i>=N_PRADIUS)
                {
                    cpt++;
                    i=0;
                }
                break;
            case 5:
                carte[x][y].bonus = MRADIUS;
                ++i;
                if(i>=N_MRADIUS)
                {
                    cpt++;
                    i=0;
                }
                break;
            case 6:
                carte[x][y].bonus = PVITESSE;
                ++i;
                if(i>=N_PVITESSE)
                {
                    cpt++;
                    i=0;
                }
                break;
            case 7:
                carte[x][y].bonus = MVITESSE;
                ++i;
                if(i>=N_MVITESSE)
                {
                    cpt++;
                    i=0;
                }
                break;
            case 8:
                carte[x][y].bonus = PBOMBE;
                ++i;
                if(i>=N_PBOMBE)
                {
                    cpt++;
                    i=0;
                }
                break;
            case 9:
                carte[x][y].bonus = MBOMBE;
                ++i;
                if(i>=N_MBOMBE)
                {
                    cpt++;
                    i=0;
                }
                break;
            case 10:
                carte[x][y].bonus = PVIE;
                ++i;
                if(i>=N_PVIE)
                {
                    cpt++;
                    i=0;
                }
                break;
            case 11:
                carte[x][y].bonus = POUSSEE;
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
     * */
}

void recuperationBonus(Square** carte, Perso* joueur, Mix_Chunk *sonBonus, Mix_Chunk *sonMalus){
    if(carte[joueur->pos.x][joueur->pos.y].bonus != 0){
        switch(carte[joueur->pos.x][joueur->pos.y].bonus){
            case FEU:
                Mix_PlayChannel( -1, sonBonus, 0 );
                joueur->effetBonus =1;
                break;
            case GLACE:
                Mix_PlayChannel( -1, sonBonus, 0 );
                joueur->effetBonus =2;
                break;
            case MINE:
                Mix_PlayChannel( -1, sonBonus, 0 );
                joueur->effetBonus =3;
                break;
            case PRADIUS:
                Mix_PlayChannel( -1, sonBonus, 0 );
                joueur->radius++;
                break;
            case MRADIUS:
                Mix_PlayChannel( -1, sonMalus, 0 );
                if(joueur->radius >1)
                    joueur->radius--;
                break;
            case PVITESSE:
                Mix_PlayChannel( -1, sonBonus, 0 );
                joueur->vitesse+=1;
                break;
            case MVITESSE:
                if(joueur->vitesse>1){
                    joueur->vitesse-=1;
                    Mix_PlayChannel( -1, sonMalus, 0 );
                }
                break;
            case PBOMBE:
                Mix_PlayChannel( -1, sonBonus, 0 );
                joueur->nbBombeTot++;
                break;
            case MBOMBE:
                Mix_PlayChannel( -1, sonMalus, 0 );
                if(joueur->nbBombeTot >1)
                    joueur->nbBombeTot--;
                break;
            case PVIE:
                Mix_PlayChannel( -1, sonBonus, 0 );
                joueur->vie++;
                break;
            case POUSSEE:
                Mix_PlayChannel( -1, sonBonus, 0 );
                joueur->poussee=1;
                break;
        }


    }
    carte[joueur->pos.x][joueur->pos.y].bonus = 0;
}

void detruire_bloc(SDL_Surface* screenSurface, Square** carte, Position pos){
    carte[pos.x][pos.y].bloc.type = 0;
}

/*prend la carte, la position de la bombe à pousser, la direction dans laquelle pousser la bombe
 * puis pousse la bombe.*/
void pousser(Square** carte, Position pos, int dirJoueur){
    switch(dirJoueur){
        /* y-1 square
        * y bombe
        * y +1 joueur*/
        case HAUT :
        printf("CASE UP\n");
        /* S'il n'y a pas de joueur sur la case suivante et qu'il n'y a pas de bombe dessus et qu'elle est un bloc d'air */
            if(carte[pos.x][pos.y-1].bloc.type ==0 && carte[pos.x][pos.y-1].bombe.radius <1){
                printf("ENTER IN DA CONDITION MAGUEULE\n");
                carte[pos.x][pos.y-1].bombe.nbpas = 39;
                carte[pos.x][pos.y-1].bombe.radius = carte[pos.x][pos.y].bombe.radius;
                carte[pos.x][pos.y-1].bombe.decompte = carte[pos.x][pos.y].bombe.decompte;
                carte[pos.x][pos.y-1].bombe.proprio = carte[pos.x][pos.y].bombe.proprio;
                carte[pos.x][pos.y-1].bombe.direction = HAUT;
                carte[pos.x][pos.y].bombe.radius = 0;
                carte[pos.x][pos.y].bombe.decompte = -1;
                carte[pos.x][pos.y].bombe.proprio = -1;
            }
            break;
            /*joueur
             * bombe
             * square*/
        case BAS :
            printf("VALUES OF CONDITION : %d \n", carte[pos.x][pos.y+1].idJoueur>0); 
            printf("VALUES OF CONDITION : %d \n", carte[pos.x][pos.y+1].bloc.type ==0); 
            printf("VALUES OF CONDITION : %d \n", carte[pos.x][pos.y+1].bombe.radius); 
            printf("VALUES OF CONDITION : %d \n", carte[pos.x][pos.y].bombe.radius); 
            if(carte[pos.x][pos.y+1].bloc.type ==0 && carte[pos.x][pos.y+1].bombe.radius == 0){
                printf("WERKS IN MY MACHINE\n");
                carte[pos.x][pos.y+1].bombe.nbpas = 39;
                carte[pos.x][pos.y+1].bombe.radius = carte[pos.x][pos.y].bombe.radius;
                carte[pos.x][pos.y+1].bombe.decompte = carte[pos.x][pos.y].bombe.decompte;
                carte[pos.x][pos.y+1].bombe.proprio = carte[pos.x][pos.y].bombe.proprio;
                carte[pos.x][pos.y+1].bombe.direction = BAS;
                carte[pos.x][pos.y].bombe.radius = 0;
                carte[pos.x][pos.y].bombe.decompte = -1;
                carte[pos.x][pos.y].bombe.proprio = -1;
                printf("TESTING THE BOMB : %d\n", carte[pos.x][pos.y+1].bombe.nbpas);
                printf("TESTING THE BOMB : %d\n", carte[pos.x][pos.y+1].bombe.radius);
                printf("TESTING THE BOMB : %d\n", carte[pos.x][pos.y+1].bombe.decompte);
                printf("TESTING THE BOMB : %d\n", carte[pos.x][pos.y+1].bombe.proprio);
                printf("TESTING THE BOMB : %d\n", carte[pos.x][pos.y+1].bombe.direction);
          }
            break;
        /*square bombe joueur*/
        case GAUCHE :
            if(carte[pos.x-1][pos.y].bloc.type ==0 && carte[pos.x-1][pos.y].bombe.radius <1){
                carte[pos.x-1][pos.y].bombe.nbpas = 39;
                carte[pos.x-1][pos.y].bombe.radius = carte[pos.x][pos.y].bombe.radius;
                carte[pos.x-1][pos.y].bombe.decompte = carte[pos.x][pos.y].bombe.decompte;
                carte[pos.x-1][pos.y].bombe.proprio = carte[pos.x][pos.y].bombe.proprio;
                carte[pos.x-1][pos.y].bombe.direction = GAUCHE;
                carte[pos.x][pos.y].bombe.radius = 0;
                carte[pos.x][pos.y].bombe.decompte = -1;
                carte[pos.x][pos.y].bombe.proprio = -1;
            }
            break;
            /*joueur bombe square*/
        case DROITE : 
            if(carte[pos.x+1][pos.y].bloc.type ==0 && carte[pos.x+1][pos.y].bombe.radius <1){
                    carte[pos.x+1][pos.y].bombe.nbpas = 39;
                    carte[pos.x+1][pos.y].bombe.radius = carte[pos.x][pos.y].bombe.radius;
                    carte[pos.x+1][pos.y].bombe.decompte = carte[pos.x][pos.y].bombe.decompte;
                    carte[pos.x+1][pos.y].bombe.proprio = carte[pos.x][pos.y].bombe.proprio;
                    carte[pos.x+1][pos.y].bombe.direction = DROITE;
                    carte[pos.x][pos.y].bombe.radius = 0;
                    carte[pos.x][pos.y].bombe.decompte = -1;
                    carte[pos.x][pos.y].bombe.proprio = -1;
                }
            break;
    }
}