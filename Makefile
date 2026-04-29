CC = gcc
CFLAGS = -Iinclude -lm
SRC = src/canvas.c src/math3d.c src/renderer.c src/lighting.c src/animation.c
OBJ = $(SRC:.c=.o)
BIN = build/demo

all: $(BIN)

$(BIN): demo/main.c $(SRC)
	$(CC) demo/main.c $(SRC) -o $(BIN) $(CFLAGS)

clean:
	rm -f build/demo *.pgm frame_*.pgm cube_*.pgm ball_*.pgm task1_demo.pgm cube.gif ball.gif

.PHONY: all clean
