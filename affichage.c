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
                printf("screensurface, %s\n", SDL_GetError());
                success = 0;
            }else{
                /*Faire un fond ROSE*/
                SDL_FillRect(*screenSurface, NULL, SDL_MapRGB((*screenSurface)->format, 0xFF, 0xAA, 0xAA));
                /*initier TTF*/
                if(TTF_Init()==-1){
                    printf("Pas pu initialiser TTF ! SDL_ttf error : %s\n", TTF_GetError());
                    success = 0;
                }
            }
        }
    }
    return success;
}

void refresh_map(SDL_Window* window, SDL_Surface* screenSurface, Square** carte, Perso* tabJoueur)
{
    int i, j;
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB((screenSurface)->format, 0 , 0, 0));
    SDL_Surface *tile1 = SDL_LoadBMP("Img/1.bmp");
    SDL_Surface *tile2 = SDL_LoadBMP("Img/2.bmp");
    SDL_Surface *tile3 = SDL_LoadBMP("Img/3.bmp");
    SDL_Surface *hard = SDL_LoadBMP("Img/hard.bmp");
    SDL_Surface *airGround = SDL_LoadBMP("Img/air.bmp");
    SDL_Surface *truc = SDL_LoadBMP("Img/ice.bmp");

    SDL_Rect posTile;
    posTile.x = 0;
    posTile.y = 0;

    for(i=0; i<longueur_map+2; ++i)
    {
        posTile.x = i*40;
        for(j=0; j<hauteur_map+2; ++j)
        {
            posTile.y = j*40;
            /*faire la bordure*/
            if(i==0 || j==0 || i == longueur_map+1 || j == hauteur_map+1){
                SDL_BlitSurface(hard, NULL, screenSurface, &posTile);
            }
            else /*les autres cases, celles jouables*/
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
                    animbombe(screenSurface, &(carte[i-1][j-1].bombe), posTile);
                }
            }
        }
    }
    for(i=1; i<longueur_map+1; ++i)
    {
        posTile.x = i*40;
        for(j=1; j<hauteur_map+1; ++j)
        {
            posTile.y = j*40;
                if(carte[i-1][j-1].bombe.aExplose > 0){
                    animexplosion(screenSurface, &(carte[i-1][j-1].bombe), posTile, carte, tabJoueur[carte[i-1][j-1].bombe.proprio].radius);
                }
                if(carte[i-1][j-1].bonus != RIEN && carte[i-1][j-1].bloc.type == 0){
                    affichebonus(screenSurface, carte[i-1][j-1].bonus, &posTile);
                }
        }
    }
    SDL_FreeSurface(tile1);
    SDL_FreeSurface(tile2);
    SDL_FreeSurface(tile3);
    SDL_FreeSurface(hard);
    SDL_FreeSurface(airGround);
    SDL_FreeSurface(truc);
}



