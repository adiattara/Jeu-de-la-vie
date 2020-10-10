#include "grille.h"

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


void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}
// alloue une grille de taille l*c, et initialise toutes les cellules à mortes
void alloue_grille (int l, int c, grille* g){
    g ->nbl =l;
    g -> nbc =c ;
    g->cellules =(int**)malloc(sizeof(int*)*l);
    for (int i=0;i<l; i++){
    	g ->cellules[i]=(int*)malloc(sizeof(int)*c);
    	for (int j=0;j<c;j++){
    		g-> cellules[i][j]=0;
    	}

    }
}
void libere_grille (grille* g){
	int l= g->nbl;
	int c= g->nbc ;
	for (int i=0; i<l ; i++){
		 free(g-> cellules[i]);
	}
	free(g->cellules);
}
