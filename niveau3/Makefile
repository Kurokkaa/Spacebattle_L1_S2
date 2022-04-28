CFLAGS = -O3 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf -lm

INC = sld2\sdl2-light.h SDL_data\SDL_data.h SDL_graphics\SDL_graphics.h constantes\constantes.h struct\struct.h sdl2\sdl2-ttf-light.h 
SRC = main.c sdl2\sdl2-light.c struct\struct.c SDL_data\SDL_data.c SDL_graphics\SDL_graphics.c sdl2\sdl2-ttf-light.c  
OBJ = $(SRC:%.c=%.o)

PROG = spacebattle

%.o: %.c $(@D)\$(INC)
	gcc $(CFLAGS) -c $(@D)\$<

spacebattle: $(OBJ)
	gcc $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@

test:SDL_data\test.exe 

SDL_data\test.exe: SDL_data\tests.o SDL_data\SDL_data.o struct\struct.o
	gcc $(CFLAGS) $^ $(LDFLAGS) -o $@ 

tests.o:SDL_data\tests.c
	gcc $(CFLAGS) -c $< 


doc: $(PROG)
	doxygen ./$(PROG)
	make -C latex

clean:
	rm -f *~ *.o $(PROG)
	rm -rf latex html

