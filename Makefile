# Executable
EXEC = bin/exec

# All object files
OBJ_FILES = obj/main.o obj/Date.o obj/Voiture.o obj/Place.o
OBJ_FILES+= obj/Parking.o obj/Message.o obj/Contenu.o obj/Agent.o
OBJ_FILES+= obj/Affichage.o


# Compilator rules
CC = g++
CFLAGS = -Wall -ggdb -std=c++17
COMPILATIONOBJ = $(CC) $(CFLAGS) -c $< -o $@ 


INCLUDE_SFML = -I./extern/SFML/include 
LIBS_SFML = -Lextern/SFML/lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system 



all: $(EXEC)

bin/exec : $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -lpthread -o $@ $(LIBS_SFML)

# Objects
obj/main.o: src/main.cpp src/Date.h src/Voiture.h
	$(COMPILATIONOBJ) 

obj/Affichage.o : src/Affichage.cpp src/Affichage.h
	$(COMPILATIONOBJ)

obj/Parking.o : src/Parking.cpp src/Parking.h src/Agent.cpp src/Agent.h src/Place.cpp src/Place.h
	$(COMPILATIONOBJ)

obj/Place.o : src/Place.cpp src/Place.h src/Date.cpp src/Date.h
	$(COMPILATIONOBJ)


obj/Voiture.o : src/Voiture.cpp src/Voiture.h src/Agent.cpp src/Agent.h
	$(COMPILATIONOBJ)

obj/Date.o : src/Date.cpp src/Date.h 
	$(COMPILATIONOBJ)

obj/Agent.o : src/Agent.cpp src/Agent.h src/Message.cpp src/Message.h
	$(COMPILATIONOBJ)

obj/Message.o : src/Message.cpp src/Message.h src/Contenu.cpp src/Contenu.h
	$(COMPILATIONOBJ)

obj/Contenu.o : src/Contenu.cpp src/Contenu.h
	$(COMPILATIONOBJ)




clean:
	rm obj/*