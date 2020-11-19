/**
*@file io.graph.h
*contient la signature des fonctions pour l'affichage d'une grille
*@author Amadou Diattara
*/

#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <string.h>
#include <X11/Xlib.h>

//brief Taille horizontale et verticale de la fenêtre, qui est fixe suivant les grilles
 //(peut être redéf, tous les autres élts s'ajusteront)

#define SIZEF 650 //Peut être changé

double SIZECASEX; // taille des cases définie dynamiquement en fonction du nombre des cases (permet de charger de grandes grilles)
double SIZECASEY; // pour gérer le cas où la grille chargée n'est pas carrée
/**
*affichage graphique  d'une grille
**/
void affiche_grille_graphique(cairo_surface_t *surface, grille g);
/**
* debute le jeu
**/
void debut_jeu(grille *g, grille *gc);

#endif