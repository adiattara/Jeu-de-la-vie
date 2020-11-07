/**
*@file io.c
*@author Amadou Diattara
* contient l'implémentation et profile des fonctions pour l'affichage d'une grille 
*/


#include "io.h"
/**
*@fn void affiche_trait (int c)
*@param \c int c 
*@return  rien 
*/
static int tmp_evolution;



void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}
/**
*@fn void affiche_ligne (int c, int* ligne)
*@param 1 \c int c 
*@param 2 \c int *ligne 
*@return rien


*/

void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) printf ("|   "); else printf ("| O ");
	printf("|\n");
	return;
}
/**
*@fn affiche_grille (grille g)
*affiche une grille en uilisant les fonctions affiche_trait  et affiche_ligne 
*@param \c grille g 
*@return rien  
*/

void affiche_grille (grille g){
    printf("tmp_evolution=%d",tmp_evolution);
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n");
	return;
}
/** 
*@fn efface_grille (grille g)
*efface une grille 
*@param \c grille g 
*@return rien 


*/ 

void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5); 
}
/**
*@fn  void debut_jeu(grille *g, grille *gc)
*marque le debut du jeu 
*@param 1 \grille *g 
*@param 2 \ grille *gc 
*@return rien 
*/
 

void debut_jeu(grille *g, grille *gc){
	int (*compte_voisins_vivants) (int, int, grille)= &compte_voisins_vivants_cyclique;
    void (*evolue)(grille *g,grille *gc ,int(*fonction)(int,int,grille))=&evolue_avec_vieillissement;

	char c = getchar(); 
	int evite_backslash=0;// on tape n puis "\n" du coup on doit éviter le back slah d'ou l'utilité de cette variable 
	tmp_evolution=0; // initialisation du temps d'évolution 
	
	while (c != 'q'){ // touche 'q' pour quitter
    
		switch (c) {
			case 'v':
			{
				if(evolue==&evolue_sans_vieillissement){
	        		evolue=&evolue_avec_vieillissement;
					printf("VIEILLISSEMENT ACTIVÉ");

	     		}
				else{
					evolue=&evolue_sans_vieillissement;
					printf("VIEILLISSEMENT DÉSACTIVÉ");
				}
				while(getchar()!='\n');
				printf("\n\e[%dA",3);
				break;
			}
			case '\n' : 
			{       
					if(evite_backslash){
						evite_backslash=0;

					}
					else{ // touche "entree" pour évoluer
					evolue(g,gc,compte_voisins_vivants);
				    tmp_evolution++;
					efface_grille(*g);
					printf("\e[H\e[2J");
					affiche_grille(*g);
					}
					break;
			}
				
			case 'n':
			{  
                tmp_evolution=0;
				libere_grille(g);
				libere_grille(gc);
				printf(" entrer le chemin complet du fichier  en partant de la racine ou du répertoir courant ");
				char *chaine=(char *)malloc(sizeof(char)*100);
	            scanf("%s",chaine);
	            
	            init_grille_from_file ( chaine,  g);
	            alloue_grille(g->nbl,g->nbc,gc);
                 
	            affiche_grille(*g);


	            evite_backslash=1;
                free(chaine);

	            break;


			}
			case 'c':{ // activation ou désactivation du cyclique 
			    getchar();
				 
				if (compte_voisins_vivants== &compte_voisins_vivants_non_cyclique){
					compte_voisins_vivants=&compte_voisins_vivants_cyclique;
					printf(" MODE CYCLIQUE ACTIVÉ\n");

				}
				else {
					compte_voisins_vivants=&compte_voisins_vivants_non_cyclique;
					printf(" MODE CYCLIQUE DÉSACTIVÉ\n "); 
				}
				while(getchar()!='\n');
				printf("\n\e[%dA",3);
				break;

			}
			
			default : 
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
         c = getchar();
	}
}
