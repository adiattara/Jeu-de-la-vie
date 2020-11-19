/**
*@file jeu.h 
*@author Amadou Diattara
*contient la signature des fonctions nécessaires pour jouer 
*/

#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

// modulo modifié pour traiter correctement les bords i=0 et j=0
//dans le calcul des voisins avec bords cycliques
/**
*@fn static inline int modulo(int i, int m)
*modulo modifié pour traiter correctement les bords i=0 et j=0
*dans le calcul des voisins avec bords cycliques
*@param 1 \c int i 
*@param 2 \c int j
 */
static inline int modulo(int i, int m) {return (i+m)%m;}
/**
*compte le nombre de voisins vivants de la cellule (i,j)
* les bords sont cycliques.
**/
int compte_voisins_vivants_cyclique(int i, int j, grille g); // compte voisin vivant de maniére cyclique 

/**
*compte le nombre de voisins vivants de la cellule (i,j)
* les bords sont  non cycliques.
**/
int compte_voisins_vivants_non_cyclique (int i, int j, grille g);// done by me 

/**
*fait évoluer la grille g d'un pas de temps
* sans vieillissement 
**/
void evolue_sans_vieillissement (grille *g, grille *gc ,int (*compte_voisins_vivants)(int,int,grille));

/**
*fait évoluer la grille g d'un pas de temps
* avec  vieillissement 
**/
void evolue_avec_vieillissement (grille *g, grille *gc, int (*compte_voisins_vivants)(int,int,grille));
#endif
