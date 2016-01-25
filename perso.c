#include "map.h"
#include "perso.h"


void init_perso(Square **carte, Perso* tab_perso, int nb_perso){
    int i;
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
            tab_perso[i].pos.x = LONGUEUR_MAP-2;
            tab_perso[i].pos.y = 1;
            carte[LONGUEUR_MAP-2][1].idJoueur = 2;

            tab_perso[i].sprite = SDL_LoadBMP("Img/P2.bmp");
            SDL_SetColorKey(tab_perso[i].sprite, 1, SDL_MapRGB(tab_perso[i].sprite->format, 0, 255, 0));
        }else if(i==2){
            tab_perso[i].pos.x = 1;
            tab_perso[i].pos.y = HAUTEUR_MAP-2;
            carte[1][HAUTEUR_MAP-2].idJoueur = 3;

            tab_perso[i].sprite = SDL_LoadBMP("Img/P3.bmp");
            SDL_SetColorKey(tab_perso[i].sprite, 1, SDL_MapRGB(tab_perso[i].sprite->format, 0, 255, 0));
        }else if(i==3){
            tab_perso[i].pos.x = LONGUEUR_MAP-2;
            tab_perso[i].pos.y = HAUTEUR_MAP-2;
            carte[LONGUEUR_MAP-2][HAUTEUR_MAP-2].idJoueur = 4;

            tab_perso[i].sprite = SDL_LoadBMP("Img/P4.bmp");
            SDL_SetColorKey(tab_perso[i].sprite, 1, SDL_MapRGB(tab_perso[i].sprite->format, 0, 255, 0));
        }
        tab_perso[i].frameEnCours = 0;
        tab_perso[i].deplacement = 0;

        tab_perso[i].direction = 0;
        tab_perso[i].vie = 1;
        tab_perso[i].nbBombePos = 0;
        tab_perso[i].nbBombeTot = 1;
        tab_perso[i].vitesse = 1.0;

        tab_perso[i].radius = 1;
        tab_perso[i].effetBonus = 0;
        tab_perso[i].poussee = 0;
    }
}

void deplacer(SDL_Window* window, SDL_Surface* screenSurface, Square** carte, int idJoueur, Perso* tab_joueur, int direction){
    int temps = SDL_GetTicks();

    SDL_Rect pos;
    pos.x = 0;
    pos.y = 0;

    if(tab_joueur[idJoueur].deplacement)
    {
        switch(tab_joueur[idJoueur].direction)
        {
            case(BAS):
                if(tab_joueur[idJoueur].pos.y >= HAUTEUR_MAP-1)
                    break;
                if(carte[tab_joueur[idJoueur].pos.x][tab_joueur[idJoueur].pos.y+1].bloc.type!=0 || carte[tab_joueur[idJoueur].pos.x][tab_joueur[idJoueur].pos.y+1].bombe.radius!=0)
                    break;
                tab_joueur[idJoueur].pos.y++;
                break;
            case(HAUT):
                if(tab_joueur[idJoueur].pos.y <= 0)
                    break;
                if(carte[tab_joueur[idJoueur].pos.x][tab_joueur[idJoueur].pos.y-1].bloc.type!=0 || carte[tab_joueur[idJoueur].pos.x][tab_joueur[idJoueur].pos.y-1].bombe.radius!=0)
                    break;
                tab_joueur[idJoueur].pos.y--;
                break;
            case(GAUCHE):
                if(tab_joueur[idJoueur].pos.x <= 0)
                    break;
                if(carte[tab_joueur[idJoueur].pos.x-1][tab_joueur[idJoueur].pos.y].bloc.type!=0 || carte[tab_joueur[idJoueur].pos.x-1][tab_joueur[idJoueur].pos.y].bombe.radius!=0)
                    break;
                tab_joueur[idJoueur].pos.x--;
            case(DROITE):
                if(tab_joueur[idJoueur].pos.x >= LONGUEUR_MAP-1)
                    break;
                if(carte[tab_joueur[idJoueur].pos.x+1][tab_joueur[idJoueur].pos.y].bloc.type!=0 || carte[tab_joueur[idJoueur].pos.x+1][tab_joueur[idJoueur].pos.y].bombe.radius!=0)
                    break;
                tab_joueur[idJoueur].pos.x++;
        }
    }
    refresh_map(window, screenSurface, carte);
}

void poseBombe(Square** carte, Perso* idJoueur){
    /*Si la case est bien vide*/
    if(carte[idJoueur->pos.x][idJoueur->pos.y].bombe.radius==0){
    /*Si le joueur peut bien poser une bombe*/
        if(idJoueur->nbBombeTot - idJoueur->nbBombePos > 0){
            idJoueur->nbBombePos++;
            carte[idJoueur->pos.x][idJoueur->pos.y].bombe.decompte = 2;
            carte[idJoueur->pos.x][idJoueur->pos.y].bombe.radius = idJoueur->radius;

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
