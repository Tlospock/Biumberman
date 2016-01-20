#include "map.h"
#include "affichage.h"

int test(){
    /*main loop flag*/
    short int quit = 0;

    /*event handler*/
    SDL_Event e;

    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;


    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        printf( "SDL mal initialisee ! SDL_Error: %s\n", SDL_GetError() );
        exit(EXIT_FAILURE);
    }

    /*Creation de la fenetre*/
    window = SDL_CreateWindow("The Legend of Biumbercat", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LONGUEUR_MAP*40, HAUTEUR_MAP*40, SDL_WINDOW_SHOWN);
    if(window == NULL){
        printf("Fenetre a pas pu etre creee! SDL_Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /*Initialisation SDL_image PNG Loading*/
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)){
        printf("\nSDL_image pas pu initialiser! SDL ERROR : %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }

    screenSurface = SDL_GetWindowSurface( window );
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xAA, 0xAA));
    SDL_UpdateWindowSurface(window);
    while(!quit){
        
        menu_joueurs(window, screenSurface);
        while(SDL_PollEvent(&e)!=0){
            if(e.type == SDL_QUIT){
                quit = 1;
            }
        }
    }
    

    SDL_FreeSurface(screenSurface);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
