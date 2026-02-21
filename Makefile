# Cible
TARGET = ./bin/a.exe

# Compilateur
CC = gcc
CFLAGS = -Wall
LDFLAGS = 

# Fichiers
SRCS = ./src/main.c ./src/interpreter.c
INCLUDES = 

OBJS = $(SRCS:.c=.o)
DEPS = ./src/interpreter.h

# Commandes cross-platform (Win/Linux)
ifeq ($(OS),Windows_NT)
	RM = cmd /c "Del /Q"
	FIXPATH = $(subst /,\,$(1))
	MKDIRBIN = cmd /c "if not exist ./bin mkdir ./bin"
else
	RM = rm -f
	FIXPATH = $1
	MKDIR = mkdir -p ./bin
endif

.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) $(call FIXPATH,$(OBJS)) $(call FIXPATH,$(TARGET))

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)