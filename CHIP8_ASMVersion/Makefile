BINARY=main.bin

build:
	gcc main.s `sdl2-config --cflags --libs` -o $(BINARY)

debug:
	gcc main.s `sdl2-config --cflags --libs` -o $(BINARY) -gvms
	gdb -q $(BINARY)

run: build
	./$(BINARY) $(ROM)

clean:
	rm $(BINARY)