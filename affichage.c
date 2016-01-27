#include "affichage.h"

/*Renvoie 1 si l'initialisation s'est bien passee*/
int initierSDL(SDL_Window** window, SDL_Surface** screenSurface){
    int success = 1;
    /*initier SDL*/
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        printf( "SDL mal initialisee ! SDL_Error: %s\n", SDL_GetError() );
        success = 0;
    }else{
        /*Creation fenetre*/
        *window = SDL_CreateWindow("The Legend of Biumbercat", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, longueur_map*TILE_SIZE+2*TILE_SIZE, hauteur_map*TILE_SIZE+2*TILE_SIZE, SDL_WINDOW_SHOWN);
        if(*window == NULL){
            printf("Fenetre a pas pu etre creee! SDL_Error: %s\n", SDL_GetError());
            success = 0;
        }else{
            /*Creation screensurface*/
            *screenSurface = SDL_GetWindowSurface( *window );
            if(*screenSurface == NULL){
                printf("\nscreensurface, %s", SDL_GetError());
                success = 0;
            }else{
                /*Faire un fond ROSE*/
                SDL_FillRect(*screenSurface, NULL, SDL_MapRGB((*screenSurface)->format, 0xFF, 0xAA, 0xAA));
            }
        }
    }
    return success;
}

void refresh_map(SDL_Window* window, SDL_Surface* screenSurface, Square** carte)
{
    int i, j;
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB((screenSurface)->format, 0 , 0, 0));
    SDL_Surface *tile1 = SDL_LoadBMP("Img/1.bmp");
    SDL_Surface *tile2 = SDL_LoadBMP("Img/2.bmp");
    SDL_Surface *tile3 = SDL_LoadBMP("Img/3.bmp");
    SDL_Surface *hard = SDL_LoadBMP("Img/hard.bmp");
    SDL_Surface *airGround = SDL_LoadBMP("Img/air.bmp");
    SDL_Surface *bomb1 = SDL_LoadBMP("Img/bomb1.bmp");
    SDL_Rect rect;

    SDL_Rect posTile;
    posTile.x = 0;
    posTile.y = 0;

    for(i=0; i<longueur_map+2; ++i)
    {
        posTile.x = i*40;

        for(j=0; j<hauteur_map+2; ++j)
        {
            posTile.y = j*40;
            if(i==0 || j==0 || i == longueur_map+1 || j == hauteur_map+1)
                SDL_BlitSurface(hard, NULL, screenSurface, &posTile);
            else
            {
                switch(carte[i-1][j-1].bloc.type)
                {
                    case 1:
                        SDL_BlitSurface(tile1, NULL, screenSurface, &posTile);
                        break;
                    case 2:
                        SDL_BlitSurface(tile2, NULL, screenSurface, &posTile);
                        break;
                    case 3:
                        SDL_BlitSurface(tile3, NULL, screenSurface, &posTile);
                        break;
                    case -1:
                        SDL_BlitSurface(hard, NULL, screenSurface, &posTile);
                        break;
                    case 0:
                        SDL_BlitSurface(airGround, NULL, screenSurface, &posTile);
                        break;
                }
                if(carte[i-1][j-1].bombe.radius>0)
                {
                    SDL_BlitSurface(bomb1, NULL, screenSurface, &posTile);
                }
            }

        }
    }
    SDL_FreeSurface(tile1);
    SDL_FreeSurface(tile2);
    SDL_FreeSurface(tile3);
    SDL_FreeSurface(hard);
    SDL_FreeSurface(airGround);
    SDL_FreeSurface(bomb1);
}



