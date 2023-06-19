#include <iostream>
#include <memory>
#include "Pieces.hpp"


Block::Block(int x, int y, sf::Color color, Pieces *piece): m_blocksize(BlockSize), m_position(std::make_pair(x, y)), m_color(color), m_piece(piece)
{}

void Block::Render(sf::RenderWindow& window)
{
    sf::RectangleShape block(sf::Vector2f(BlockSize, BlockSize));
    block.setFillColor(m_color);
    block.setPosition(m_position.first * BlockSize, m_position.second * BlockSize);//TODO: make sure set the correct position 
    window.draw(block);
}

void Block::SetPosition(int x, int y)
{
    m_position.first += x;
    m_position.second += y;
}

std::pair<int,int> Block::GetPosition()
{
    return m_position;
}


Pieces::Pieces(const sf::Color color):m_color(color), m_current_state(0)
{
}

Pieces::~Pieces()
{
}

std::shared_ptr<Pieces> Block::GetPiece()
{
    return m_piece;
}

size_t Pieces::GetCurrentState() const
{
    return m_current_state;
}

std::vector<Block*> Pieces::GetBlocks()
{
    std::vector<Block *> blockPosition;

    for (int row = 0; row < ROW_SIZE; row++) 
    {
        for (int col = 0; col < COL_SIZE; col++) 
        {
            if ((m_shapes_vector[m_current_state])[row][col] != nullptr) 
            {
                blockPosition.push_back(m_shapes_vector[m_current_state][row][col]);
            }
        }
    }
    return blockPosition;
}

void Pieces::SetPosition(int x, int y)
{
    
    for (int row = 0; row < ROW_SIZE; row++) 
    {
        for (int col = 0; col < COL_SIZE; col++) 
        {
            for (auto state: m_shapes_vector)
            {
                if (state[row][col] != nullptr) 
                {
                    state[row][col]->SetPosition(x,y);
                }
            }
        }
    }
}


void Pieces::SetShape(std::vector<std::vector<std::vector<Block*>>> state)
{
    m_shapes_vector = state;
}


void Pieces::Render(sf::RenderWindow& window)
{
    for (int row = 0; row < ROW_SIZE; row++) 
    {
        for (int col = 0; col < COL_SIZE; col++) 
        {
            if ((m_shapes_vector[m_current_state])[row][col] != nullptr) 
            {
                m_shapes_vector[m_current_state][row][col]->Render(window);
            }
        }
    }
}

sf::Color Pieces::GetColor()const
{
    return m_color;
}


void Pieces::Move(Direction direction, BOARD& board)
{
    for (auto block : GetBlocks())
    {
        std::pair<int,int> position = block->GetPosition();
        board[position.first][position.second] = nullptr;
    } 
    
    switch (direction)
    {
    case LEFT:
        SetPosition(- 1, 0);
        break;
    case RIGHT:
        SetPosition(1, 0);
        break;
    case DOWN:
        SetPosition(0, 1);
        break;
    case ROTATE_LEFT:
        m_current_state = (m_current_state - 1) % NumOfShapes;
        break;
    case ROTATE_RIGHT:
        m_current_state = (m_current_state + 1) % NumOfShapes;
        break;
    }

    for (auto block : GetBlocks())
    {
        std::pair<int,int> position = block->GetPosition();
        board[position.first][position.second] = block;
    }

}




LPiece::LPiece() : Pieces(sf::Color::White)
{
    sf::Color color = GetColor();
    std::vector<std::vector<std::vector<Block*>>> vector = 
    {
        {
            {new Block(5, 0, color, this), nullptr, nullptr},
            {new Block(5, 1, color, this), nullptr, nullptr},
            {new Block(5, 2, color, this), new Block(6, 2, color, this), nullptr}
        },
        {
            {nullptr, nullptr, nullptr},
            {nullptr, nullptr, new Block(7, 1, color, this)},
            {new Block(5, 2, color, this), new Block(6, 2, color, this), new Block(7, 2, color, this)},
        },
        {
            {nullptr, new Block(6, 0, color, this), new Block(7, 0, color, this)},
            {nullptr, nullptr, new Block(7, 1, color, this)},
            {nullptr, nullptr, new Block(7, 2, color, this)},
        },
        {
            {new Block(5, 0, color, this), new Block(6, 0, color, this), new Block(7, 0, color, this)},
            {new Block(5, 1, color, this), nullptr, nullptr},
            {nullptr, nullptr, nullptr},
        }
    };
    SetShape(vector);
}



JPiece::JPiece():Pieces(sf::Color::Magenta)
{
    sf::Color color = GetColor();
    std::vector<std::vector<std::vector<Block*>>> vector = 
{
    {
        {nullptr, nullptr, new Block(7, 0, color, this)},
        {nullptr, nullptr, new Block(7, 1, color, this)},
        {nullptr, new Block(6, 2, color, this), new Block(7, 2, color, this)}
    },
    {
        {nullptr, nullptr, nullptr},
        {new Block(5, 1, color, this),  new Block(6, 1, color, this),  new Block(7, 1, color, this)},
        {nullptr, nullptr, new Block(7, 2, color, this)},
    },
    {
        {new Block(5, 0, color, this), new Block(6, 0, color, this), nullptr},
        {new Block(5, 1, color, this), nullptr, nullptr},
        {new Block(5, 2, color, this), nullptr, nullptr},
    },
    {
        {nullptr, nullptr, nullptr},
        {new Block(5, 1, color, this), nullptr, nullptr},
        {new Block(5, 2, color, this), new Block(6, 2, color, this), new Block(7, 2, color, this)},
    }
};
    
    SetShape(vector);
}


