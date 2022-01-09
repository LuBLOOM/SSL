CC = gcc
LINKER = -lSDL2 -lSDL2_image -lSDL2_ttf -lGL -lGLU -lGLEW
SRC = $(wildcard src/*.c)
EXEC = ssl

all : $(EXEC)

$(EXEC) : $(SRC)
	$(CC) $^ -o $@ $(LINKER)

clean:
	rm $(EXEC)
