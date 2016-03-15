TARGET = autodidacte

CC = gcc
CFLAGS = -W -Wall -std=c99 -pedantic -ansi

LINKER = gcc -o
LDFLAGS = Wall -I. -lm

SRCDIR = src
BINDIR = bin
OBJDIR = obj



SOURCES := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm  =  rm -f
$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(FLAGS) $(OBJECTS)
	@echo "link ok"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "compiled "$<" ok"

.PHONEY : clean
clean:
	@$(rm) $(OBJECTS)
	@echo "clean ok"

.PHONEY : remove
remove : clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "exec removed"

.PHONEY : 
run: 
	./$(BINDIR)/$(TARGET)