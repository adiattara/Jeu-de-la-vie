CC=gcc


vpath %.c src
vpath %.h include

ifeq ($(MODE),TEXTE)
main : main.o jeu.o grille.o io.o
	ar -crv	libjeu.a	jeu.o	io.o	grille.o
	mkdir -p lib
	mv libjeu.a lib
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


else

main : main.o jeu.o grille.o io_graph.o
	ar -crv	libjeu.a	jeu.o	io_graph.o	grille.o
	mkdir -p lib
	mv libjeu.a lib
	$(CC) -o $@  $^ -lcairo -lm -lX11
	mkdir -p bin 
	mv $@ bin
	mkdir -p obj
	mv *.o obj

	
main.o : main.c jeu.h grille.h io_graph.h
	$(CC) -c -g -o $@ $< -Iinclude -I/usr/include/cairo  
grille.o : grille.c grille.h 
	$(CC) -c -g -o $@ $< -Iinclude
io_graph.o:  io_graph.c grille.h jeu.h 
	$(CC) -c -g -o $@ $< -Iinclude	-I/usr/include/cairo

jeu.o :jeu.c jeu.h grille.h 
	$(CC) -c  -g -o $@ $< -Iinclude
	
endif	
	
dist :
	tar  cJvf DiattaraAmadou_Gol_v_1.1.tar.xz src/*.c include/*.h  makefile  Doxyfile
	
clean: 
	rm -r obj bin
docs :
	doxygen -g 
	makdir -p doc 
	mv Doxyfile doc
	

