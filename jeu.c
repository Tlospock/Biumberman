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
    hauteur_map = 15;
    longueur_map = 16;
    /*Initialisation de la SDL*/
     short int success;

     Position actuelles;

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
    /*Menu choix nb persos jouables puis Menu choix nb joueurs puis Menu choix taille map*/
    int nbPerso = inputNbPersos(window, screenSurface);
    if(nbPerso>0 && nbPerso<=NB_PERSONNAGE_MAX){
        SDL_FillRect(screenSurface, NULL, SDL_MapRGB((screenSurface)->format, 0xFF, 0xAA, 0xAA));
        int nbJoueurs = inputNbJoueurs(window, screenSurface, nbPerso);
        if(nbJoueurs>0){
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB((screenSurface)->format, 0xFF, 0xAA, 0xAA));
            int choixTaille = inputTailleMap(window, screenSurface);
            if(choixTaille>0){

                /*init petite carte*/
                if(choixTaille==1){
                    hauteur_map = 15;
                    longueur_map = 16;
                }else if(choixTaille==2){
                    hauteur_map = 15;
                    longueur_map = 26;
                    SDL_DestroyWindow(window);
                    initierSDL(&window, &screenSurface);
                }
                SDL_FillRect(screenSurface, NULL, SDL_MapRGB((screenSurface)->format, 0xFF, 0xAA, 0xAA));

                /*Déclaration / allocation de la carte de jeu*/
                Square **carte = (Square**)malloc(longueur_map*sizeof(Square*));
                for(i=0; i<longueur_map; i++){
                    carte[i] = (Square*)malloc(hauteur_map*sizeof(Square));
                }
                /*Déclaration/allocation du tableau de joueurs*/
                Perso* tab_joueur = (Perso*)malloc(nbPerso*sizeof(Perso));

                /*Structure qui contient les sprites de la bombe, utile pour l'animation
                SpriteBombe *spritebomb=NULL;*/
                
                init_map(carte, longueur_map, hauteur_map);
                init_perso(carte, tab_joueur, nbPerso);
      /*          initSpritesBombe(screenSurface, spritebomb);*/
                /*Fin Initialisation*/
                /*Boucle de Jeu*/
                /*Initialisation de l'écran de jeu*/
/*Pour que les joueurs puissent appuyer sur les touches en meme temps, sans se bloquer entre eux, 
 * il faut un booleen par key, le mettre a 1 dans le switch du pollevent, puis après le switch gerer les actions */
/*char down1 = 0;
char up1 = 0;
char left = 0;
char right = 0;
char action1 = 0;
char down2 = 0;
char up2 = 0;
char left2 = 0;
char right2 = 0;
char action2 = 0;*/

                while(!quit){
                SDL_PollEvent(&e);
                    /*User requests quit*/
                    switch(e.type){
                        case SDL_QUIT:
                            quit = 1;
                            break;
                        case SDL_KEYDOWN:
                            switch(e.key.keysym.scancode)
                            {
                                /*JOUEUR 1 A LES FLECHES*/
                                case SDL_SCANCODE_DOWN:
                                    if(tab_joueur[0].nbpas==0){
                                        tab_joueur[0].direction = BAS;
                                        tab_joueur[0].deplacement = deplacer(carte, &tab_joueur[0]);
                                    }
                                    break;
                                case SDL_SCANCODE_UP:
                                    if(tab_joueur[0].nbpas==0){
                                        tab_joueur[0].direction = HAUT;
                                        tab_joueur[0].deplacement = deplacer(carte, &tab_joueur[0]);
                                    }
                                    break;
                                case SDL_SCANCODE_LEFT:
                                    if(tab_joueur[0].nbpas==0){
                                        tab_joueur[0].direction = GAUCHE;
                                        tab_joueur[0].deplacement = deplacer(carte, &tab_joueur[0]);
                                    }
                                    break;
                                case SDL_SCANCODE_RIGHT:
                                    if(tab_joueur[0].nbpas==0){
                                        tab_joueur[0].direction = DROITE;
                                        tab_joueur[0].deplacement = deplacer(carte, &tab_joueur[0]);
                                    }
                                    break;
                                case SDL_SCANCODE_RETURN:
                                    if(tab_joueur[0].vie>0){
                                        poseBombe(carte, &tab_joueur[0], window, screenSurface);
                                    }
                                   /*         for(i=0; i<hauteur_map; ++i)
                                                {
                                                    for(j=0; j<longueur_map; ++j)
                                                        printf("%d", carte[j][i].idJoueur);
                                                
                                                    printf("\n");
                                                }*/
                                    break;
                                    /*JOUEUR 2 A LES ZQSD*/
                                    case SDL_SCANCODE_S :
                                        if(nbJoueurs > 1 && tab_joueur[1].nbpas==0){
                                            tab_joueur[1].direction = BAS;
                                            tab_joueur[1].deplacement = deplacer(carte, &tab_joueur[1]);
                                        }
                                        break;
                                    case SDL_SCANCODE_W :
                                        if(nbJoueurs > 1 && tab_joueur[1].nbpas==0){
                                            tab_joueur[1].direction = HAUT;
                                            tab_joueur[1].deplacement = deplacer(carte, &tab_joueur[1]);
                                        }
                                        break;
                                    case SDL_SCANCODE_A :
                                        if(nbJoueurs > 1 && tab_joueur[1].nbpas==0){
                                            tab_joueur[1].direction = GAUCHE;
                                            tab_joueur[1].deplacement = deplacer(carte, &tab_joueur[1]);
                                        }
                                        break;
                                    case SDL_SCANCODE_D :
                                        if(nbJoueurs > 1 && tab_joueur[1].nbpas==0){
                                            tab_joueur[1].direction = DROITE;
                                            tab_joueur[1].deplacement = deplacer(carte, &tab_joueur[1]);
                                        }
                                        break;
                                        case SDL_SCANCODE_SPACE:
                                            if(tab_joueur[1].vie>0){
                                            poseBombe(carte, &tab_joueur[1], window, screenSurface);
                                            }
                                            break;
                                default:
                                    break;
                            }
                            break;
                    }
                    check_bomb(carte, tab_joueur);
                    refresh_map(window, screenSurface, carte);
                    for(i=0; i<nbPerso; i++){
                        refresh_perso(screenSurface, &tab_joueur[i]);

                    }
                    SDL_UpdateWindowSurface(window);
            }
                /*Fin de la boucle de Jeu*/

                /*Quitter la SDL*/

                quitter(window, screenSurface);

                /*désallouer le tableau de la carte*/
                for(i=0; i<longueur_map; i++){
                    free(carte[i]);
                }
                free(carte);

                /*désallouer le tableau des joueurs*/
                free(tab_joueur);

                printf("\n\n FIN DU JEU\n\n");
            }
        }
    }
    return 0;
}
