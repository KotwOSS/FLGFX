export CC = gcc
export PRJPATH = $(shell pwd)
export INCLUDE = $(PRJPATH)/include
export LIBS = -lm -lglfw -lGL -lGLEW
export CFLAGS = -Wall -g -I$(INCLUDE)
export OBJDIR = $(PRJPATH)/obj/

OBJECTS = \
		  main.o \
		  gfx/shader.o

OBJECTS := $(addprefix $(OBJDIR), $(OBJECTS))

flgfx:
	mkdir -p obj/gfx
	
	cd src; $(MAKE)
	cd src/gfx; $(MAKE)

	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LIBS)
		

clean:
	rm -rf obj
	rm -rf flgfx
