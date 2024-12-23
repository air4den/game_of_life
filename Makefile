CC = g++
CFLAGS = -std=c++11 -Wall -g
SRC = *.cpp
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
TARGET = game_of_life

build: main.cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

run: main.cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)
	./$(TARGET)

clean: 
	@rm -rf $(TARGET) *.o $(wildcard *.dSYM)