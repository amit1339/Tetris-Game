#include "Tetris.hpp"
#include <iostream>
#include <random>

int RandomNum()
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, 6);

    return distribution(generator);
}

Tetris::Tetris(sf::RenderWindow *window):m_window(window), m_score(0), m_isRunning(true)
{
}

void Tetris::Run()
{
    std::shared_ptr<Pieces> piece = m_factory.Create(RandomNum());
    float dropTime = 0.0f;
    float dropInterval = 1.0f; // Drop interval in seconds

    while (m_isRunning && m_window->isOpen())
    {
        sf::Event event;
        while (m_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_window->close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Left:
                    piece->Move(LEFT);
                    if (CheckCollision(piece))  // Check collision after moving
                    {
                        piece->Move(RIGHT);  // Undo the move if there's a collision
                    }
                    break;
                case sf::Keyboard::Right:
                    piece->Move(RIGHT);
                    if (CheckCollision(piece))  // Check collision after moving
                    {
                        piece->Move(LEFT);  // Undo the move if there's a collision
                    }
                    break;
                case sf::Keyboard::Down:
                    piece->Move(DOWN);
                    break;
                case sf::Keyboard::A:
                    piece->Rotate(LEFT);
                    if (CheckCollision(piece))  // Check collision after rotating
                    {
                        piece->Rotate(RIGHT);  // Undo the rotation if there's a collision
                    }
                    break;
                case sf::Keyboard::D:
                    piece->Rotate(RIGHT);
                    if (CheckCollision(piece))  // Check collision after rotating
                    {
                        piece->Rotate(LEFT);  // Undo the rotation if there's a collision
                    }
                    break;
                }
            }
        }

        float deltaTime = m_clock.restart().asSeconds();
        dropTime += deltaTime;

        if (CheckCollision(piece) || piece->GetPosition().y >= 395)
        {
            if (CheckEndGame(piece))
            {
                std::cout << "Game over! Your score: " << m_score << std::endl;
                m_isRunning = false;
            }
            else
            {
                m_dropped.push_back(piece);
                piece = m_factory.Create(RandomNum());
                dropTime = 0.0f;
            }
        }
        else if (dropTime >= dropInterval)
        {
            piece->Move(DOWN);
            dropTime = 0.0f;
        }

        m_window->clear();

        for (auto i : m_dropped)
        {
            i->Render(*m_window);
        }

        piece->Render(*m_window);

        m_window->display();
    }

    while (m_window->isOpen())
    {
        sf::Event event;
        while (m_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_window->close();
            }
        }
    }
}
