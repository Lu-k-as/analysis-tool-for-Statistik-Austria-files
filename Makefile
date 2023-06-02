CC=g++
CFLAGS=-g
# static inline gives warnings without next line 
# CFLAGS=-g -std=c++1z
SRC=Projekt2022_16.cpp importdata.cpp
OBJ=Projekt2022_16.o importdata.o database.o

all: fullprogramm

fullprogramm: $(OBJ)
	$(CC) $(CFLAGS) -o Projekt2022_16 $(OBJ)

Projekt2022_16.o: importdata.h database.h Projekt2022_16.cpp
	$(CC) $(CFLAGS) -c Projekt2022_16.cpp

importdata.o: database.h importdata.h importdata.cpp
	$(CC) $(CFLAGS) -c importdata.cpp

database.o: database.h database.cpp
	$(CC) $(CFLAGS) -c database.cpp

clean:
	rm main main.o importdata.o database.o
