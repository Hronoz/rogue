# CC specifies which compiler to use
CC = gcc

# FLAGS specifies the compilation options we're using
FLAGS = -Wall -g

# OBJS specifies whis file to compile
OBJS = main.c

# LINKER specifies the libraies we're linking against
LINKER = -lncurses

# OBJD specifies the name of our executable
OBJD = main

all: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LINKER) -o $(OBJD)
