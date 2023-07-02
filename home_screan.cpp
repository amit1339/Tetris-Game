#include "home_scream.hpp"

HomeScreen::HomeScreen(sf::RenderWindow* window) : m_window(window)
{
}

void HomeScreen::Run()
{
    sf::Font font;
    if (!font.loadFromFile("Arial.ttf"))
    {
        // Error loading font
        return;
    }

    sf::Text titleText("Tetris", font, 48);
    titleText.setFillColor(sf::Color::Black);
    titleText.setPosition(110, 100);

    sf::Text inputText("Enter your name:", font, 24);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(80, 200);

    sf::RectangleShape inputBox(sf::Vector2f(200, 40));
    inputBox.setPosition(80, 250);
    inputBox.setOutlineThickness(2);
    inputBox.setOutlineColor(sf::Color::Black);

    sf::Text playerNameText("", font, 24);
    playerNameText.setFillColor(sf::Color::Black);
    playerNameText.setPosition(90, 255);

    bool isEnteringName = true;

    while (m_window->isOpen() && isEnteringName)
    {
        sf::Event event;
        while (m_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_window->close();
                return;
            }
            else if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128 && event.text.unicode != 13) // 13 is the Enter key
                {
                    if (event.text.unicode == 8 && m_playerName.length() > 0) // 8 is the Backspace key
                    {
                        m_playerName.pop_back();
                    }
                    else if (m_playerName.length() < 15) // Limit name to 20 characters
                    {
                        m_playerName += static_cast<char>(event.text.unicode);
                    }
                }
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter && m_playerName.length() > 0)
                {
                    isEnteringName = false;
                }
            }
        }

        playerNameText.setString(m_playerName);

        m_window->clear(sf::Color::White);
        m_window->draw(titleText);
        m_window->draw(inputText);
        m_window->draw(inputBox);
        m_window->draw(playerNameText);
        m_window->display();
    }
}

std::string HomeScreen::GetPlayerName() const
{
    return m_playerName;
}