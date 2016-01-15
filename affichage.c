#include "map.h"
#include "affichage.h"

int test(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetVideoMode(LONGUEUR_MAP*15, HAUTEUR_MAP*15, 32, SDL_DOUBLEBUF);
    SDL_WM_SetCaption("The Legend of Biumbercat", NULL);

/*PAUSE*/
int continuer = 1;
    SDL_Event event;
    while (continuer){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                continuer = 0;
        }
    }
/*FIN PAUSE*/

    SDL_Quit();
    return 0;
}
