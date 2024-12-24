CC = g++
CFLAGS = -std=c++11 -Wall -g -fsanitize=address
SRC = ./src/*.cpp
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
TARGET = game_of_life

build: $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

run: build
	./$(TARGET)

clean: 
	@rm -rf $(TARGET) *.o $(wildcard *.dSYM)