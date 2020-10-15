main : main.o jeu.o grille.o io.o
	gcc   -o $@  $^
main.o : main.c jeu.h grille.h io.h
	gcc -c -g  $<
grille.o : grille.c grille.h 
	gcc -c -g  $<

io.o:  io.c grille.h jeu.h 
	gcc -c -g $<

jeu.o :jeu.c jeu.h grille.h 
	gcc -c -g $<
	
dist :
	tar  cJvf sauve.tar.xz *.c *.h  makefile  doxygen 
	
clean: 
	rm  -f  *.o
	rm  main
docs :
	doxygen -g 
	

