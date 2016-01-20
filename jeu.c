#include "jeu.h"
#include "perso.h"

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

int menu_joueurs(SDL_Window* window, SDL_Surface* screenSurface){
    int nbjoueurs;
    
    SDL_Event* event;
    
 /*bouton1 = 1joueur, bouton2= 2joueurs, ...*/
    SDL_Surface* bouton1_opt = NULL;
    SDL_Surface* bouton2_opt = NULL;
    SDL_Surface* bouton3_opt = NULL;
    SDL_Surface* bouton4_opt = NULL;
    
    SDL_Surface* bouton1_load = IMG_Load("Img/P1.png");
    SDL_Surface* bouton2_load = IMG_Load("Img/P2.png");
    SDL_Surface* bouton3_load = IMG_Load("Img/P3.png");
    SDL_Surface* bouton4_load = IMG_Load("Img/P4.png");
    if(bouton1_load==NULL || bouton2_load == NULL || bouton3_load == NULL || bouton4_load == NULL){
        printf("\nSDL error = %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }
    bouton1_opt = SDL_ConvertSurface(bouton1_load, screenSurface->format, NULL);
    bouton2_opt = SDL_ConvertSurface(bouton2_load, screenSurface->format, NULL);
    bouton3_opt = SDL_ConvertSurface(bouton3_load, screenSurface->format, NULL);
    bouton4_opt = SDL_ConvertSurface(bouton4_load, screenSurface->format, NULL);
    
    if(bouton1_opt==NULL || bouton2_opt == NULL || bouton3_opt == NULL || bouton4_opt == NULL){
        printf("\nSDL error = %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }
    
    SDL_BlitSurface(bouton1_opt, NULL, screenSurface, NULL);
    /*Si clic, vérifier la pos de la souris, si sur un bouton, alors sélectionner nb de joueurs*/
    if(event->type == SDL_MOUSEBUTTONDOWN){
        int x, y;
        SDL_GetMouseState(&x, &y);
        /*bouton1*/
        if(x<=40 && y<=40){
            nbjoueurs = 1;
            printf("\nCliqué sur 1 joueur\n");
        }
    }

    SDL_UpdateWindowSurface(window);
    return 2;
}


int jeu(){
    int i, j;
    int nbPerso=4;

    /*Déclaration / allocation de la carte de jeu*/
    Square **carte = (Square**)malloc(LONGUEUR_MAP*sizeof(Square*));
    for(i=0; i<LONGUEUR_MAP; i++){
        carte[i] = (Square*)malloc(HAUTEUR_MAP*sizeof(Square));
    }

    /*Déclaration/allocation du tableau de joueurs*/
    Perso* tab_joueur = (Perso*)malloc(nbPerso*sizeof(Perso));

    init_map(carte, LONGUEUR_MAP, HAUTEUR_MAP);

    init_perso(carte, tab_joueur, nbPerso);

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
