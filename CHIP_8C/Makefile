#Compiler to use
CC = g++

# Compiler flags
CFLAGS = -Wall -std=c++17

# SDL2 compiler flags (sdl2-config)
SDL_CFLAGS = $(shell sdl2-config --cflags)

# SDL2 linker flags (using sdl2-config)
SDL_LDFLAGS = $(shell sdl2-config --libs)

# Target executable file
chip8: main.o chip8.o trap
	# Link the object files to create the executable
	$(CC) $(CFLAGS) $(SDL_LDFLAGS) -o $@ $^
	@echo "Executable file created, to run the chip8 emulator use command"
	echo "make run ROM=<ROM filename>" 
	echo "file clean up will happen automatically after exiting the console of the emulator"

# Compile main.cpp to create main.o
main.o: main.cpp chip8.h
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c -o $@ $<

# Compile chip8.cpp to create chip8.o
chip8.o: chip8.cpp chip8.h
	$(CC) $(CFLAGS) -c -o $@ $<

# Phony target to clean up object files and executable
#.PHONY is used to now we dont get the error "no *.o files found" etc
.PHONY: clean

clean:
	rm -f *.o chip8
# Catch the EXIT signal and run the clean target
trap:
	trap "$(MAKE) clean" EXIT

# Target to run the emulator with a specified ROM file
.PHONY: run

run: chip8
	./chip8 ROMS/$(ROM).ch8