void quitter(SDL_Window* window, SDL_Surface* screenSurface){
    SDL_FreeSurface(screenSurface);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void obtenirCheminImage(char* nomFichier)
{
    sprintf(nomFichier, "Img/%s.bmp", nomFichier);
}

/*Affiche le choix du nb de joueurs, renvoie ce nb de joueurs*/
int inputNbJoueurs(SDL_Window* window, SDL_Surface* screenSurface){
    int nbjoueurs=0;

 /*AFFICHAGE DES BOUTONS
  * bouton1 = 1joueur, bouton2= 2joueurs, ...*/
    SDL_Surface *ecriteau = NULL;
    SDL_Rect ecr;
    ecr.x = (longueur_map*TILE_SIZE)/2 - 200;
    ecr.y = 30;

    SDL_Surface *bouton1 = NULL;
    SDL_Rect b1;
    b1.x = ((longueur_map*TILE_SIZE)/2)-20-50;
    b1.y = ((hauteur_map*TILE_SIZE)/2)-20-50;

    SDL_Surface* bouton2 = NULL;
    SDL_Rect b2;
    b2.x = (longueur_map*TILE_SIZE)/2-20-50;
    b2.y = (hauteur_map*TILE_SIZE)/2-20+50;

    SDL_Surface* bouton3 = NULL;
    SDL_Rect b3;
    b3.x = (longueur_map*TILE_SIZE)/2-20+50;
    b3.y = (hauteur_map*TILE_SIZE)/2-20-50;

    SDL_Surface* bouton4 = NULL;
    SDL_Rect b4;
    b4.x = (longueur_map*TILE_SIZE)/2-20+50;
    b4.y = (hauteur_map*TILE_SIZE)/2-20+50;

    bouton1 = SDL_LoadBMP("Img/P1.bmp");
    bouton2 = SDL_LoadBMP("Img/P2.bmp");
    bouton3 = SDL_LoadBMP("Img/P3.bmp");
    bouton4 = SDL_LoadBMP("Img/P4.bmp");
    ecriteau = SDL_LoadBMP("Img/ecriteau_joueurs.bmp");
    if(bouton1 ==NULL || bouton2 == NULL || bouton3 == NULL || bouton4 == NULL || ecriteau == NULL){
        printf("\nBoutons nuls : SDL error = %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    /*Gerer la transparence*/
    SDL_SetColorKey(bouton1, 1, SDL_MapRGB(bouton1->format, 0, 255, 0));
    SDL_SetColorKey(bouton2, 1, SDL_MapRGB(bouton2->format, 0, 255, 0));
    SDL_SetColorKey(bouton3, 1, SDL_MapRGB(bouton3->format, 0, 255, 0));
    SDL_SetColorKey(bouton4, 1, SDL_MapRGB(bouton4->format, 0, 255, 0));
    /*Afficher*/
    SDL_BlitSurface(bouton1, NULL, screenSurface, &b1);
    SDL_BlitSurface(bouton2, NULL, screenSurface, &b2);
    SDL_BlitSurface(bouton3, NULL, screenSurface, &b3);
    SDL_BlitSurface(bouton4, NULL, screenSurface, &b4);
    SDL_BlitSurface(ecriteau, NULL, screenSurface, &ecr);

    SDL_FreeSurface(bouton1);
    SDL_FreeSurface(bouton2);
    SDL_FreeSurface(bouton3);
    SDL_FreeSurface(bouton4);
    SDL_FreeSurface(ecriteau);

    SDL_UpdateWindowSurface(window);

/*GESTION DU CLIC SUR LE BOUTON*/
    /*Si clic, vérifier la pos de la souris, si sur un bouton, alors sélectionner nb de joueurs*/
    SDL_Event e;
    int x, y;
    while(nbjoueurs ==0){
        SDL_WaitEvent(&e);
        switch (e.type){
            case SDL_QUIT :
                nbjoueurs = -1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&x, &y);
                printf("\nPos clic : x = %d, y = %d", x, y);
                /*Clic sur bouton 1*/
                if(x>=b1.x && x<=b1.x+b1.w && y>=b1.y && y<=b1.y+b1.h){
                    nbjoueurs = 1;
                    printf("\nClique sur 1 joueur\n");
                }
                 /*Clic sur bouton 2*/
                else if(x>=b2.x && x<=b2.x+b2.w && y>=b2.y && y<=b2.y+b2.h){
                    nbjoueurs = 2;
                    printf("\nClique sur 2 joueurs\n");
                }
                /*Clic sur bouton 3*/
                else if(x>=b3.x && x<=b3.x+b3.w && y>=b3.y && y<=b3.y+b3.h){
                    nbjoueurs = 3;
                    printf("\nClique sur 3 joueurs\n");
                }
                /*Clic sur bouton 4*/
                else if(x>=b4.x && x<=b4.x+b4.w && y>=b4.y && y<=b4.y+b4.h){
                    nbjoueurs = 4;
                    printf("\nClique sur 4 joueurs\n");
                }
                break;
        }
    }
    return nbjoueurs;
}



/*Affiche le choix d'une map petite ou grande, renvoie 1 pour ue petite map, 2 pour une grande map */
int inputTailleMap(SDL_Window* window, SDL_Surface* screenSurface){
    int choixTaille = 0;
    SDL_Event e;
    int x, y;

    /*AFFICHAGE DES BOUTONS*/
    SDL_Surface *ecriteau = NULL;
    SDL_Rect ecr;
    ecr.x = (longueur_map*TILE_SIZE)/2 - 200;
    ecr.y = 30;

    SDL_Surface *bouton_petit = NULL;
    SDL_Rect bp;
    bp.x = (longueur_map*TILE_SIZE)/2 - 100;
    bp.y = (hauteur_map*TILE_SIZE)/2 - 50;

    SDL_Surface *bouton_grand = NULL;
    SDL_Rect bg;
    bg.x = (longueur_map*TILE_SIZE)/2 - 100;
    bg.y = (hauteur_map*TILE_SIZE)/2 + 50;

    ecriteau = SDL_LoadBMP("Img/ecriteau_taillemap.bmp");
    bouton_petit = SDL_LoadBMP("Img/choix_petit.bmp");
    bouton_grand = SDL_LoadBMP("Img/choix_grand.bmp");
    if(ecriteau == NULL || bouton_petit == NULL || bouton_grand == NULL){
        printf("\nBoutons taille map erreurs : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /*AFFICHER*/
    SDL_BlitSurface(ecriteau, NULL, screenSurface, &ecr);
    SDL_BlitSurface(bouton_petit, NULL, screenSurface, &bp);
    SDL_BlitSurface(bouton_grand, NULL, screenSurface, &bg);

   SDL_UpdateWindowSurface(window);

    SDL_FreeSurface(bouton_grand);
    SDL_FreeSurface(bouton_petit);
    SDL_FreeSurface(ecriteau);

    /*GESTION CLIC BOUTON*/
    while(choixTaille==0){
        SDL_WaitEvent(&e);
        switch(e.type){
            case SDL_QUIT :
                choixTaille = -1;
                break;
            case SDL_MOUSEBUTTONDOWN :
                    SDL_GetMouseState(&x, &y);
                    /*Clic sur bouton PETIT*/
                    if(x>bp.x && x<(bp.x+bp.w) && y>bp.y && y<(bp.y+bp.h)){
                        choixTaille = 1;
                        printf("\nA clique sur PETIT!");
                    }
                    /*Clic sur bouton GRAND*/
                    else if(x>bg.x && x<(bg.x+bg.w) && y>bg.y && y<(bg.y+bg.h)){
                        choixTaille = 2;
                        printf("\nA clique sur GRAND!");
                    }
                    break;
        }
    }
    return choixTaille;
}


void refresh_perso(SDL_Surface* screenSurface, Perso* joueur){
    SDL_Rect pos;

    if(joueur->deplacement){
        switch(joueur->direction){
            case HAUT :
                pos.x = joueur->pos.x * TILE_SIZE+TILE_SIZE;
                pos.y = joueur->pos.y * TILE_SIZE+TILE_SIZE + joueur->nbpas;
                SDL_BlitSurface(joueur->sprite, &joueur->spriteClip[((joueur->nbpas/LIMITFRAME)%2)+4], screenSurface, &pos);
                break;
            case BAS :
                pos.x = joueur->pos.x * TILE_SIZE+TILE_SIZE;
                pos.y = joueur->pos.y * TILE_SIZE+TILE_SIZE - joueur->nbpas;
                SDL_BlitSurface(joueur->sprite, &joueur->spriteClip[((joueur->nbpas/LIMITFRAME)%2)+1], screenSurface, &pos);
                break;
            case GAUCHE :
                pos.x = joueur->pos.x * TILE_SIZE+TILE_SIZE + joueur->nbpas;
                pos.y = joueur->pos.y * TILE_SIZE+TILE_SIZE;
                SDL_BlitSurface(joueur->sprite, &joueur->spriteClip[((joueur->nbpas/LIMITFRAME)%2)+7], screenSurface, &pos);
                break;
            case DROITE :
                pos.x = joueur->pos.x * TILE_SIZE+TILE_SIZE - joueur->nbpas;
                pos.y = joueur->pos.y * TILE_SIZE+TILE_SIZE;
                SDL_BlitSurface(joueur->sprite, &joueur->spriteClip[((joueur->nbpas/LIMITFRAME)%2)+10], screenSurface, &pos);
                break;
        }
        joueur->nbpas--;
        if(joueur->nbpas == 0){ /*S'il a fini de se deplacer*/
            joueur->deplacement = 0;
        }
    }else{
        pos.x= joueur->pos.x*TILE_SIZE+TILE_SIZE;
        pos.y= joueur ->pos.y*TILE_SIZE+TILE_SIZE;
        switch(joueur->direction){
            case HAUT :
                SDL_BlitSurface(joueur->sprite, &joueur->spriteClip[3], screenSurface, &pos);
                break;
            case BAS :
                SDL_BlitSurface(joueur->sprite, &joueur->spriteClip[0], screenSurface, &pos);
                break;
            case GAUCHE :
                SDL_BlitSurface(joueur->sprite, &joueur->spriteClip[6], screenSurface, &pos);
                break;
            case DROITE :
                SDL_BlitSurface(joueur->sprite, &joueur->spriteClip[9], screenSurface, &pos);
                break;
        }
    }
}
