FROM ubuntu:20.04

WORKDIR /tetris
RUN apt-get update


# Install necessary dependencies
RUN apt-get install -y g++
RUN apt-get install -y libsfml-dev
RUN apt-get install -y x11-xserver-utils
RUN apt-get install -y mesa-utils libgl1-mesa-glx
# Copy your C++ source code to the container
COPY Pieces.cpp .
COPY Pieces.hpp .
COPY PiecesFactory.cpp .
COPY PiecesFactory.hpp .
COPY Tetris.cpp .
COPY Tetris.hpp .
COPY Test.cpp .


# Compile the C++ program
RUN g++ -std=c++11 -g -I ./ Pieces.cpp PiecesFactory.cpp Tetris.cpp Test.cpp -o play_tetris_game.out -lsfml-graphics -lsfml-window -lsfml-system

CMD ["./play_tetris_game.out"]