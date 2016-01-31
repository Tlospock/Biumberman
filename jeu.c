#include "jeu.h"


int jeu(){
    int i, j;
    int nbalive = 0;
    int time_start = 0;
    
    hauteur_map = 15;
    longueur_map = 16;
    /*Initialisation de la SDL*/
     short int success;

     Position actuelle;

    /*main loop flag*/
    short int quit = 0;    
    int play_again = 0;

    /*event handler*/
    SDL_Event e;
    SDL_Window* window;
    SDL_Surface* screenSurface;

    success = initierSDL(&window, &screenSurface);
    if(!success){
        printf("\nPas pu initialiser TLO BIUMBERMAN");
        exit(EXIT_FAILURE);
    }
    
    do{
        play_again = 0;
  
        SDL_FillRect(screenSurface, NULL, SDL_MapRGB((screenSurface)->format, 0xFF, 0xAA, 0xAA));
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
                    
                    init_map(carte, longueur_map, hauteur_map);
                    init_perso(carte, tab_joueur, nbPerso);
                    /*Fin Initialisation*/
                    /*Boucle de Jeu*/
                    /*Pour que les joueurs puissent appuyer sur les touches en meme temps, sans se bloquer entre eux, 
                    * il faut un booleen par key, le mettre a 1 dans le switch du pollevent, puis après le switch gerer les actions */
                    char down1 = 0; char down2 = 0;
                    char up1 = 0; char up2 = 0;
                    char left1 = 0; char left2 = 0;
                    char right1 = 0; char right2 = 0;
                    char action1 = 0; char action2 = 0;

                    time_start = SDL_GetTicks();
                    do{
                        SDL_PollEvent(&e);
                        switch(e.type){
                             /*User requests quit*/
                            case SDL_QUIT:
                                quit = 1;
                                break;
                            /*à l'appui d'une touche au clavier*/
                            case SDL_KEYDOWN:
                                switch(e.key.keysym.scancode){
                                    /*JOUEUR 1 A LES ZQSD*/
                                    case SDL_SCANCODE_S :
                                        down1 = 1;
                                        break;
                                    case SDL_SCANCODE_W :
                                        up1 = 1;
                                        break;
                                    case SDL_SCANCODE_A :
                                        left1 = 1;
                                        break;
                                    case SDL_SCANCODE_D :
                                        right1 = 1;
                                        break;
                                    case SDL_SCANCODE_SPACE :
                                        poseBombe(carte, &tab_joueur[0], window, screenSurface);
                                        break;
                                        
                                    /*JOUEUR 2 A LES FLECHES*/
                                    case SDL_SCANCODE_DOWN:
                                        down2 = 1;
                                        break;
                                    case SDL_SCANCODE_UP:
                                        up2 = 1;
                                        break;
                                    case SDL_SCANCODE_LEFT:
                                        left2 = 1;
                                        break;
                                    case SDL_SCANCODE_RIGHT:
                                        right2 = 1;
                                        break;
                                    case SDL_SCANCODE_RETURN:
                                        poseBombe(carte, &tab_joueur[1], window, screenSurface);
                                        break;
                                    default :
                                        break;
                                }
                                break;
                            case SDL_KEYUP :
                                switch(e.key.keysym.scancode){
                                    /*JOUEUR 1 A LES ZQSD*/
                                    case SDL_SCANCODE_S :
                                        down1 = 0;
                                        break;
                                    case SDL_SCANCODE_W :
                                        up1 = 0;
                                        break;
                                    case SDL_SCANCODE_A :
                                        left1 = 0;
                                        break;
                                    case SDL_SCANCODE_D :
                                        right1 = 0;
                                        break;
                                    case SDL_SCANCODE_SPACE :
                                        break;
                                            
                                    /*JOUEUR 2 A LES FLECHES*/
                                    case SDL_SCANCODE_DOWN:
                                        down2 = 0;
                                        break;
                                    case SDL_SCANCODE_UP:
                                        up2 = 0;
                                        break;
                                    case SDL_SCANCODE_LEFT:
                                        left2 = 0;
                                        break;
                                    case SDL_SCANCODE_RIGHT:
                                        right2 = 0;
                                        break;
                                    case SDL_SCANCODE_RETURN:
                                        break;
                                    
                                    
                                    case SDL_SCANCODE_ESCAPE:
                                        quit=1;
                                        break;
                                    default :
                                        break;
                                }
                                break;
                        }/*fin switch des touches*/
                        /*Interprétation des booléens des touches du joueur1*/
                        if(down1 && tab_joueur[0].nbpas==0){
                            tab_joueur[0].direction = BAS;
                            tab_joueur[0].deplacement = deplacer(carte, &tab_joueur[0]);
                        }
                        if(up1 && tab_joueur[0].nbpas==0){
                            tab_joueur[0].direction = HAUT;
                            tab_joueur[0].deplacement = deplacer(carte, &tab_joueur[0]);
                            
                        }
                        if(left1 && tab_joueur[0].nbpas==0){
                            tab_joueur[0].direction = GAUCHE;
                            tab_joueur[0].deplacement = deplacer(carte, &tab_joueur[0]);
                        }
                        if(right1 && tab_joueur[0].nbpas==0){
                            tab_joueur[0].direction = DROITE;
                            tab_joueur[0].deplacement = deplacer(carte, &tab_joueur[0]);
                        }
                        /*Interprétation des booléens des touches du joueur1*/
                        if(down2 && nbJoueurs > 1 && tab_joueur[1].nbpas==0){
                            tab_joueur[1].direction = BAS;
                            tab_joueur[1].deplacement = deplacer(carte, &tab_joueur[1]);
                        }
                        if(up2 && nbJoueurs > 1 && tab_joueur[1].nbpas==0){
                            tab_joueur[1].direction = HAUT;
                            tab_joueur[1].deplacement = deplacer(carte, &tab_joueur[1]);
                        }
                        if(left2 && nbJoueurs > 1 && tab_joueur[1].nbpas==0){
                            tab_joueur[1].direction = GAUCHE;
                            tab_joueur[1].deplacement = deplacer(carte, &tab_joueur[1]);
                        }
                        if(right2 && nbJoueurs > 1 && tab_joueur[1].nbpas==0){
                            tab_joueur[1].direction = DROITE;
                            tab_joueur[1].deplacement = deplacer(carte, &tab_joueur[1]);
                        }
                        /*Début gestion IA*/
                    if(nbPerso>1 && nbJoueurs==1)           /*Si il y a plus de 1 joueurs et que le joueur 2 est une IA*/
                    {
                        actuelle = tab_joueur[1].pos;       /*On récupère la position actuelle du joueur*/
                        if(tab_joueur[1].nbpas==0)          /*Si il n'est pas en déplacement*/
                        {
                            if (prochaineCase(carte, actuelle, &tab_joueur[1], window, screenSurface)!= -1)     /*Si la fonction renvoie une direction, -1 étant l'ordre de ne pas bouger*/
                            {
                                tab_joueur[1].direction = prochaineCase(carte, actuelle, &tab_joueur[1], window, screenSurface);    /*On règle la direction de l'IA*/
                                tab_joueur[1].deplacement = deplacer(carte, &tab_joueur[1]);                                        /*On déplace l'IA*/
                            }
                        }
                    }
                    if(nbPerso>2)   /*Si il y a plus de 2 joueurs*/
                    {
                        actuelle = tab_joueur[2].pos;       /*On récupère la position actuelle du joueur*/
                        if(tab_joueur[2].nbpas==0)          /*Si il n'est pas en déplacement*/
                        {
                            if (prochaineCase(carte, actuelle, &tab_joueur[2], window, screenSurface)!= -1)
                            {
                                tab_joueur[2].direction = prochaineCase(carte, actuelle, &tab_joueur[2], window, screenSurface);    /*On règle la direction de l'IA*/
                                tab_joueur[2].deplacement = deplacer(carte, &tab_joueur[2]);                                        /*On déplace l'IA*/
                            }
                        }
                    }
                    if(nbPerso>3)   /*Si il y a plus de 3 joueurs*/
                    {
                        actuelle = tab_joueur[3].pos;
                        if(tab_joueur[3].nbpas==0)
                        {
                            if (prochaineCase(carte, actuelle, &tab_joueur[3], window, screenSurface)!= -1)                         /*Si la fonction renvoie une direction, -1 étant l'ordre de ne pas bouger*/
                            {
                                tab_joueur[3].direction = prochaineCase(carte, actuelle, &tab_joueur[3], window, screenSurface);    /*On règle la direction de l'IA*/
                                tab_joueur[3].deplacement = deplacer(carte, &tab_joueur[3]);                                        /*On déplace l'IA*/
                            }
                        }
                    }

                    /*Fin gestion IA*/
                        
                        check_bomb(screenSurface, carte, tab_joueur);
                        refresh_map(window, screenSurface, carte, tab_joueur);
                        /*Si c'est la fin du timer ou si un des joueurs est mort ou les deux */
                        nbalive = nbJoueurs;
                        for(i=0;  i<nbJoueurs; i++){
                            if(tab_joueur[i].vie==0){
                                nbalive --;
                            }
                        }
                        if((nbalive==1 && nbJoueurs>1) || nbalive==0 || timer(screenSurface, time_start)){
                            /*Déterminer les gagnants*/
                            for(i=0; i<nbJoueurs; i++){
                                if(tab_joueur[i].vie>0){
                                    tab_joueur[i].gagnant = 1;
                                }
                            }
                            /*afficher le menu de fin avec les joueurs et proposition de quitter / recommencer une partie*/
                            play_again = finjeu(window, screenSurface, tab_joueur, nbJoueurs);
                            quit=!play_again;
                            
                            for(i=0; i<nbJoueurs; i++){
                                tab_joueur[i].vie = 0;
                            }
                        }
                        for(i=0; i<nbPerso; i++){
                            refresh_perso(screenSurface, &tab_joueur[i]);
                        }
                        SDL_UpdateWindowSurface(window);
                    
                    }while(!quit && !play_again); /*Fin de la boucle de Jeu*/
                    /*Quitter la SDL*/
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
    }while(!quit && play_again);
    quitter(window, screenSurface);
    return 0;
}
