# Makefile

all:
	gcc -Wall -Wextra -O0 -fsanitize=address -g `pkg-config --cflags gtk+-3.0 sdl2 SDL2_image` -c nn2.c lexer.c file.c
	gcc -fsanitize=address -g `pkg-config --libs gtk+-3.0 sdl2 SDL2_image` -lm *.o
clean:
	rm *.o
	rm *.out
