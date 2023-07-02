#ifndef __HOME_SCREAN_HPP__
#define __HOME_SCREAN_HPP__



#include <SFML/Graphics.hpp>
#include <string>

class HomeScreen
{
public:
    HomeScreen(sf::RenderWindow* window);
    void Run();
    std::string GetPlayerName() const;

private:
    sf::RenderWindow* m_window;
    std::string m_playerName;
};

#endif //__HOME_SCREAN_HPP__