# Cible
TARGET = ./bin/a.exe

# Compilateur
CC = gcc
CFLAGS = -Wall
LDFLAGS = 

# Fichiers
SRCS = ./src/main.c
INCLUDES = 

OBJS = $(SRCS:.c=.o)
DEPS = 

# Commandes cross-platform (Win/Linux)
ifeq ($(OS),Windows_NT)
else
endif


.PHONY: all clean

all: $(TARGET)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)