void quitter(SDL_Window* window, SDL_Surface* screenSurface){
    SDL_FreeSurface(screenSurface);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void obtenirCheminImage(char* nomFichier){
    sprintf(nomFichier, "Img/%s.bmp", nomFichier);
}

/*Affiche le choix du nb de joueurs, renvoie ce nb de joueurs*/
int inputNbJoueurs(SDL_Window* window, SDL_Surface* screenSurface, int nbPerso){
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
    bouton1 = SDL_LoadBMP("Img/bouton1.bmp");
        
    SDL_Surface* bouton2 = NULL;
    SDL_Rect b2;
    
    if(nbPerso >1){
        b2.x = (longueur_map*TILE_SIZE)/2-20-50;
        b2.y = (hauteur_map*TILE_SIZE)/2-20+50;
        bouton2 = SDL_LoadBMP("Img/bouton2.bmp");
        if(bouton2 == NULL){
            printf("\nBoutons nuls : SDL error = %s\n", SDL_GetError());
        }
        SDL_SetColorKey(bouton2, 1, SDL_MapRGB(bouton2->format, 0, 255, 0));
        SDL_BlitSurface(bouton2, NULL, screenSurface, &b2);
    }
    
    ecriteau = SDL_LoadBMP("Img/ecriteau_joueurs.bmp");
    if(bouton1 ==NULL || ecriteau == NULL){
        printf("\nBoutons nuls : SDL error = %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_SetColorKey(bouton1, 1, SDL_MapRGB(bouton1->format, 0, 255, 0));

    SDL_BlitSurface(bouton1, NULL, screenSurface, &b1);
    SDL_BlitSurface(ecriteau, NULL, screenSurface, &ecr);
    
    SDL_FreeSurface(bouton1);
    SDL_FreeSurface(bouton2);
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
                /*Clic sur bouton 1*/
                if(x>=b1.x && x<=b1.x+b1.w && y>=b1.y && y<=b1.y+b1.h){
                    nbjoueurs = 1;
                }
                 /*Clic sur bouton 2*/
                else if(bouton2 !=NULL && x>=b2.x && x<=b2.x+b2.w && y>=b2.y && y<=b2.y+b2.h){
                    nbjoueurs = 2;
                }
                break;
        }
    }
    return nbjoueurs;
}

/*Affiche le choix du nb de persos jouables, renvoie ce nb*/
int inputNbPersos(SDL_Window* window, SDL_Surface* screenSurface){
    int nbPersos = 0;
    SDL_Event e;
    int x, y;
    
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

    bouton1 = SDL_LoadBMP("Img/bouton1.bmp");
    bouton2 = SDL_LoadBMP("Img/bouton2.bmp");
    bouton3 = SDL_LoadBMP("Img/bouton3.bmp");
    bouton4 = SDL_LoadBMP("Img/bouton4.bmp");
    ecriteau = SDL_LoadBMP("Img/ecriteau_persos.bmp");
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
    while(nbPersos ==0){
        SDL_WaitEvent(&e);
        switch (e.type){
            case SDL_QUIT :
                nbPersos = -1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&x, &y);
                /*Clic sur bouton 1*/
                if(x>=b1.x && x<=b1.x+b1.w && y>=b1.y && y<=b1.y+b1.h){
                    nbPersos = 1;
                }
                 /*Clic sur bouton 2*/
                else if(x>=b2.x && x<=b2.x+b2.w && y>=b2.y && y<=b2.y+b2.h){
                    nbPersos = 2;
                }
                /*Clic sur bouton 3*/
                else if(x>=b3.x && x<=b3.x+b3.w && y>=b3.y && y<=b3.y+b3.h){
                    nbPersos = 3;
                }
                /*Clic sur bouton 4*/
                else if(x>=b4.x && x<=b4.x+b4.w && y>=b4.y && y<=b4.y+b4.h){
                    nbPersos = 4;
                }
                break;
        }
    }
    return nbPersos;
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
                    }
                    /*Clic sur bouton GRAND*/
                    else if(x>bg.x && x<(bg.x+bg.w) && y>bg.y && y<(bg.y+bg.h)){
                        choixTaille = 2;
                    }
                    break;
        }
    }
    return choixTaille;
}

