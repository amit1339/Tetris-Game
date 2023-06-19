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
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            m_board[i][j] = nullptr;
        }
    }
    
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
                if (m_board[position.first][position.second + 1] != nullptr && CanMove(m_board[position.first][position.second + 1]->GetPiece(), DOWN) == false)
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

            if (m_board[position.first + 1][position.second] == nullptr && m_board[position.first + 1][position.second] != block)
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
    std::shared_ptr<Pieces> piece = m_factory.Create(1);
    float dropTime = 0.0f;
    float dropInterval = 1.0f; // Drop interval in seconds */

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
                    if (CanMove(piece, DOWN))  
                    {
                        piece->Move(DOWN, m_board);  
                    }
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

        if (dropTime >= dropInterval)
        {
            dropTime = 0.0f;
            if (CanMove(piece, DOWN))
            {
                piece->Move(DOWN, m_board);
            }
        }

        m_window->clear();

        for (auto i : m_dropped)
        {
            i->Render(*m_window);
        }

        piece->Render(*m_window);

        m_window->display();
    }
}

