CC = gcc
CFLAGS = -Wall
LINKS = -lSDL2 -lSDL2_image -l SDL2_ttf
OUTFILE = snake
INFILE = main.c

snake: 
	$(CC) $(INFILE) $(CFLAGS) $(LINKS) -o $(OUTFILE)
