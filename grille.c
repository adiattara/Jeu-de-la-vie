/**
*@file grille.c 
*contient l'implémentation et signature  des fonctions relatives à une grille
*/

#include "grille.h"
/**
*@fn void init_grille_from_file (char * filename, grille* g)
*initialise une grille en recupérant les information nécessaires sur un fichier 
*@param 1 \c char *filename 
*@param 2 \c grille *g 
*@return  rien 
*/

void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes=0;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}
	
	fclose (pfile);
	return;
}
/**
*@fn copie_grille (grille gs, grille gd)
*copie une grille dans une autre 
*@param 1 \c grille  gs 
*@param 2 \c grille gd 
*@return rien 
*/


void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}
// alloue une grille de taille l*c, et initialise toutes les cellules à mortes

/**
*@fn void alloue_grille (int l, int c, grille* g)
*alloue une grille de taille l*c, et initialise toutes les cellules à mortes
*@param 1 \c int l 
*@param 2 \c int c 
*@param 3 \c grille  *g 
*@ return rien 
*/
void alloue_grille (int l, int c, grille* g){
    g ->nbl =l;
    g -> nbc =c ;
    g->cellules =(int**)malloc(sizeof(int*)*l);
    for (int i=0;i<l; i++){
    	g ->cellules[i]=(int*)malloc(sizeof(int)*c);
    	for (int j=0;j<c;j++){
    		//g-> cellules[i][j]=0;
		set_morte(i,j,*g);


    	}

    }
}
/**
*@fn void libere_grille (grille* g)
*libére une une grille 
*@param \grille *g
*@return rien
*/
void libere_grille (grille* g){
	int l= g->nbl;
	int c= g->nbc ;
	for (int i=0; i<l ; i++){
		 free(g-> cellules[i]);
	}
	free(g->cellules);
}