void refresh_perso(SDL_Surface* screenSurface, Perso* joueur){
    SDL_Rect pos;

    if(joueur->vie > 0 && joueur->deplacement){
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
        /*v=d/t, en augmentant le nb de pas au coef de vitesse du joueur, on augmente le découpage de la distance et donc ça va plus vite 
         * donc on peut passer de 40 à 20 pas*/
        joueur->nbpas-=joueur->vitesse; 
        if(joueur->nbpas < 0){ /*S'il a fini de se deplacer*/
            joueur->deplacement = 0;
            joueur->nbpas =0;
        }
    }else if(joueur->vie >0){ /*S'il bouge pas*/
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

/*animation de la bombe jusqu'à ce qu'elle explose*/
void animbombe(SDL_Surface* screenSurface, Bombe *bombe, SDL_Rect pos){
    int i;
    SDL_Surface* sprite = NULL;
    SDL_Rect spriteClip[2];
    
    sprite = SDL_LoadBMP("Img/bombe_explode.bmp");
    if(sprite == NULL){
        printf("\nPas pu load sprite bombe : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
    for(i=0; i<2; i++){
        spriteClip[i].x = i*TILE_SIZE;
        spriteClip[i].y = 0;
        spriteClip[i].w = TILE_SIZE;
        spriteClip[i].h = TILE_SIZE;
    }
    if(bombe->decompte > 0 ) {
        SDL_SetColorKey(sprite, 1, SDL_MapRGB(sprite->format, 0, 255, 0));
        SDL_BlitSurface(sprite, &(spriteClip[((COMPTE_A_REBOURS-(SDL_GetTicks()-bombe->decompte))/500) %2]), screenSurface, &pos);
    }
    SDL_FreeSurface(sprite);
}

/*animation du nuage créé par le souffle de l'explosion*/
void animexplosion(SDL_Surface* screenSurface, Bombe *bombe, SDL_Rect pos, Square** carte, int radius){
    int i;
    SDL_Rect cpy_pos;
    SDL_Surface* sprite = NULL;
    SDL_Rect spriteClip[6];
    
    /*Ces booleens memorisent les obstacles, car l'animation doit s'arreter à leur rencontre*/
    char obstacle_haut = 0;
    char obstacle_bas = 0;
    char obstacle_gauche = 0;
    char obstacle_droite = 0;

    sprite = SDL_LoadBMP("Img/bombe_explode.bmp");
    if(sprite == NULL){
        printf("\nPas pu load sprite explosion bombe : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_SetColorKey(sprite, 1, SDL_MapRGB(sprite->format, 0, 255, 0));
    for(i=0; i<6; i++){
        spriteClip[i].x = (i*TILE_SIZE)+80;
        spriteClip[i].y = 0;
        spriteClip[i].w = TILE_SIZE;
        spriteClip[i].h = TILE_SIZE;
    }
        
        if((SDL_GetTicks()-bombe->aExplose) <= 1200){ /*Si ce n'est pas la fin du tab de sprites d'explosion, on le parcourt*/
            /*case de la bombe*/
            SDL_BlitSurface(sprite, &spriteClip[(((SDL_GetTicks()-bombe->aExplose)/200) %6)], screenSurface, &pos);
            /*CASES AUTOUR DE LEPICENTRE DE LA BOMBE*/
            for(i=1; i<=radius; i++){
                /*cases vers le haut*/ 
                cpy_pos.x = pos.x;
                cpy_pos.y = pos.y - TILE_SIZE * i;
                /*si pas d'obstacle AND pas au bord de la carte AND pas un bloc indestructible ==> pas de nuage*/
                if(!obstacle_haut && (cpy_pos.y>=TILE_SIZE) && carte[(cpy_pos.x/TILE_SIZE-1)][(cpy_pos.y/TILE_SIZE-1)].bloc.type == 0){
                    SDL_BlitSurface(sprite, &(spriteClip[(((SDL_GetTicks()-bombe->aExplose)/200) %6)]), screenSurface, &cpy_pos);
                }
                else {
                    obstacle_haut = 1;
                }
                if(carte[(cpy_pos.x/TILE_SIZE-1)][(cpy_pos.y/TILE_SIZE-1)].bloc.type  > 0) {
                    obstacle_haut = 1;
                }
                cpy_pos.x = pos.x;
                cpy_pos.y = pos.y + TILE_SIZE * i;
                /*cases vers le bas*/
                if(!obstacle_bas && (cpy_pos.y<=hauteur_map*TILE_SIZE) && carte[cpy_pos.x/TILE_SIZE-1][(cpy_pos.y/TILE_SIZE-1)].bloc.type == 0){
                    SDL_BlitSurface(sprite, &(spriteClip[(((SDL_GetTicks()-bombe->aExplose)/200) %6)]), screenSurface, &cpy_pos);
                }else{
                    obstacle_bas = 1;
                }
                cpy_pos.x = pos.x- TILE_SIZE * i;
                cpy_pos.y = pos.y;
                /*cases vers la gauche*/
                if(!obstacle_gauche && (cpy_pos.x>=TILE_SIZE) && carte[cpy_pos.x/TILE_SIZE-1][cpy_pos.y/TILE_SIZE-1].bloc.type == 0){ 
                    SDL_BlitSurface(sprite, &(spriteClip[(((SDL_GetTicks()-bombe->aExplose)/200) %6)]), screenSurface, &cpy_pos);
                }else{
                    obstacle_gauche = 1;
                }
                cpy_pos.x = pos.x + TILE_SIZE * i;
                cpy_pos.y = pos.y;
                /*cases vers la droite*/
                if(!obstacle_droite && (cpy_pos.x <= longueur_map*TILE_SIZE) && carte[cpy_pos.x/TILE_SIZE-1][(cpy_pos.y/TILE_SIZE-1)].bloc.type == 0){
                    SDL_BlitSurface(sprite, &(spriteClip[(((SDL_GetTicks()-bombe->aExplose)/200) %6)]), screenSurface, &cpy_pos);
                }else{
                    obstacle_droite = 1;
                }
                
            }
        }else{ /*Sinon c'est que le nuage est dissipé, on remet la case à -1*/
            bombe->aExplose = -1;
        }
    SDL_FreeSurface(sprite);
    
}

/*affichage du timer, une fois tombé de 120sec à 0, renvoie 1*/
int timer(SDL_Surface* screenSurface, int start){
    int fini = 0;
    int temps = SDL_GetTicks();
    int temps_sec = 0;
    
    SDL_Color textColor = {0, 0, 0};
        
    SDL_Rect posTimer;
    posTimer.x = longueur_map*TILE_SIZE -124;
    posTimer.y = 1;
    posTimer.w = 80;
    posTimer.h = TILE_SIZE-2;
    
    SDL_Surface *fond_timer = SDL_CreateRGBSurface(0, posTimer.w, posTimer.h, 32, 0, 0, 0, 0);
    SDL_FillRect(fond_timer, NULL, SDL_MapRGB(screenSurface->format, 0xB5, 0xDB, 0xDA));
    
    SDL_Rect postext;
    postext.x = posTimer.x+ posTimer.w/2 - 10;
    postext.y = 0;
    
    
    TTF_Font *font = NULL;
    font = TTF_OpenFont("CloisterBlack.ttf", 36);
    if(font == NULL){
        printf("Pas pu load la police d ecriture ! erreur : %s", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    char chaine[4];
    SDL_Surface *textSurface = NULL;
    temps_sec = (temps - start)/1000;
    
    int duree = 120;
    if(duree-temps_sec > -1 && temps_sec<duree*1000){
        sprintf(chaine, "%d", duree-temps_sec);
        textSurface = TTF_RenderText_Solid(font, chaine, textColor);
        if(textSurface == NULL){
            printf("Pas pu load la textSurface ! Erreur : %s", TTF_GetError());
            exit(EXIT_FAILURE);
        }
        
        SDL_BlitSurface(fond_timer, NULL, screenSurface, &posTimer);
        SDL_BlitSurface(textSurface, NULL, screenSurface, &postext);
    }else{
        fini = 1;
    }
    
    SDL_FreeSurface(textSurface);
    SDL_FreeSurface(fond_timer);
    TTF_CloseFont(font);
    
    return fini;
}

/*menu de fin de jeu :
 * affiche le / les / aucun gagnant(s)
 * recommencer une partie
 * quitter*/
int finjeu(SDL_Window* window, SDL_Surface* screenSurface, Perso* tab_joueurs, int nbjoueurs){
    int i;
    int cpt_gagnants=0;
    
    SDL_Color textColor = {0, 0, 0};
    TTF_Font *font = NULL;
    font = TTF_OpenFont("CloisterBlack.ttf", 36);
    
    /*
     * 
     *  AFFICHER LE GAGNANT OU L EGALITE OU LA DEFAITE
     * 
     * 
      */
     
    /*surface où afficher les scores, avec une jolie ptite bordure*/
    SDL_Rect posCadre;
    posCadre.w = 504;
    posCadre.h = 104;
    posCadre.x = (screenSurface->w/2)-(posCadre.w/2);
    posCadre.y = (screenSurface->h/2)-(posCadre.h/2);
    
    SDL_Surface *cadre = SDL_CreateRGBSurface(0, posCadre.w, posCadre.h, 32, 0, 0, 0, 0);
    SDL_FillRect(cadre, NULL, SDL_MapRGB(screenSurface->format, 0x1E, 0x10, 0x05));
    
    SDL_Rect posEncadre;
    posEncadre.w = 500;
    posEncadre.h = 100;
    posEncadre.x = (screenSurface->w/2)-(posEncadre.w/2);
    posEncadre.y = (screenSurface->h/2)-(posEncadre.h/2);

    SDL_Surface *encadre = SDL_CreateRGBSurface(0, posEncadre.w, posEncadre.h, 32, 0, 0, 0, 0);
    SDL_FillRect(encadre, NULL, SDL_MapRGB(screenSurface->format, 0xA0, 0x68, 0x3A));
     if(encadre == NULL) {
        fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
        exit(1);
    }
    
    SDL_Rect postext;
    postext.x = posEncadre.x + 40;
    postext.y = posEncadre.y + 40;
    postext.h = 40;
    postext.w = posEncadre.w;
    
    SDL_Surface *textSurface = NULL;
    
    char chaine[50];
    for(i=0; i<nbjoueurs; i++){
        if(tab_joueurs[i].gagnant==1){
            cpt_gagnants++;
        }
    }
    /*Aucun gagnant*/
    if(cpt_gagnants==0){
        sprintf(chaine, "Defaite totale !\n");
    }/*Egalité*/
    else if(cpt_gagnants == nbjoueurs && nbjoueurs>1){
        sprintf(chaine, "Egalite");
        postext.x = screenSurface->w / 2 - 40;
    }else{
        for(i=0; i<nbjoueurs; i++){
            if(tab_joueurs[i].gagnant==1){
                sprintf(chaine, "Le joueur %d remporte la victoire !\n", i+1);
            }
        }
    }
    
    textSurface = TTF_RenderText_Solid(font, chaine, textColor);
    if(textSurface == NULL){
        printf("Pas pu load la textSurface ! Erreur : %s", TTF_GetError());
        exit(EXIT_FAILURE);
    }
            
    postext.y = posEncadre.y + 40;
    SDL_BlitSurface(cadre, NULL, screenSurface, &posCadre);
    SDL_BlitSurface(encadre, NULL, screenSurface, &posEncadre);
    SDL_BlitSurface(textSurface, NULL, screenSurface, &postext);

    /*
     * 
     *  AFFICHER LES BOUTONS QUITTER OU RECOMMENCER
     * 
     * 
      */

    SDL_Surface *textQuit = NULL;

    SDL_Rect posQuit;
    posQuit.h = 60;
    posQuit.w = 100;
    posQuit.x = longueur_map*TILE_SIZE/2 - posQuit.w/2-40;
    posQuit.y = hauteur_map*TILE_SIZE -posQuit.h - 40;
    
    SDL_Surface *boutonQuit = SDL_CreateRGBSurface(0, posQuit.w, posQuit.h, 32, 0, 0, 0, 0);
    SDL_FillRect(boutonQuit, NULL, SDL_MapRGB(screenSurface->format, 0xA0, 0x68, 0x3A));
    
    textQuit = TTF_RenderText_Solid(font, "Quitter", textColor);
    if(textQuit == NULL){
        printf("Pas pu load la textSurface ! Erreur : %s", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    
    SDL_BlitSurface(boutonQuit, NULL, screenSurface, &posQuit);
    SDL_BlitSurface(textQuit, NULL, screenSurface, &posQuit);
    
    SDL_Surface *textRejouer = NULL;
    
    SDL_Rect posRejouer;
    posRejouer.h = 60;
    posRejouer.w = 100;
    posRejouer.x = longueur_map*TILE_SIZE/2 + 40;
    posRejouer.y = hauteur_map*TILE_SIZE - posRejouer.h - 40;
    
    SDL_Surface *boutonRejouer = SDL_CreateRGBSurface(0, posRejouer.w, posRejouer.h, 32, 0, 0, 0, 0);
    SDL_FillRect(boutonRejouer, NULL, SDL_MapRGB(screenSurface->format, 0xA0, 0x68, 0x3A));
    
    textRejouer = TTF_RenderText_Solid(font, "Rejouer", textColor);
    if(textRejouer == NULL){
        printf("Pas pu load la textSurface ! Erreur : %s", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    
    SDL_BlitSurface(boutonRejouer, NULL, screenSurface, &posRejouer);
    SDL_BlitSurface(textRejouer, NULL, screenSurface, &posRejouer);
    
    SDL_FreeSurface(cadre);
    SDL_FreeSurface(encadre);
    SDL_FreeSurface(textSurface);
    SDL_FreeSurface(textQuit);
    SDL_FreeSurface(textRejouer);
    SDL_FreeSurface(boutonQuit);
    SDL_FreeSurface(boutonRejouer);
    TTF_CloseFont(font);
    
    SDL_UpdateWindowSurface(window);
    /*Clic sur le bouton*/
    SDL_Event event;
    int x, y;
    while(1){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT :
                exit(EXIT_SUCCESS);
                break;
            case SDL_MOUSEBUTTONDOWN :
                SDL_GetMouseState(&x, &y);
                /*Clic sur QUITTER*/
                if(x>=posQuit.x && x<=posQuit.x+posQuit.w && y>=posQuit.y && y<=posQuit.y+posQuit.h){
                    printf("quitter\n");
                    return 0;
                }
                /*Clic sur REJOUER*/
                if(x>=posRejouer.x && x<=posRejouer.x+posRejouer.w && y>=posRejouer.y && y<=posRejouer.y+posRejouer.h){
                    printf("rejouer\n");
                    return 1;
                }
                break;
        }
    }
}

void affichebonus(SDL_Surface* screenSurface, short int bonus, SDL_Rect *pos){
   
   SDL_Surface* surfBonus = NULL;
   
   switch(bonus){
        case FEU:
            surfBonus = SDL_LoadBMP("Img/fire.bmp");
            break;
        case GLACE: 
            surfBonus = SDL_LoadBMP("Img/ice.bmp");
            break;
        case MINE: 
            surfBonus= SDL_LoadBMP("Img/bomb2.bmp");
            break;
       case PRADIUS: 
            surfBonus = SDL_LoadBMP("Img/radiusPlus.bmp");
            break;
        case MRADIUS: 
            surfBonus = SDL_LoadBMP("Img/radiusMoins.bmp");
            break;
        case PVITESSE: 
            surfBonus = SDL_LoadBMP("Img/vitessePlus.bmp");
            break;
        case MVITESSE: 
            surfBonus = SDL_LoadBMP("Img/vitesseMoins.bmp");
            break;
        case PBOMBE: 
            surfBonus = SDL_LoadBMP("Img/bomb2.bmp");
            break;
        case MBOMBE: 
            surfBonus = SDL_LoadBMP("Img/bomb2.bmp");
            break;
        case PVIE: 
            surfBonus = SDL_LoadBMP("Img/viePlus.bmp");
            break;
        case POUSSEE: 
            surfBonus = SDL_LoadBMP("Img/bomb2.bmp");
            break;
            default : 
                printf("\n\nNO BONUS AVAILABLE HERE\n\n");
            break;
   }
    if(surfBonus==NULL){
        printf("Pas pu load img bonus %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_SetColorKey(surfBonus, 1, SDL_MapRGB(surfBonus->format, 0, 255, 0));
    SDL_BlitSurface(surfBonus, NULL, screenSurface, pos);
    SDL_FreeSurface(surfBonus);
    
}

