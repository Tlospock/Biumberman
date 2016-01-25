#ifndef _PERSO_H
#define _PERSO_H

#include "map.h"




/* Numero d'identification des effets bonus qui ne modifient pas les caracs
 * 0 Rien
 * 1 Feu
 * 2 Glace
 * 3 Mine
 */

void init_perso(Square **carte, Perso* tab_perso, int nb_perso);

void deplacer(int idJoueur, Position arrivee, Position depart);

void poseBombe(Square** carte, Perso* idJoueur);

void exploser(Square** carte, int posBombeX, int posBombeY);
#endif /* _PERSO_H*/
