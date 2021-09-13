# Executable
EXEC = bin/exec

# All object files
OBJ_FILES = obj/main.o obj/Date.o obj/Voiture.o obj/Reservation.o obj/Place.o
OBJ_FILES+= obj/Parking.o


# Compilator rules
CC = g++
CFLAGS = -Wall -ggdb -std=c++14
COMPILATIONOBJ = $(CC) $(CFLAGS) -c $< -o $@ 



all: $(EXEC)

bin/exec : $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS_SFML)

# Objects
obj/main.o: src/main.cpp src/Date.h src/Voiture.h
	$(COMPILATIONOBJ)

obj/Parking.o : src/Parking.cpp src/Parking.h
	$(COMPILATIONOBJ)

obj/Place.o : src/Place.cpp src/Place.h
	$(COMPILATIONOBJ)

obj/Reservation.o : src/Reservation.cpp src/Reservation.h
	$(COMPILATIONOBJ)

obj/Voiture.o : src/Voiture.cpp src/Voiture.h
	$(COMPILATIONOBJ)

obj/Date.o : src/Date.cpp src/Date.h 
	$(COMPILATIONOBJ)


clean:
	rm obj/*