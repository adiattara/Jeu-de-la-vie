# SYSTEME DE VERSIONAGE DE MON PROJET (JEUX DE A VIE)
---------------------------------------------------------------------------------------------------------------
#### EXPLICATION DU SYSTEME DE VERSIONNAGE :
je divise le projet  en 6 niveuau : niveau 0 ,niveau 1,2,3,4,5

niveau 0(=v_0.0) : corespond au version initale du projet aucune  modifiaction n'a été apporté sur le projet 

à chaque commite importante qui permet d'évolué dans le niveau 1 on fait un tag(=v_0.1.1)

si le niveau 1 est terminé  on versionne notre projet en v_1.0 

à chaque commite importante qui permet d'évolué dans le niveau 2 on fait un tag(=v_1.1)

si le niveau 2 est terminé  on versionne notre projet en v_2.0 
......
......

on suit cette logique jusqu'à ce que le niveau 5 soit terminé

ainsi on livre  une version(v_5.0) du projet


-------------------------------------------------------------------------------------------------------------
#### liste des versions :
v_0.0= fichier de départ 

v_0.1=implémentation des fonctions alloue_grilles et libere_grille

v_1.0 = terminaison du niveau 1 et debut du niveau 2 

v_1.1=activation ou désactivation du cyclique  c'est la touche 'c' dans la fonction debut_jeu

v_2.0=niveau 2 terminé passage niveau 3

v_2.1=makefile amélioré utilisation de vpath ,option -I pour gcc

v_2.1.1= programmation de la fonction évolue_avec_vieillissement

v_2.1.2= correction bug vieilleissement