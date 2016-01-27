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
            tab_perso[i].spriteClip[j].y = i*TILE_SIZE;
            tab_perso[i].spriteClip[j].w = TILE_SIZE;
            tab_perso[i].spriteClip[j].h = TILE_SIZE;
        }
    }
}

/*renvoie 1 si déplacement possible, sinon 0
 * Si possible alors déplace.*/
int deplacer(Square** carte, Perso* joueur){
    if(joueur->nbpas ==0) {
        switch(joueur->direction)
        {
            case(BAS):
                if(joueur->pos.y >= hauteur_map-1)
                    break;
                if(carte[joueur->pos.x][joueur->pos.y+1].bloc.type!=0 || carte[joueur->pos.x][joueur->pos.y+1].bombe.radius!=0)
                    break;
                joueur->pos.y++;
                joueur->nbpas = 39;
                return 1;
                break;
            case(HAUT):
                if(joueur->pos.y <= 0)
                    break;
                if(carte[joueur->pos.x][joueur->pos.y-1].bloc.type!=0 || carte[joueur->pos.x][joueur->pos.y-1].bombe.radius!=0)
                    break;
                joueur->pos.y--;
                joueur->nbpas = 39;
                return 1;
                break;
            case(GAUCHE):
                if(joueur->pos.x <= 0)
                    break;
                if(carte[joueur->pos.x-1][joueur->pos.y].bloc.type!=0 || carte[joueur->pos.x-1][joueur->pos.y].bombe.radius!=0)
                    break;
                joueur->pos.x--;
                joueur->nbpas = 39;
                return 1;
                break;
            case(DROITE):
                if(joueur->pos.x >= longueur_map-1)
                    break;
                if(carte[joueur->pos.x+1][joueur->pos.y].bloc.type!=0 || carte[joueur->pos.x+1][joueur->pos.y].bombe.radius!=0)
                    break;
                joueur->pos.x++;
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

void poseBombe(Square** carte, Perso* tab_perso, int idJoueur, SDL_Window* window, SDL_Surface* screenSurface){

    int i=0, j=1;


    /*Si la case est bien vide*/
    if(carte[tab_perso[idJoueur].pos.x][tab_perso[idJoueur].pos.y].bombe.radius==0){
    /*Si le joueur peut bien poser une bombe*/
        if(tab_perso[idJoueur].nbBombeTot - tab_perso[idJoueur].nbBombePos > 0){
            tab_perso[idJoueur].nbBombePos++;
            carte[tab_perso[idJoueur].pos.x][tab_perso[idJoueur].pos.y].bombe.decompte = SDL_GetTicks();
            carte[tab_perso[idJoueur].pos.x][tab_perso[idJoueur].pos.y].bombe.radius = tab_perso[idJoueur].radius;


            /*On met à jour le danger dans les cases concerné par le radius*/
            int posX = tab_perso[idJoueur].pos.x;
            int posY = tab_perso[idJoueur].pos.y;
            while(i<4)
            {
                while(j<tab_perso[idJoueur].radius)
                {
                    switch(i)
                    {
                        case 0:
                            if(posY >0 && carte[posX][posY-j].bloc.type != 0)
                                j=tab_perso[idJoueur].radius;
                            else
                                carte[posX][posY-j].danger=1;

                            break;
                        case 1:
                            if(posY <hauteur_map-1 && carte[posX][posY+j].bloc.type != 0)
                                j=tab_perso[idJoueur].radius;
                            else
                                carte[posX][posY-j].danger=1;
                            break;
                        case 2:
                            if(posX >0 && carte[posX-j][posY].bloc.type != 0)
                                j=tab_perso[idJoueur].radius;
                            else
                                carte[posX][posY-j].danger=1;
                            break;
                        default:
                            if(posX <longueur_map-1 && carte[posX+j][posY].bloc.type != 0)
                                j=tab_perso[idJoueur].radius;
                            else
                                carte[posX][posY-j].danger=1;
                            break;
                    }
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

void mourir(Square** carte, int idJoueur)
{

}

void exploser(Square** carte, int posBombeX, int posBombeY){
/*h : horizontalement / v : verticalement*/
    int cpt=0, h=0, v=0;
    while(h<=carte[posBombeX][posBombeY].bombe.radius){
        while(cpt < 4 && v!=0)
        {
            if(carte[posBombeX+v][posBombeY+h].bombe.radius!=0 && carte[posBombeX+v][posBombeY+h].bombe.decompte==0)
                exploser(carte, posBombeX+h, posBombeY+v);
            else
            {
                if(carte[posBombeX+v][posBombeY+h].bloc.type>0)
                    detruire_bloc(carte, posBombeX+v, posBombeY+h);
                else if(carte[posBombeX+v][posBombeY+h].idJoueur!=0)
                    mourir(carte, carte[posBombeX+v][posBombeY+h].idJoueur);
            }

            /*Utiliser ce switch pour l'affichage des différents sprites d'explosion*/

            switch(cpt)
            {
                case 0:
                    h=-abs(h);
                    ++v;
                    break;
                case 1:
                    v=-abs(v);
                    break;
                case 2:
                    h=abs(h);
                    break;
                case 3:
                    v=abs(v);
                    break;
                default:
                    printf("Erreur! Depassement\n\n\b");
                    break;
            }
            cpt++;
        }

        /*Ne pas oublier d'afficher l'origine de l'explosion*/

        if(v==0)
        {
            if(carte[posBombeX+v][posBombeY+h].bloc.type>0)
                    detruire_bloc(carte, posBombeX+v, posBombeY+h);
            else if(carte[posBombeX+v][posBombeY+h].idJoueur!=0)
                    mourir(carte, carte[posBombeX+v][posBombeY+h].idJoueur);
        }

        cpt=0;
        ++h;
        ++v;
    }
    /*refresh la map*/
}
