TARGET = autodidacte

CC = gcc
CFLAGS = -g -Wall -pedantic -ansi -std=c99

LINKER = gcc -o
LDFLAGS = -Wall 

SRCDIR = src
BINDIR = bin
OBJDIR = obj
LIBDIR = lib



SOURCES := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
SDL := -I/usr/include/SDL2 -lSDL2 -lSDL2_gfx -lSDL2_image
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm  =  rm -rf
$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(OBJECTS) $(LDFLAGS) $(SDL) -lm
	@echo "link ok"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(SDL)
	@echo "compiled "$<" ok"

.PHONY : remove clean run valgrind

clean:
	@$(rm) $(OBJECTS)
	@echo "clean ok"

remove : clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "exec removed"

run: 
	./$(BINDIR)/$(TARGET)

valgrind:

	valgrind --leak-check=full --show-leak-kinds=all -v ./$(BINDIR)/$(TARGET) 