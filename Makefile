# CC specifies which compiler to use
CC = gcc

# FLAGS specifies the compilation options we're using
CFLAGS = -Wall -g -I$(IDIR)
IDIR = ./include/

# SOURCES specifes the src files
SRCDIR = ./src/
SOURCES = $(SRCDIR)*.c

# LINKER specifies the libraies we're linking against
LINKER = -lncurses

# OBJD specifies the name of our executable
OBJD = rogue

all: clean rogue

rogue:
	$(CC) $(CFLAGS) $(SOURCES) $(LINKER) -o $(OBJD)

run:
	./rogue

clean:
	rm rogue