SPiece::SPiece():Pieces(sf::Color::Red)
{
    sf::Color color = GetColor();
    std::vector<std::vector<std::vector<Block*>>> vector = 
{
    {
        {nullptr, nullptr, nullptr},
        {nullptr, new Block(6, 1, color, this), new Block(7, 1, color, this)},
        {new Block(5, 2, color, this), new Block(6, 2, color, this), nullptr}
    },
    {
        {new Block(5, 0, color, this), nullptr, nullptr},
        {new Block(5, 1, color, this), new Block(6, 1, color, this), nullptr},
        {nullptr, new Block(6, 2, color, this), nullptr},
    },
    {
        {nullptr, nullptr, nullptr},
        {nullptr, new Block(6, 1, color, this), new Block(7, 1, color, this)},
        {new Block(5, 2, color, this), new Block(6, 2, color, this), nullptr}
    },
    {
        {new Block(5, 0, color, this), nullptr, nullptr},
        {new Block(5, 1, color, this), new Block(6, 1, color, this), nullptr},
        {nullptr, new Block(6, 2, color, this), nullptr},
    }
};
    
    SetShape(vector);
}



ZPiece::ZPiece():Pieces(sf::Color::Green)
{
    sf::Color color = GetColor();
    std::vector<std::vector<std::vector<Block*>>> vector = 
{
    {
        {nullptr, nullptr, nullptr},
        {new Block(5, 1, color, this), new Block(6, 1, color, this), nullptr},
        {nullptr, new Block(6, 2, color, this), new Block(7, 2, color, this)}
    },
    {
        {nullptr, nullptr, new Block(7, 0, color, this)},
        {nullptr, new Block(6, 1, color, this), new Block(7, 1, color, this)},
        {nullptr, new Block(6, 2, color, this), nullptr},
    },
    {
        {nullptr, nullptr, nullptr},
        {new Block(5, 1, color, this), new Block(6, 1, color, this), nullptr},
        {nullptr, new Block(6, 2, color, this), new Block(7, 2, color, this)}
    },
    {
        {nullptr, nullptr, new Block(7, 0, color, this)},
        {nullptr, new Block(6, 1, color, this), new Block(7, 1, color, this)},
        {nullptr, new Block(6, 2, color, this), nullptr},
    }
};
    
    SetShape(vector);
}



IPiece::IPiece():Pieces(sf::Color::Blue)
{
    sf::Color color = GetColor();
    std::vector<std::vector<std::vector<Block*>>> vector = 
{
    {
        {nullptr, new Block(6, 0, color, this), nullptr},
        {nullptr, new Block(6, 1, color, this), nullptr},
        {nullptr, new Block(6, 2, color, this), nullptr}
    },
    {
        {nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr},
        {new Block(5, 2, color, this), new Block(6, 2, color, this), new Block(7, 2, color, this)},
    },
    {
        {nullptr, new Block(6, 0, color, this), nullptr},
        {nullptr, new Block(6, 1, color, this), nullptr},
        {nullptr, new Block(6, 2, color, this), nullptr}
    },
    {
        {nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr},
        {new Block(5, 2, color, this), new Block(6, 2, color, this), new Block(7, 2, color, this)},
    }
};
    
    SetShape(vector);
}



OPiece::OPiece():Pieces(sf::Color::Yellow)
{   
    sf::Color color = GetColor();
    std::vector<std::vector<std::vector<Block*>>> vector = 
{
    {
        {nullptr, nullptr, nullptr},
        {new Block(5, 1, color, this), new Block(6, 1, color, this), nullptr},
        {new Block(5, 2, color, this), new Block(6, 2, color, this), nullptr}
    },
    {
        {nullptr, nullptr, nullptr},
        {new Block(5, 1, color, this), new Block(6, 1, color, this), nullptr},
        {new Block(5, 2, color, this), new Block(6, 2, color, this), nullptr}
    },
    {
        {nullptr, nullptr, nullptr},
        {new Block(5, 1, color, this), new Block(6, 1, color, this), nullptr},
        {new Block(5, 2, color, this), new Block(6, 2, color, this), nullptr}
    },
    {
        {nullptr, nullptr, nullptr},
        {new Block(5, 1, color, this), new Block(6, 1, color, this), nullptr},
        {new Block(5, 2, color, this), new Block(6, 2, color, this), nullptr}
    }
};
    
    SetShape(vector);
}


TPiece::TPiece():Pieces(sf::Color::Cyan)
{
    sf::Color color = GetColor();
    std::vector<std::vector<std::vector<Block*>>> vector = 
{
    {
        {nullptr, nullptr, nullptr},
        {nullptr, new Block(6, 1, color, this), nullptr},
        {new Block(5, 2, color, this), new Block(6, 2, color, this), new Block(7, 2, color, this)}
    },
    {
        {nullptr, nullptr, new Block(7, 0, color, this)},
        {nullptr, new Block(6, 1, color, this), new Block(7, 1, color, this)},
        {nullptr, nullptr, new Block(7, 2, color, this)},
    },
    {
        {nullptr, nullptr, nullptr},
        {new Block(5, 1, color, this), new Block(6, 1, color, this), new Block(7, 1, color, this)},
        {nullptr, new Block(6, 2, color, this), nullptr}
    },
    {
        {new Block(5, 0, color, this), nullptr, nullptr},
        {new Block(5, 1, color, this), new Block(6, 1, color, this), nullptr},
        {new Block(5, 2, color, this), nullptr, nullptr},
    }
};
    
    SetShape(vector);
}
