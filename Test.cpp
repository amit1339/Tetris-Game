#include <Tetris.hpp>
#include "home_scream.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(350, 475), "SFML Tetris");
    HomeScreen homeScreen(&window);
    homeScreen.Run();

    std::string playerName = homeScreen.GetPlayerName();
    if (!playerName.empty())
    {
        // Start the Tetris game with the player's name
        Tetris game(&window, playerName);
        game.Run();
    }

    return 0;
}