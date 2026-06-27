CC = g++
CFLAGS = -Wall -O2 -I C:/raylib/raylib/src -g
LIBS = -L C:/raylib/raylib/src -lraylib -lopengl32 -lgdi32 -lwinmm -static-libgcc -static-libstdc++

SRC = Battaglia_navale.cpp
OUT = Battaglia_navale.exe

all:
	$(CC) $(SRC) $(CFLAGS) -o $(OUT) $(LIBS)

clean:
	del $(OUT)