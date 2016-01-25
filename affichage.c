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
        *window = SDL_CreateWindow("The Legend of Biumbercat", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LONGUEUR_MAP*TILE_SIZE, HAUTEUR_MAP*TILE_SIZE, SDL_WINDOW_SHOWN);
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

    SDL_Surface *tile1 = SDL_LoadBMP("Img/2.bmp");
    SDL_Surface *tile2 = SDL_LoadBMP("Img/2.bmp");
    SDL_Surface *tile3 = SDL_LoadBMP("Img/2.bmp");
    SDL_Surface *hard = SDL_LoadBMP("Img/hard.bmp");
    SDL_Surface *airGround = SDL_LoadBMP("Img/air.bmp");

    SDL_Rect posTile;
    posTile.x = 0;
    posTile.y = 0;

    for(i=0; i<LONGUEUR_MAP; ++i)
    {
        posTile.x = i*40;

        for(j=0; j<HAUTEUR_MAP; ++j)
        {
            posTile.y = j*40;

            switch(carte[i][j].bloc.type)
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
            SDL_UpdateWindowSurface(window);
        }
    }

}

void refreshPerso(SDL_Window* window, SDL_Surface* screenSurface, Square** carte, Perso* tab_perso, int nb_perso)
{
    int i;
    SDL_Rect posPerso;
    posPerso.x = 0;
    posPerso.y = 0;

    SDL_Surface* joueur1 = SDL_LoadBMP("Img/P1.bmp");
    SDL_Surface* joueur2 = SDL_LoadBMP("Img/P2.bmp");
    SDL_Surface* joueur3 = SDL_LoadBMP("Img/P3.bmp");
    SDL_Surface* joueur4 = SDL_LoadBMP("Img/P4.bmp");





    for(i=0; i<nb_perso; ++i)
    {

    }
     SDL_UpdateWindowSurface(window);
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



/* Charge l'image @path en une texture. Renvoie la texture.
 * ren : le renderer dan lequel charger la texture

SDL_Texture* loadTexture(char* path, SDL_Renderer *ren, SDL_Surface* screenSurface){
    SDL_Texture *texture = NULL;
    SDL_Surface *optSurface = NULL;

    SDL_Surface *loadedSurface = IMG_Load(path);
    if(loadedSurface == NULL){
        printf("\fct loadTextue : pas pu load surface %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    optSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, NULL);
    if(optSurface == NULL){
        printf("\fct loadTextue : pas pu convert optsurface %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(loadedSurface);
    texture = SDL_CreateTextureFromSurface(ren, optSurface);
    if(texture == NULL){
        printf("\fct loadTextue : pas pu createTextureFromSurface %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return texture;
}
*/
/* Faire le rendu de la textue dans le renderer à X;Y */
/*
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, tex, NULL, &dst);
}
*/
