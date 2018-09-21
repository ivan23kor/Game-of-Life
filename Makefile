BIN=game
COMPILE_FLAGS=-lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window
SRC=src/
OBJ=obj/
BIN=game

test: build
	./$(BIN)

build: main.cpp | clean_all
	g++ -c $(SRC)cell.cpp -o $(OBJ)cell.o $(COMPILE_FLAGS)
	g++ -c main.cpp -o $(OBJ)main.o $(COMPILE_FLAGS)
	g++ $(OBJ)main.o $(OBJ)cell.o -o $(BIN) $(COMPILE_FLAGS)

clean_all:
	rm -rf $(OBJ)* $(BIN)