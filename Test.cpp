#include <Tetris.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(350, 500), "SFML Tetris");
    Tetris game(&window);
    game.Run();
    return 0;
}