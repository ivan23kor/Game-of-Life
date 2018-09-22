BIN=game
COMPILE_FLAGS=-lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window
SRC=src/
OBJ=obj/
BIN=bin/game

test: build
	./$(BIN)

build: clean_all
	g++ -c $(SRC)cell.cpp -o $(OBJ)cell.o $(COMPILE_FLAGS)
	g++ -c $(SRC)pattern.cpp -o $(OBJ)pattern.o $(COMPILE_FLAGS)
	g++ -c main.cpp -o $(OBJ)main.o $(COMPILE_FLAGS)
	g++ $(OBJ)main.o $(OBJ)cell.o $(OBJ)pattern.o -o $(BIN) $(COMPILE_FLAGS)

clean_all:
	rm -rf $(OBJ)* $(BIN)
