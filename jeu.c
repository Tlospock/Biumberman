#include "jeu.h"


/* DEFINE DES BONUS */
#define RIEN            0
#define FEU              1
#define GLACE         2
#define MINE            3
#define PRADIUS      4
#define MRADIUS     5
#define PVITESSE     6
#define MVITESSE    7
#define PBOMBE       8
#define MBOMBE      9
#define PVIE             10
#define POUSSEE     11


int jeu(){
    int i, j;
    int nbPerso=NB_PERSONNAGE_MAX;

    /*Initialisation de la SDL*/
     short int success;

    /*main loop flag*/
    short int quit = 0;

    /*event handler*/
    SDL_Event e;
    SDL_Window* window;
    SDL_Surface* screenSurface;

    success = initierSDL(&window, &screenSurface);
    if(!success){
        printf("\nPas pu initialiser TLO BIUMBERMAN");
        exit(EXIT_FAILURE);
    }

    /*Menu choix nb joueurs puis Menu choix taille map*/
    int nbJoueurs = inputNbJoueurs(window, screenSurface);
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB((screenSurface)->format, 0xFF, 0xAA, 0xAA));
    int choixTaille = inputTailleMap(window, screenSurface);

    /*Déclaration / allocation de la carte de jeu*/
    Square **carte = (Square**)malloc(LONGUEUR_MAP*sizeof(Square*));
    for(i=0; i<LONGUEUR_MAP; i++){
        carte[i] = (Square*)malloc(HAUTEUR_MAP*sizeof(Square));
    }

    /*Déclaration/allocation du tableau de joueurs*/
    Perso* tab_joueur = (Perso*)malloc(nbPerso*sizeof(Perso));

    init_map(carte, LONGUEUR_MAP, HAUTEUR_MAP);

    init_perso(carte, tab_joueur, nbPerso);

    /*Fin Initialisation*/

    /*Jeu*/

    for(i=0; i<LONGUEUR_MAP; ++i)
    {
        for(j=0; j< HAUTEUR_MAP; ++j)
        {
            if(carte[i][j].bloc.type ==-1)
                printf("0");
            else if(carte[i][j].idJoueur!=0)
                printf("%d", carte[i][j].idJoueur);
            else
                printf("*");
        }


        printf("\n");
    }

    /*Boucle de Jeu*/

    /*Initialisation de l'écran de jeu*/
    refresh_map(window, screenSurface, carte);

     SDL_UpdateWindowSurface(window);
    int done =0;
    while(!quit){
        while(SDL_PollEvent(&e)){
            /*User requests quit*/
            switch(e.type){
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_KEYDOWN:
                    switch(e.key.keysym.scancode)
                    {
                        case SDL_SCANCODE_DOWN:
                            printf("TEST BAS REUSSI\n\n");
                            break;
                        case SDL_SCANCODE_UP:
                            break;
                        case SDL_SCANCODE_LEFT:
                            break;
                        case SDL_SCANCODE_RIGHT:
                            break;
                        default:
                            break;
                    }
                    break;
            }
            /*menu_joueurs(window, screenSurface, e);*/

            refreshPerso(window, screenSurface, carte, tab_joueur, nbPerso);



        }
    }

    /*Fin de la boucle de Jeu*/

    /*Quitter la SDL*/

    quitter(window, screenSurface);

    /*désallouer le tableau de la carte*/
    for(i=0; i<LONGUEUR_MAP; i++){
        free(carte[i]);
    }
    free(carte);

    /*désallouer le tableau des joueurs*/
    free(tab_joueur);

    printf("\n\n FIN DU JEU\n\n");

    return 0;
}
