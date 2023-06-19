INCLUDE = -I./

SRCS = PiecesFactory.cpp Pieces.cpp Tetris.cpp
GAME_MAIN = Test.cpp

NAME = Tetris_Game

# Compiler flags
CPPFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -g
CC = g++

$(NAME): $(SRCS) $(GAME_MAIN)
	$(CC) $(INCLUDE) $^ $(CPPFLAGS) -o $(NAME).out

.PHONY: clean
clean:
	rm -f *.hex *.out *.so *.o
