BIN=game
COMPILE_FLAGS=-lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window
GUI=src/GUI/
OBJ=obj/
BIN=game

test: build
	./$(BIN)

build: main.cpp
	g++ -c $(GUI)cell.cpp -o $(OBJ)cell.o $(COMPILE_FLAGS)
	g++ -c main.cpp -o $(OBJ)main.o $(COMPILE_FLAGS)
	g++ $(OBJ)main.o $(OBJ)cell.o -o $(BIN) $(COMPILE_FLAGS)
	