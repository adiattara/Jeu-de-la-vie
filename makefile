CC=gcc


vpath %.c src
vpath %.h include


main : main.o jeu.o grille.o io.o
	$(CC) -o $@  $^
	mkdir -p bin 
	mv $@ bin
	mkdir -p obj
	mv *.o obj

	
main.o : main.c jeu.h grille.h io.h
	$(CC) -c -g -o $@ $< -Iinclude
grille.o : grille.c grille.h 
	$(CC) -c -g -o $@ $< -Iinclude
io.o:  io.c grille.h jeu.h 
	$(CC) -c -g -o $@ $< -Iinclude

jeu.o :jeu.c jeu.h grille.h 
	$(CC) -c  -g -o $@ $< -Iinclude
	
	
dist :
	tar  cJvf DiattaraAmadou_Gol_v_1.1.tar.xz src/*.c include/*.h  makefile  Doxyfile
	
clean: 
	rm -r obj bin
docs :
	doxygen -g 
	makdir -p doc 
	mv Doxyfile doc
	

