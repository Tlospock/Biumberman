#include "map.h"
#include "perso.h"

void init_perso(Square **carte, Perso* tab_perso, int nb_perso){
    int i,j;
    for(i=0; i<nb_perso; i++)
    {
        tab_perso[i].id = i+1;
        if(i==0){
            tab_perso[i].pos.x = 1;
            tab_perso[i].pos.y = 1;
            carte[1][1].idJoueur = 1;

            tab_perso[i].sprite = SDL_LoadBMP("Img/P1.bmp");
            SDL_SetColorKey(tab_perso[i].sprite, 1, SDL_MapRGB(tab_perso[i].sprite->format, 0, 255, 0));
        }else if(i==1){
            tab_perso[i].pos.x = longueur_map-2;
            tab_perso[i].pos.y = 1;
            carte[longueur_map-2][1].idJoueur = 2;

            tab_perso[i].sprite = SDL_LoadBMP("Img/P2.bmp");
            SDL_SetColorKey(tab_perso[i].sprite, 1, SDL_MapRGB(tab_perso[i].sprite->format, 0, 255, 0));
        }else if(i==2){
            tab_perso[i].pos.x = 1;
            tab_perso[i].pos.y = hauteur_map-2;
            carte[1][hauteur_map-2].idJoueur = 3;

            tab_perso[i].sprite = SDL_LoadBMP("Img/P3.bmp");
            SDL_SetColorKey(tab_perso[i].sprite, 1, SDL_MapRGB(tab_perso[i].sprite->format, 0, 255, 0));
        }else if(i==3){
            tab_perso[i].pos.x = longueur_map-2;
            tab_perso[i].pos.y = hauteur_map-2;
            carte[longueur_map-2][hauteur_map-2].idJoueur = 4;

            tab_perso[i].sprite = SDL_LoadBMP("Img/P4.bmp");
            SDL_SetColorKey(tab_perso[i].sprite, 1, SDL_MapRGB(tab_perso[i].sprite->format, 0, 255, 0));
        }
        tab_perso[i].nbpas = 0;
        tab_perso[i].deplacement = 0;

        tab_perso[i].direction = BAS;
        tab_perso[i].vie = 1;
        tab_perso[i].nbBombePos = 0;
        tab_perso[i].nbBombeTot = 1;
        tab_perso[i].vitesse = 1.0;

        tab_perso[i].radius = 1;
        tab_perso[i].effetBonus = 0;
        tab_perso[i].poussee = 0;

        for(j=0; j< 12; j++){
            tab_perso[i].spriteClip[j].x = j*TILE_SIZE;
            tab_perso[i].spriteClip[j].y = 0;
            tab_perso[i].spriteClip[j].w = TILE_SIZE;
            tab_perso[i].spriteClip[j].h = TILE_SIZE;
        }
    }
}

/*renvoie 1 si déplacement possible, sinon 0
 * Si possible alors déplace.*/
int deplacer(Square** carte, Perso* joueur){
    if(joueur->vie > 0 && joueur->nbpas ==0) {
        switch(joueur->direction)
        {
            case(BAS):
                if(joueur->pos.y >= hauteur_map-1)
                    break;
                if(carte[joueur->pos.x][joueur->pos.y+1].bloc.type!=0 || carte[joueur->pos.x][joueur->pos.y+1].bombe.radius!=0)
                    break;
                carte[joueur->pos.x][joueur->pos.y].idJoueur = -1;
                joueur->pos.y++;
                carte[joueur->pos.x][joueur->pos.y].idJoueur = joueur->id;
                joueur->nbpas = 39;
                return 1;
                break;
            case(HAUT):
                if(joueur->pos.y <= 0)
                    break;
                if(carte[joueur->pos.x][joueur->pos.y-1].bloc.type!=0 || carte[joueur->pos.x][joueur->pos.y-1].bombe.radius!=0)
                    break;
                carte[joueur->pos.x][joueur->pos.y].idJoueur = -1;
                joueur->pos.y--;
                carte[joueur->pos.x][joueur->pos.y].idJoueur = joueur->id;
                joueur->nbpas = 39;
                return 1;
                break;
            case(GAUCHE):
                if(joueur->pos.x <= 0)
                    break;
                if(carte[joueur->pos.x-1][joueur->pos.y].bloc.type!=0 || carte[joueur->pos.x-1][joueur->pos.y].bombe.radius!=0)
                    break;
                carte[joueur->pos.x][joueur->pos.y].idJoueur = -1;
                joueur->pos.x--;
                carte[joueur->pos.x][joueur->pos.y].idJoueur = joueur->id;
                joueur->nbpas = 39;
                return 1;
                break;
            case(DROITE):
                if(joueur->pos.x >= longueur_map-1)
                    break;
                if(carte[joueur->pos.x+1][joueur->pos.y].bloc.type!=0 || carte[joueur->pos.x+1][joueur->pos.y].bombe.radius!=0)
                    break;
                carte[joueur->pos.x][joueur->pos.y].idJoueur = -1;
                joueur->pos.x++;
                carte[joueur->pos.x][joueur->pos.y].idJoueur = joueur->id;
                joueur->nbpas = 39;
                return 1;
                break;
        }
    /*deplacement a pas pu se faire car obstacle*/
    return 0;
    }
    else {
        /*s'il lui reste des pas à faire, on le laisse finir (animation)*/
        return 1;
    }
}

