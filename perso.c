#include "map.h"
#include "perso.h"


void init_perso(Square **carte, Perso* tab_perso, int nb_perso){
    int i;
    for(i=0; i<nb_perso; i++){
        tab_perso[i].id = i+1;
        if(i==1){
            tab_perso[i].pos.x = 1;
            tab_perso[i].pos.y = 1;
            carte[1][1].idJoueur = 1;
        }else if(i==2){
            tab_perso[i].pos.x = LONGUEUR_MAP-1;
            tab_perso[i].pos.y = 1;
            carte[LONGUEUR_MAP-1][1].idJoueur = 2;
        }else if(i==3){
            tab_perso[i].pos.x = 1;
            tab_perso[i].pos.y = HAUTEUR_MAP-1;
            carte[1][HAUTEUR_MAP-1].idJoueur = 3;
        }else if(i==4){
            tab_perso[i].pos.x = LONGUEUR_MAP-1;
            tab_perso[i].pos.y = HAUTEUR_MAP-1;
            carte[LONGUEUR_MAP-1][HAUTEUR_MAP-1].idJoueur = 4;
        }

        tab_perso[i].vie = 1;
        tab_perso[i].nbBombePos = 0;
        tab_perso[i].nbBombeTot = 1;
        tab_perso[i].vitesse = 1;

        tab_perso[i].radius = 1;
        tab_perso[i].effetBonus = 0;
        tab_perso[i].poussee = 0;
    }
}
/* init_perso : manque à init le sprite*/

void deplacer(int idJoueur){

}

void poseBombe(Square** carte, Perso* idJoueur){
    /*Si la case est bien vide*/
    if(carte[idJoueur->pos.x][idJoueur->pos.y].bombe.radius==0){
    /*Si le joueur peut bien poser une bombe*/
        if(idJoueur->nbBombeTot - idJoueur->nbBombePos > 0){
        idJoueur->nbBombePos++;
        carte[idJoueur->pos.x][idJoueur->pos.y].bombe.decompte = 2;
        carte[idJoueur->pos.x][idJoueur->pos.y].bombe.radius = idJoueur->radius;
        }else{
        /*PEUT PAS POSER LA BOMBEEEEEE!!!!!!!*/
        }
    }
}

void exploser(Square** carte, int posBombeX, int posBombeY){
/*h : horizontalement / v : verticalement*/
    int cpt=1, h=0, v=0;
    while(cpt<5){
        while(h < carte[posBombeX][posBombeY].bombe.radius+1 && v < carte[posBombeX][posBombeY].bombe.radius+1){
            if(carte[posBombeX][posBombeY].bombe.decompte!=0){
                exploser(carte, posBombeX+h, posBombeY+v);
            }else{

            }
        }
    }
}
