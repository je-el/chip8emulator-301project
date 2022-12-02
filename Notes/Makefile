# makefile is ussed to define a set of tasks to be executed
# usually used to compile programs from source code

# form of compilation rules format::
# target: dependencies
#		  command

#should I include an install function?? 
##maybe not now but later on.

BINARY=main.bin 

build:
	gcc main.s `sdl-config --cflags --libs` -o $(BINARY)

debug:
	gcc main.s `sdl-config --cflags --libs` -0 $(BINARY) -gstabs+
	gdb -q $(BINARY)

run: 
	build
		./$(BINARY) $(ROM)

clean: #so that those pesky executables can disapear after we finish running :)
	rm $(BINARY)

# when you want to suppress echoing the actual command so that when
# suhc targets are called you should use @echo/command and then the
# execution should ignore repeating the actual command again and 
# run the code itself
