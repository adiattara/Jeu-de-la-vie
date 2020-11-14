

/**
*@file io.graph.c
*@author Amadou Diattara
* contient l'implémentation et profile des fonctions pour l'affichage graphique d'une grille 
*/
#include <stdio.h>
#include <stdlib.h>
#include"io_graph.h"
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <string.h>




//Taille du texte standard

int TEXTSIZE1 = (SIZEF/60);


// Taille du texte plus petite

int TEXTSIZE2 = SIZEF/65;


//Définit la zone text de la fenêtre

int TEXTAREA = SIZEF/18;



// Compteur d'évolution
int  Evolution = 0;

// Affichage du compteur d'évolution
char strTemps[5];


 //brief Variable à afficher

char varChar[256];


 // pointeur de fonction nécessaires
int (*compte_voisins_vivants)(int,int,grille) = compte_voisins_vivants_cyclique;
void (*evolue)(grille *g,grille *gc ,int(*fonction)(int,int,grille))=&evolue_avec_vieillissement;

//chemin grilles 

char cheminFichier[255];


 // 0 affichage terne de la inputbox, 1 affichage couleurs vives

int nvGrilleFocus = 0;


//brief Détermine si on veut le contour des cases (activé par défaut)
int contourCase = 1;




void affiche_grille_graphique(cairo_surface_t *surface, grille g)
{
	
	// cration du contexte et initialisation 
	cairo_t *cr;
	cr=cairo_create(surface);
	
	// coloration du source 
	cairo_set_source_rgb (cr, 0.9, 0.9, 0.); //(0.0,0.0 0.0) fond noir 
	cairo_paint(cr);

	// choix police

	cairo_select_font_face (cr, "Ubuntu", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    // choix taille police 
	cairo_set_font_size (cr, TEXTSIZE1);
	// AFFICHAGE TEXTE ETAT

		// Temps d'évolutiion 
	cairo_set_source_rgb(cr, 0.0, 0.0, 0.0); 
	cairo_move_to(cr, 0, TEXTSIZE1);
	sprintf(strTemps, "%d", Evolution);
	strcpy(varChar, "Temps d'évolution : ");
	cairo_show_text(cr, strcat(varChar, strTemps));

		// Vieillissement
	cairo_move_to(cr, 0, 2*TEXTSIZE1);
	if(evolue==evolue_avec_vieillissement ) cairo_show_text(cr, "Vieillissement activé : oui");
	else cairo_show_text(cr, "Vieillissement activé : non");
	// Cyclique
	cairo_move_to(cr, 0, 3*TEXTSIZE1);
	if(compte_voisins_vivants==compte_voisins_vivants_cyclique) cairo_show_text(cr, "Calcul cyclique du voisinage activé : oui");
	else cairo_show_text(cr, "Calcul cyclique du voisinage activé : non");
	cairo_move_to(cr, 41*TEXTSIZE1, 0.9*TEXTSIZE1);
	
	// TEXTFIELD INPUTBOX

	 // fond 
	cairo_rectangle(cr,41*TEXTSIZE1,SIZEF/30,16*TEXTSIZE1,1*TEXTSIZE1);
	(nvGrilleFocus == 1)?(cairo_set_source_rgb(cr, 0.0, 0.0, 0.0)):(cairo_set_source_rgb(cr, 1., 1, 1));
	cairo_fill(cr);
	cairo_stroke(cr);
	// texte
	(nvGrilleFocus == 1)?(cairo_set_source_rgb(cr, 1, 1, 1)):(cairo_set_source_rgb(cr, 0.0, 0.0, 0.0));
	cairo_move_to(cr, 41*TEXTSIZE1, 1.8*TEXTSIZE1);
	cairo_show_text(cr, "Chemin vers la grille à charger :");
	cairo_move_to(cr, 41*TEXTSIZE1, 2.9*TEXTSIZE1);
	cairo_select_font_face (cr, "Courrier", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_show_text(cr, cheminFichier);
	// FIN TEXTFIELD INPUTBOX

	
	// DESSIN DE LA GRILLE
	for(int i = 0; i < g.nbl; i++) { // parcourir toutes les lignes
		for(int c = 0; c < g.nbc; c++) { // parcourir toutes les colonnes	
			if(contourCase==1)
				cairo_set_source_rgb (cr, 0.1, 0.3, 0.1); // contour des cases blanc (S'ACTIVE/DESACTIVE AVEC X)
			else
				cairo_set_source_rgb (cr, 0, 0.1, 0); // contour des cases invisible (plus agréable)

			cairo_rectangle(cr,c*SIZECASEX,i*SIZECASEY+TEXTAREA,SIZECASEX,SIZECASEY); // on crée une case au bon emplacement
			
			for(int v = 1; v<=8; v++) { // couleur de la cellules en fonction de sa vie, plus elle se rapproche de 8 plus elle vire vers vers la couleur du fond
				if(g.cellules[i][c] == v){
				cairo_set_source_rgb (cr, 0.1,(0.7*((float)v)), 0.1); // 0.111 c'est le pas (= 1/9, pour avancer progressivement)
				cairo_fill(cr);}
			}
			
			if(g.cellules[i][c] == -1) { //coloriage en rouge si cellules non viable
				cairo_set_source_rgb (cr, 1.0, 0.0, 0.0); 
				cairo_fill(cr);
			}
			
			cairo_stroke(cr);

		}
	}
	// FIN DESSIN DE LA GRILLE
	
	
	// AFFICHE LIGNE SEPARATION
	cairo_move_to(cr, 0, TEXTAREA);
	cairo_set_source_rgb (cr, 0.1, 0.3, 0.1);
	cairo_rectangle(cr,0,TEXTAREA,SIZEF,0.5);
	cairo_stroke(cr);
	// FIN AFFICHE LIGNE SEPARATION
	
	
	cairo_destroy(cr); // destroy cairo mask	
}


void debut_jeu(grille *g, grille *gc){
	
	// X11 display
	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int scr;
	
	// calcul de la taille d'une case
	// la taille de la fenêtre est toujours fixe, c'est la taille des cases qui change
	// permet de pouvoir charger de très grandes grilles
	SIZECASEX = (double)(SIZEF)/((g->nbc));
	SIZECASEY = (double)(SIZEF-TEXTAREA)/((g->nbl));
	
	
	// init the display
	if(!(dpy=XOpenDisplay(NULL))) {
		fprintf(stderr, "ERROR: Could not open display\n");
		exit(1);
	}

	scr=DefaultScreen(dpy);
	rootwin=RootWindow(dpy, scr);

	win=XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEF, SIZEF, 0, 
			BlackPixel(dpy, scr), BlackPixel(dpy, scr));

	XStoreName(dpy, win, "Jeu de la vie");
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask|KeyPressMask|KeyReleaseMask);
	XMapWindow(dpy, win);
	
	// create cairo surface
	cairo_surface_t *cs; 
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEF, SIZEF);

	// run the event loop
	while(1) {
		
		XNextEvent(dpy, &e);
		
		// permet de connaître les codes des diff touches (équivalent du xmodmap -pke)
		//fprintf(stdout, "%d\n", e.xbutton.button);
		
		if(e.type==Expose && e.xexpose.count<1) 
		{
			affiche_grille_graphique(cs, *g);
		}
		//évolue
		//1 == clic gauche, 36 = touche Entrée
		else if((e.type==ButtonPress && e.xbutton.button == 1) || (e.type==KeyPress && e.xkey.keycode==36))
		{
			evolue(g,gc, compte_voisins_vivants);
			Evolution++;
			affiche_grille_graphique(cs, *g);
		}
		
		// activer/désactiver le calcul de voisinage cyclique (activé par défaut)
		if(e.type==KeyPress && e.xkey.keycode==54) // 54 = c
		{
			(compte_voisins_vivants == compte_voisins_vivants_cyclique)?(compte_voisins_vivants = compte_voisins_vivants_non_cyclique):(compte_voisins_vivants = compte_voisins_vivants_cyclique);
			affiche_grille_graphique(cs, *g);
		}
		
		// activer/désactiver le vieillissement
		if(e.type==KeyPress && e.xkey.keycode==55) // 55 = v
		{
			(evolue==&evolue_sans_vieillissement)?(evolue=&evolue_avec_vieillissement) :(evolue=evolue_sans_vieillissement);
			affiche_grille_graphique(cs, *g);
		}

		
		// activer/désactiver l'affichage du contour des grilles
		if(e.type==KeyPress && e.xkey.keycode==53) // 53 = x
		{ 
			(contourCase==1)?(contourCase=0):(contourCase=1);
			affiche_grille_graphique(cs, *g);
		}
        
		
		// charger nouvelle grille
		if(e.type==KeyPress && e.xkey.keycode==57) // 57 = n
		{
			KeySym key;		/* a dealie-bob to handle KeyPress Events */	
			char carac[256];
			nvGrilleFocus = 1;
			while(1)
			{
				XNextEvent(dpy, &e);
							if (e.type==KeyPress && XLookupString(&e.xkey,carac,256,&key,0)==1) 
							{
								if(e.xkey.keycode == 36) // Entrée
								{
									nvGrilleFocus=0;
					                libere_grille(g);
					                libere_grille(gc);
									init_grille_from_file(cheminFichier, g);
									alloue_grille(g->nbl, g->nbc, gc);
									SIZECASEX = SIZEF/((g->nbc));
									SIZECASEY = (SIZEF-TEXTAREA)/((g->nbl));
									Evolution = 0;
									//oscillation = 0;
									affiche_grille_graphique(cs, *g);
									break;
								}
								else if (e.xkey.keycode == 22) // Suppr
								{
									cheminFichier[strlen(cheminFichier)-1] = '\0'; //on suppr le dernier élément
								}
								else if (e.xkey.keycode == 9) // Echap
								{
									nvGrilleFocus=0; // on fait perdre le focus à l'inputbox
									affiche_grille_graphique(cs, *g);
									break;
								}

								else
								{
									strcat(cheminFichier, carac); // on ajoute le caractère tapé à la chaîne
								}
							}
							affiche_grille_graphique(cs, *g);
			}

		}
		// on peut quitter avec q, et le clic droit
		if((e.type==KeyPress && e.xkey.keycode==38) || (e.type==ButtonPress && e.xbutton.button == 3)) // 38 = q
			break;
		
	}
	
	cairo_surface_destroy(cs); // destroy cairo surface
	XCloseDisplay(dpy); // close the display
	
	return;	
}
