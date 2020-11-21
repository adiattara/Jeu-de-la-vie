CC=gcc
CPPFLAGS=
LDFLAGS=


vpath %.c src
vpath %.h include

ifeq ($(MODE),TEXTE)
IOC = io.c
IOO = io.o
IOH=io.h
LDFLAGS += -ljeu -Llib/
CPPFLAGS=	-Iinclude
else
IOC = io_graph.c
IOO = io_graph.o
IOH=io_graph.h
CPPFLAGS += -Iinclude -I/usr/include/cairo 
LDFLAGS += -lcairo -lm -lX11 -ljeu -Llib/
endif
main : main.o jeu.o grille.o $(IOO)
	ar -crv	libjeu.a	jeu.o	grille.o
	mkdir -p lib
	mv libjeu.a lib
	$(CC) -o $@  $^ $(LDFLAGS)
	mkdir -p bin 
	mv $@ bin
	mkdir -p obj
	mv *.o obj

	
main.o : main.c jeu.h grille.h $(IOH)
	$(CC) -c -g -o $@ $<	$(CPPFLAGS)
grille.o : grille.c grille.h 
	$(CC) -c -g -o $@ $<	$(CPPFLAGS)
$(IOO):  $(IOC) grille.h jeu.h 
	$(CC) -c -g -o $@ $< 	$(CPPFLAGS)

jeu.o :jeu.c jeu.h grille.h 
	$(CC) -c  -g -o $@ $< 	$(CPPFLAGS)

	
dist :
	tar  cJvf DiattaraAmadou_Gol_v_4.1.tar.xz src/*.c include/*.h  makefile	Doxyfile
	
clean: 
	rm -r obj bin
docs :
	@mkdir -p doc
	doxygen
	mv html latex doc
	

