/**
*@file jeu.c 
* contient l'implémentation et signature des fonctions  nécessaires pour jouer 
*/

#include "jeu.h"

/**
*@fn int compte_voisins_vivants_cyclique (int i, int j, grille g)
*calcule le nombre de voisin en considérant que les bords de la  la grille ne sonts  pas cycliques
*@param 1 \c int i 
*@param 2 \c int j 
*@param 2 \c griile g 
*@return le nombre cellules voisins vivantes  dans le cas où les bords de la  la grille ne sonts  pas cycliques
*/

int compte_voisins_vivants_cyclique(int i, int j, grille g){ // modification du compte_voisins_vivant en compte_voisins_vivant_cyclique 
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v; 
/**
 * @fn  \c int compte_voisins_vivants_non_cyclique (int i, int j, grille g)
 * calcule le nombre de voisin en considérant que les bords de  la grille ne sont  pas cycliques 
 * @param 1 \c int i 
 * @param 2 \c int j 
 * @param 3 \c grille g
 * @return  le nombre voisin d'une case dans le cas où  les bords de  la grille ne sont  pas cycliques 
 
 */
}
int compte_voisins_vivants_non_cyclique (int i, int j, grille g){// implémentaion de compte_voisins_vivants_non_cyclique 
int v = 0, l=g.nbl, c = g.nbc;

v+= (i-1 >= 0 && j-1 >= 0) ? est_vivante(i-1,j-1,g) : 0;
v+= (i-1 >= 0) ? est_vivante(i-1,j,g) : 0;
v+= (i-1 >= 0 && j+1 < c) ? est_vivante(i-1,j+1,g) : 0;
v+= (j-1 >= 0) ? est_vivante(i,j-1,g) : 0;
v+= (j+1 < c) ? est_vivante(i,j+1,g) : 0;
v+= (i+1 < l && j-1 >= 0) ? est_vivante(i+1,j-1,g) : 0;
v+= (i+1 < l) ? est_vivante(i+1,j,g) : 0;
v+= (i+1 < l && j+1 < c) ? est_vivante(i+1,j+1,g) : 0;

return v;
}


/** 
*@fn void evolue_sans_vieillissement(grille *g, grille *gc)
*fait évoluer la grille  sans tenir compte du vieillisement des cellules
*@param 1 \c grille *g 
*@param 2 \c grille *gc 
*@return rien 
*/

void evolue_sans_vieillissement (grille *g, grille *gc ,int (*cyclique_ou_non)(int,int,grille)){
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			v = (*cyclique_ou_non) (i, j, *gc); // valeur de retour de la fonction et non l'adresse de la de la fonction il pointe

			if (est_vivante(i,j,*g)) 
			{ // evolution d'une cellule vivante
				if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
			}
			else 
			{ // evolution d'une cellule morte
				if ( v==3 ) set_vivante(i,j,*g);
			}
		}
	}
	return;
}
/** 
*@fn void evolue_avec_viellissement(grille *g, grille *gc)
*fait évoluer la grille en tenant en compte du viellissement des cellules 
*@param 1 \c grille *g 
*@param 2 \c grille *gc 
*@return rien 
*/

void evolue_avec_vieillissement (grille *g, grille *gc, int (*cyclique_ou_non)(int,int,grille)){
  copie_grille (*g,*gc); // copie temporaire de la grille
  int i,j,l=g->nbl, c = g->nbc,v;
  for (i=0; i<l; i++)
    {
      for (j=0; j<c; ++j)
				{
	  			v = (*cyclique_ou_non)(i, j, *gc);
	  			if (est_vivante(i,j,*g))
	    			{ // evolution d'une cellule vivante
	      			if ( v!=2 && v!= 3 ) set_morte(i,j,*g); // si elle a moins de deux ou plus de trois voisins elle meurt
	      			else if (g->cellules[i][j] > 8) set_morte(i,j,*g);// on suppose que age-cel >= 1000 elle meurt
	      			else {g->cellules[i][j]++;} // sinon on incrémente son age++
	    			}
	  			else
	    			{ // evolution d'une cellule morte
	      			if ( v==3 ) set_vivante(i,j,*g);// si elle a exactement 3 voisins alors elle nait
	    			}
				}
    }
}

