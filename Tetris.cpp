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

/* void Tetris::AddToDropedMap(std::shared_ptr<Pieces> piece)
{
    for (int row = 0; row < PIECE_SIZE; row++) 
    {
        for (int col = 0; col < PIECE_SIZE; col++) 
        {
            if (piece->m_state[piece->m_current_state][row][col] != nullptr) 
            {
                sf::Vector2f blockPosition = piece->m_state[piece->m_current_state][row][col]->GetPosition();
                int blockX = static_cast<int>(blockPosition.x) / BlockSize;
                int blockY = static_cast<int>(blockPosition.y) / BlockSize;

                if (blockX >= 0 && blockX < m_window->getSize().x && blockY >= 0 && blockY < m_window->getSize().x) 
                {
                    m_dropped[blockX][blockY] = piece->m_state[piece->m_current_state][row][col];
                }
            }
        }
    }
} */


bool Tetris::CheckCollision(const std::shared_ptr<Pieces>& piece)
{
    for (const auto& droppedPiece : m_dropped)
    {
        const sf::Vector2f& piecePos = piece->GetPosition();
        const sf::Vector2f& droppedPos = droppedPiece->GetPosition();

        if (piecePos.y + BlockSize == droppedPos.y && piecePos.x == droppedPos.x)
        {
            std::cout << piecePos.y << " piece x and dropped x " << droppedPos.y << std::endl;
            return true;
        }
    }
    return false;

}



bool Tetris::CheckEndGame(const std::shared_ptr<Pieces>& piece)
{
    if (piece->GetPosition().y == 0)
    {
        return true;
    }
    return false;
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
                    break;
                case sf::Keyboard::Right:
                    piece->Move(RIGHT);
                    break;
                case sf::Keyboard::Down:
                    piece->Move(DOWN);
                    break;
                case sf::Keyboard::A:
                    piece->Rotate(LEFT);
                    break;
                case sf::Keyboard::D:
                    piece->Rotate(RIGHT);
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
                //AddToDropedMap(piece);
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

        // Render the Tetris pieces
        

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