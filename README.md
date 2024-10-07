# SYSTEME DE VERSIONAGE DE MON PROJET (JEUX DE lA VIE)
---------------------------------------------------------------------------------------------------------------
#### EXPLICATION DU SYSTEME DE VERSIONNAGE :
Je divise le projet en 6 niveaux : niveau 0, niveau 1, 2, 3, 4, 5

- **Niveau 0 (=v_0.0)** : correspond à la version initiale du projet, aucune modification n'a été apportée sur le projet.
- À chaque commit important qui permet d'évoluer dans le niveau 1, on fait un tag (=v_0.1.1).
- Si le niveau 1 est terminé, on versionne notre projet en v_1.0.
- À chaque commit important qui permet d'évoluer dans le niveau 2, on fait un tag (=v_1.1).
- Si le niveau 2 est terminé, on versionne notre projet en v_2.0.
- ...
- ...

On suit cette logique jusqu'à ce que le niveau 5 soit terminé, ainsi on livre une version (v_5.0) du projet.

-------------------------------------------------------------------------------------------------------------
#### LISTE DES VERSIONS :
- **v_0.0** : fichier de départ
- **v_0.1** : implémentation des fonctions `alloue_grilles` et `libere_grille`
- **v_1.0** : terminaison du niveau 1 et début du niveau 2
- **v_1.1** : activation ou désactivation du cyclique, c'est la touche 'c' dans la fonction `debut_jeu`
- **v_2.0** : niveau 2 terminé, passage niveau 3
- **v_2.1** : makefile amélioré, utilisation de `vpath`, option `-I` pour gcc
- **v_2.1.1** : programmation de la fonction `évolue_avec_vieillissement`
- **v_2.1.2** : correction bug vieillissement
- **v_3.0** : niveau 3 achevé, début de niveau 4
- **v_3.1** : dessin grille, programmation fenêtre, clic souris pour quitter
- **v_4.0** : niveau 4 achevé et début niveau 5
- **v_4.1** : mise à jour du makefile