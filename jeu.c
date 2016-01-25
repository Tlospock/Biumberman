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

int menu_joueurs(SDL_Window* window, SDL_Surface* screenSurface, SDL_Event event){
    int nbjoueurs;

 /*AFFICHAGE DES BOUTONS
  * bouton1 = 1joueur, bouton2= 2joueurs, ...*/
    SDL_Surface *ecriteau = NULL;
    SDL_Rect ecr;
    ecr.x = (LONGUEUR_MAP*TILE_SIZE)/2 - 200;
    ecr.y = 30;

    SDL_Surface *bouton1 = NULL;
    SDL_Rect b1;
    b1.x = ((LONGUEUR_MAP*TILE_SIZE)/2)-20-50;
    b1.y = ((HAUTEUR_MAP*TILE_SIZE)/2)-20-50;

    SDL_Surface* bouton2 = NULL;
    SDL_Rect b2;
    b2.x = (LONGUEUR_MAP*TILE_SIZE)/2-20-50;
    b2.y = (HAUTEUR_MAP*TILE_SIZE)/2-20+50;

    SDL_Surface* bouton3 = NULL;
    SDL_Rect b3;
    b3.x = (LONGUEUR_MAP*TILE_SIZE)/2-20+50;
    b3.y = (HAUTEUR_MAP*TILE_SIZE)/2-20-50;

    SDL_Surface* bouton4 = NULL;
    SDL_Rect b4;
    b4.x = (LONGUEUR_MAP*TILE_SIZE)/2-20+50;
    b4.y = (HAUTEUR_MAP*TILE_SIZE)/2-20+50;

    bouton1 = SDL_LoadBMP("Img/P1.bmp");
    bouton2 = SDL_LoadBMP("Img/P2.bmp");
    bouton3 = SDL_LoadBMP("Img/P3.bmp");
    bouton4 = SDL_LoadBMP("Img/P4.bmp");
    ecriteau = SDL_LoadBMP("Img/ecriteau_joueurs.bmp");
    if(bouton1 ==NULL || bouton2 == NULL || bouton3 == NULL || bouton4 == NULL || ecriteau == NULL){
        printf("\nBoutons nuls : SDL error = %s\n", IMG_GetError());
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


/*GESTION DU CLIC SUR LE BOUTON*/
    /*Si clic, vérifier la pos de la souris, si sur un bouton, alors sélectionner nb de joueurs*/
        if(event.type == SDL_MOUSEBUTTONDOWN){
            int x, y;
            SDL_GetMouseState(&x, &y);
            printf("\nPos clic : x = %d, y = %d", x, y);
            /*Clic sur bouton 1*/
            if(x>=b1.x && x<=b1.x+TILE_SIZE && y>=b1.y && y<=b1.y+TILE_SIZE){
                nbjoueurs = 1;
                printf("\nClique sur 1 joueur\n");
            }
             /*Clic sur bouton 2*/
            if(x>=b2.x && x<=b2.x+TILE_SIZE && y>=b2.y && y<=b2.y+TILE_SIZE){
                nbjoueurs = 2;
                printf("\nClique sur 2 joueurs\n");
            }
            /*Clic sur bouton 3*/
            if(x>=b3.x && x<=b3.x+TILE_SIZE && y>=b3.y && y<=b3.y+TILE_SIZE){
                nbjoueurs = 3;
                printf("\nClique sur 3 joueurs\n");
            }
            /*Clic sur bouton 4*/
            if(x>=b4.x && x<=b4.x+TILE_SIZE && y>=b4.y && y<=b4.y+TILE_SIZE){
                nbjoueurs = 4;
                printf("\nClique sur 4 joueurs\n");
            }

        }

    SDL_UpdateWindowSurface(window);

    return nbjoueurs;
}


int jeu(){
    int i, j;
    int nbPerso=NB_PERSONNAGE;

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

     SDL_UpdateWindowSurface(window);
    int done =0;
    while(!quit){
        while(SDL_PollEvent(&e)!=0){
            /*User requests quit*/
            if(e.type == SDL_QUIT){
                quit = 1;
            }
            /*menu_joueurs(window, screenSurface, e);*/
            if(done==0)
            {
                refresh_map(window, screenSurface, carte);
                done=1;
            }

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
