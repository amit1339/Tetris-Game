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

Tetris::Tetris(sf::RenderWindow *window, std::string playerName):m_window(window), m_score(0), m_isRunning(true), m_playerName(playerName)
{
    for (int i = 0; i < ROW_SIZE; i++)
    {
        for (int j = 0; j < COL_SIZE; j++)
        {
            m_board[i][j] = nullptr;
        }
    }
    
}

bool Tetris::CanMove(const std::shared_ptr<Pieces>& piece, Direction direction)
{
    int old_state = piece->GetCurrentState();

    switch (direction)
    {
    case DOWN:
        for (auto block : piece->GetBlocks())
        {
            std::pair<int,int> position = block->GetPosition();
            if (position.second >= COL_SIZE || position.second + 1 >= COL_SIZE)
            {
                return false;
            }
            std::shared_ptr<Block> other = m_board[position.first][position.second + 1];
            if (other && other->GetPiece() != block->GetPiece())
            {
                if (!CanMove(other->GetPiece(), DOWN))
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
            if (position.first >= ROW_SIZE || position.first + 1 >= ROW_SIZE)
            {
                return false;
            }

            std::shared_ptr<Block> other = m_board[position.first + 1][position.second];
            if (other && other->GetPiece() != block->GetPiece())
            {
                return false;
            }
        }
        break;

    case LEFT:
        for (auto block : piece->GetBlocks())
        {
            std::pair<int,int> position = block->GetPosition();
            if (position.first <= 0 || position.first - 1 < 0)
            {
                return false;
            }

            std::shared_ptr<Block> other = m_board[position.first - 1][position.second];
            if (other && other->GetPiece() != block->GetPiece())
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
            if (position.first < 0 || position.first >= ROW_SIZE || position.second < 0 || position.second >= COL_SIZE)
            {
                piece->m_current_state = old_state;
                return false;
            }

            std::shared_ptr<Block> other = m_board[position.first][position.second];
            if (other && other->GetPiece() != block->GetPiece())
            {
                piece->m_current_state = old_state;
                return false;
            }
        }
        break;

    case ROTATE_RIGHT:
        piece->m_current_state = (piece->m_current_state - 1) % 4;

        for (auto block : piece->GetBlocks())
        {
            std::pair<int,int> position = block->GetPosition();
            if (position.first < 0 || position.first >= ROW_SIZE || position.second < 0 || position.second >= COL_SIZE)
            {
                piece->m_current_state = old_state;
                return false;
            }

            std::shared_ptr<Block> other = m_board[position.first][position.second];
            if (other && other->GetPiece() != block->GetPiece())
            {
                piece->m_current_state = old_state;
                return false;
            }
        }
        break;
    }

    piece->m_current_state = old_state;
    return true;
}

void Tetris::DeleteRow(int col)
{
    for (int row = 0; row < ROW_SIZE; row++)
    {
        for (auto piece = m_dropped.begin(); piece != m_dropped.end(); piece++)
        {
            (*piece)->RemoveBlock(m_board[row][col]);
            if ((*piece)->GetBlocks().empty())
            {
                m_dropped.erase(piece);
                break;  // Break out of the loop after erasing the element
            }
        }
    }

    for (int c = col; c > 0; c--)
    {
        for (int row = 0; row < ROW_SIZE; row++)
        {
            auto temp = m_board[row][c];
            m_board[row][c] = m_board[row][c - 1];
            m_board[row][c - 1] = temp;

            if (m_board[row][c] != nullptr)
            {
                m_board[row][c]->SetPosition(0, 1);
            }
            if (m_board[row][c - 1] != nullptr)
            {
                m_board[row][c - 1]->SetPosition(0, -1);
                if (m_board[row][c - 1]->GetPosition().second == 0)
                {
                    m_board[row][c - 1]->GetPiece()->RemoveBlock(m_board[row][c - 1]);
                    m_board[row][c - 1] = nullptr;
                }
            }
        }
    }
}






void Tetris::AddScore()
{
    int num_of_filled_rows = 0;
    for (int col = 0; col < COL_SIZE; col++)
    {
        bool isRowFilled = true;
        for (int row = 0; row < ROW_SIZE; row++)
        {
            if (m_board[row][col] == nullptr)
            {
                isRowFilled = false;
                break;
            }
        }
        
        if (isRowFilled)
        {
            ++num_of_filled_rows;
            if (col >= 0 && col < COL_SIZE)
            {
                DeleteRow(col);
            }  // Check if col is within valid range
        }
    }

    switch (num_of_filled_rows)
    {
    case 1:
        m_score += 40;
        break;
    case 2:
        m_score += 100;
        break;
    case 3:
        m_score += 300;
        break;
    case 4:
        m_score += 1200;
        break;
    }
}




void Tetris::Run()
{
    std::shared_ptr<Pieces> piece = m_factory.Create(4);
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
            else
            {
                // Add the current piece to the list of dropped pieces
                for (auto block : piece->GetBlocks())
                {
                    std::pair<int, int> position = block->GetPosition();
                    m_board[position.first][position.second] = block;
                }
                
                //piece->FreeAllStates();
                m_dropped.push_back(piece);
                AddScore();
                std::cout << m_score << std::endl;
                // Create a new piece
                piece = m_factory.Create(4);
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
