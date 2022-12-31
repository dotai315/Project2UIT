TARGET = camera

CC = gcc
CFLAGS = -g -Wall 

SRC = src
SRCS = $(wildcard $(SRC)/*.c)

OBJ = obj
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

INC = inc
INCLUDES = -I$(INC)

BIN_DIR = bin
BIN = $(BIN_DIR)/$(TARGET)

LIBS = -lcjson

PKG= `pkg-config --cflags --libs gstreamer-1.0` 

all: $(BIN)

$(BIN): $(OBJS) $(OBJ)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@ $(PKG) 

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c $< -o $@ $(PKG)

$(OBJ):
	mkdir -p $@

clean:
	rm -rf $(BIN_DIR)/* $(OBJ)/*