void poseBombe(Square** carte, Perso* joueur, SDL_Window* window, SDL_Surface* screenSurface){

    int i=0, j=1;
    /*Si la case est bien vide*/
    if(carte[joueur->pos.x][joueur->pos.y].bombe.radius==0){
    /*Si le joueur peut bien poser une bombe*/
    
        if(joueur->nbBombeTot - joueur->nbBombePos > 0){
            joueur->nbBombePos++;
            carte[joueur->pos.x][joueur->pos.y].bombe.decompte = SDL_GetTicks();
            carte[joueur->pos.x][joueur->pos.y].bombe.radius = joueur->radius;  /*Définition du raadius de la bombe*/
            carte[joueur->pos.x][joueur->pos.y].bombe.proprio = joueur->id-1;                   /*Propriétaire de la bombe*/
            carte[joueur->pos.x][joueur->pos.y].danger=1;

            /*On met à jour le danger dans les cases concerné par le radius*/
            int posX = joueur->pos.x;
            int posY = joueur->pos.y;
            while(i<4)
            {

                while(j<joueur->radius+1)
                {
                    switch(i)
                    {
                        case 0:                                                                     /*On regarde vers le haut*/
                            if(posY-j <0 || carte[posX][posY-j].bloc.type != 0)
                                j=joueur->radius;
                            else
                                carte[posX][posY-j].danger=1;
                            break;
                        case 1:
                            if(posY+j >hauteur_map-1 || carte[posX][posY+j].bloc.type != 0)
                                j=joueur->radius;
                            else
                                carte[posX][posY-j].danger=1;
                            break;
                        case 2:
                            if(posX-j <0 || carte[posX-j][posY].bloc.type != 0)
                                j=joueur->radius;
                            else
                                carte[posX][posY-j].danger=1;
                            break;
                        default:
                            if(posX+j <longueur_map-1 || carte[posX+j][posY].bloc.type != 0)
                                j=joueur->radius;
                            else
                                carte[posX][posY-j].danger=1;
                            break;
                    }
                    ++j;
                }
                j=1;
                ++i;
            }
            /*Animation de pose de bombe*/
        }else{
        /*PEUT PAS POSER LA BOMBEEEEEE!!!!!!!*/
        }
    }
}


void mourir(Square** carte, Perso* joueur)
{
    joueur->vie--;
    printf("\nblblblblblb\n");
    if(!joueur->vie){     
        printf("\n%d",joueur->id);
        carte[joueur->pos.x][joueur->pos.y].idJoueur=-1;
    }
}

void check_bomb(Square** carte, Perso* tab_joueur)
{
    int i, j;

    for(i=0; i<longueur_map; ++i)
    {
        for(j=0; j<hauteur_map; ++j)
        {
            if(carte[i][j].bombe.radius !=0 && SDL_GetTicks()-carte[i][j].bombe.decompte>=2000)
            {
                printf("Time start decompte %d,  Decompte à l'explosion %d\n", carte[i][j].bombe.decompte, SDL_GetTicks());
                carte[i][j].bombe.decompte = 0;
                exploser(carte, i, j, tab_joueur);
            }
        }
    }
}

