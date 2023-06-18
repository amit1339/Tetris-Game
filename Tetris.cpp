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

bool Tetris::CanMove(const std::shared_ptr<Pieces>& piece, Direction direection)
{
    int old_state = piece->GetCurrentState();
    
    switch (direection)
    {
    case DOWN:
        for (auto block : piece->GetBlocks())
        {
            std::pair<int,int> position = block->GetPosition();
            if (position.second >= 19)
            {
                return false;
            }
            if (m_board[position.first][position.second + 1] && m_board[position.first][position.second + 1] != block)
            {
                if (CanMove(m_board[position.first][position.second + 1]->GetPiece(), DOWN) == false)
                {
                    return false;
                }
            }
        }
        break;

    case RIGHT:
        for (auto block : piece->GetBlocks())
        {
            std::pair<int,int> position = block->GetPosition();
            if (position.first >= 9)
            {
                return false;
            }

            if (m_board[position.first + 1][position.second] && m_board[position.first + 1][position.second] != block)
            {
                return false;
            }
        }
        break;
    case LEFT:
        for (auto block : piece->GetBlocks())
        {
            std::pair<int,int> position = block->GetPosition();
            if (position.first <= 0)
            {
                return false;
            }

            if (m_board[position.first - 1][position.second] && m_board[position.first - 1][position.second] != block)
            {
                return false;
            }
        }
        break;

    case ROTATE_LEFT:

        piece->m_current_state = (piece->m_current_state + 1) % 4;

        for (auto block : piece->GetBlocks())
        {
            std::pair<int,int> position = block->GetPosition();

            if (m_board[position.first][position.second] && m_board[position.first][position.second] != block)
            {
                piece->m_current_state = old_state;
                return true;
            }
        }
        break;
    
    case ROTATE_RIGHT:

        piece->m_current_state = (piece->m_current_state - 1) % 4;

        for (auto block : piece->GetBlocks())
        {
            std::pair<int,int> position = block->GetPosition();

            if (m_board[position.first][position.second] && m_board[position.first][position.second] != block)
            {
                piece->m_current_state = old_state;
                return true;
            }
        }
        break;

    }
    piece->m_current_state = old_state;
    return true;
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
                    if (CanMove(piece, LEFT))  
                    {
                        piece->Move(LEFT, m_board);
                    }
                    break;
                case sf::Keyboard::Right:
                    if (CanMove(piece, RIGHT))  
                    {
                        piece->Move(RIGHT, m_board);  
                    }
                    break;
                case sf::Keyboard::Down:
                    break;
                case sf::Keyboard::A:
                    if (CanMove(piece, ROTATE_LEFT))  // Check collision after rotating
                    {
                        piece->Move(ROTATE_LEFT, m_board);
                    }
                    break;
                case sf::Keyboard::D:
                    if (CanMove(piece, ROTATE_RIGHT))  // Check collision after rotating
                    {
                        piece->Move(ROTATE_RIGHT, m_board);
                    }
                    break;
                case sf::Keyboard::Q:
                    m_isRunning = false;
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