void exploser(Square** carte, int posBombeX, int posBombeY, Perso* tab_joueur){
    /*h : horizontalement / v : verticalement*/
    int i=0, j=1;

    while(i<4)
    {
        while(j<carte[posBombeX][posBombeY].bombe.radius+1)
        {
            switch(i)
            {
                case HAUT:
                    if(posBombeY-j <0 || carte[posBombeX][posBombeY-j].bloc.type < 0) /*si bloc indestructible ou outmap*/
                        j=carte[posBombeX][posBombeY].bombe.radius+1;
                    else
                    {
                        if(carte[posBombeX][posBombeY-j].bombe.radius!=0 && carte[posBombeX][posBombeY-j].bombe.decompte==0)
                            exploser(carte, posBombeX, posBombeY-j, tab_joueur);
                        else
                        {
                            if(carte[posBombeX][posBombeY-j].bloc.type>0)
                            {
                                detruire_bloc(carte, posBombeX, posBombeY-j);
                                j=carte[posBombeX][posBombeY].bombe.radius+1;
                            }
                            else if(carte[posBombeX][posBombeY-j].idJoueur>0)
                            {
                                    printf("HAUT \n");
                                    mourir(carte, &tab_joueur[carte[posBombeX][posBombeY-j].idJoueur-1]);
                            }
                            carte[posBombeX][posBombeY-j].danger=0;
                        }
                        
                    }
                    break;
                case BAS:
                    if(posBombeY+j >hauteur_map-1 || carte[posBombeX][posBombeY+j].bloc.type < 0)
                        j=carte[posBombeX][posBombeY].bombe.radius+1;
                    else
                    {
                        if(carte[posBombeX][posBombeY+j].bombe.radius!=0 && carte[posBombeX][posBombeY+j].bombe.decompte==0)
                            exploser(carte, posBombeX, posBombeY+j, tab_joueur);
                        else
                        {
                            if(carte[posBombeX][posBombeY+j].bloc.type>0)
                            {
                                detruire_bloc(carte, posBombeX, posBombeY+j);
                                j=carte[posBombeX][posBombeY].bombe.radius+1;
                            }
                            else if(carte[posBombeX][posBombeY+j].idJoueur>0)
                             {
                                    printf("BAS\n");
                                    mourir(carte, &tab_joueur[carte[posBombeX][posBombeY+j].idJoueur-1]);
                            }
                            carte[posBombeX][posBombeY+j].danger=0;
                        }
                        
                    }
                    break;
                case GAUCHE:
                    if(posBombeX-j <0 || carte[posBombeX-j][posBombeY].bloc.type < 0)
                        j=carte[posBombeX][posBombeY].bombe.radius+1;
                    else
                    {
                        if(carte[posBombeX-j][posBombeY].bombe.radius!=0 && carte[posBombeX-j][posBombeY].bombe.decompte==0)
                        {
                            exploser(carte, posBombeX, posBombeY-j, tab_joueur);
                            j=carte[posBombeX][posBombeY].bombe.radius+1;
                        }
                        else
                        {
                            if(carte[posBombeX-j][posBombeY].bloc.type>0)
                                detruire_bloc(carte, posBombeX-j, posBombeY);
                            else if(carte[posBombeX-j][posBombeY].idJoueur>0)
                            {
                                    printf("GAUCHE\n");
                                    mourir(carte, &tab_joueur[carte[posBombeX-j][posBombeY].idJoueur-1]);
                            }
                            carte[posBombeX-j][posBombeY].danger=0;
                        }
                        
                    }
                    break;
                case DROITE:
                    if(posBombeX+j >longueur_map-1 || carte[posBombeX+j][posBombeY].bloc.type < 0)
                        j=carte[posBombeX][posBombeY].bombe.radius+1;
                    else
                    {
                        if(carte[posBombeX+j][posBombeY].bombe.radius!=0 && carte[posBombeX+j][posBombeY].bombe.decompte==0)
                            exploser(carte, posBombeX+j, posBombeY, tab_joueur);
                        else
                        {
                            if(carte[posBombeX+j][posBombeY].bloc.type>0)
                            {
                                detruire_bloc(carte, posBombeX+j, posBombeY);
                                j=carte[posBombeX][posBombeY].bombe.radius+1;
                            }
                            else if(carte[posBombeX][posBombeY+j].idJoueur>0)
                            {
                                    printf("DROITE \n");
                                    mourir(carte, &tab_joueur[carte[posBombeX+j][posBombeY].idJoueur-1]);
                            }carte[posBombeX+j][posBombeY].danger=0;
                        }
                    }
                    break;
            }
            ++j;
        }
        j=1;
        ++i;
    }

        /*Ne pas oublier d'afficher l'origine de l'explosion*/

    if(carte[posBombeX][posBombeY].bloc.type>0)
        detruire_bloc(carte, posBombeX, posBombeY);
    else if(carte[posBombeX][posBombeY].idJoueur>0)
        mourir(carte, &tab_joueur[carte[posBombeX][posBombeY].idJoueur-1]);
    carte[posBombeX][posBombeY].danger=0;
    /*Mise à jour des infos de la carte liées à la bombe*/
    carte[posBombeX][posBombeY].bombe.radius = 0;
    carte[posBombeX][posBombeY].bombe.decompte = -1;
    
    /*Mise à jour des infos du perso liées à la bombe*/
    tab_joueur[carte[posBombeX][posBombeY].bombe.proprio].nbBombePos--;
    carte[posBombeX][posBombeY].bombe.proprio=-1;

}
    /*refresh la map*/
