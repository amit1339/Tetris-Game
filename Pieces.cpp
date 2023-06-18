#include <iostream>
#include <memory>
#include "Pieces.hpp"

Block::Block(int x, int y, sf::Color color):m_blocksize(BlockSize),m_position(x,y), m_color(color)
{}

void Block::Render(sf::RenderWindow& window)
{
    
    sf::RectangleShape block(sf::Vector2f(BlockSize, BlockSize));
    block.setFillColor(m_color);
    block.setPosition(m_position.first, m_position.second);//TODO: make sure set the correct position 
    window.draw(block);
}

void Block::SetPosition(int x, int y)
{
    m_position.first = x;
    m_position.second = y;
}

std::pair<int,int> Block::GetPosition()
{
    return m_position;
}


Pieces::Pieces(const sf::Color color):m_color(color), m_current_state(0), m_position(150,0)
{
}

Pieces::~Pieces()
{
}

std::shared_ptr<Pieces>& Block::GetPiece()
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
                blockPosition.push_back(m_shapes_vector[m_current_state][row][col]->GetPosition());
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
    
    std::pair<int,int> position = GetPosition();
    switch (direction)
    {
    case LEFT:
        SetPosition(position.first - 1, position.second);
        break;
    case RIGHT:
        SetPosition(position.first + 1, position.second);
        break;
    case DOWN:
        SetPosition(position.first, position.second + 1);
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

std::pair<int,int> Pieces::GetPosition()
{
    return m_position;
}


LPiece::LPiece():Pieces(sf::Color::White)
{
    sf::Vector2f pos = GetPosition();
    sf::Color color = GetColor();
    std::vector<std::vector<std::vector<Block*>>> vector = 
{
    {
        {new Block(pos.x, pos.y, color), nullptr, nullptr},
        {new Block(pos.x, pos.y + BlockSize, color), nullptr, nullptr},
        {new Block(pos.x, pos.y + 2 * BlockSize, color), new Block(pos.x + BlockSize, pos.y + 2 * BlockSize, color), nullptr}
    },
    {
        {nullptr, nullptr, nullptr},
        {nullptr, nullptr, new Block(pos.x + 2 * BlockSize, pos.y + BlockSize, color)},
        {new Block(pos.x , pos.y +  2 * BlockSize, color), new Block(pos.x + BlockSize, pos.y + 2 * BlockSize, color), new Block(pos.x + 2 * BlockSize, pos.y + 2 *BlockSize, color)},
    },
    {
        {nullptr, new Block(pos.x + BlockSize, pos.y, color), new Block( pos. x + 2 * BlockSize, pos.y, color)},
        {nullptr, nullptr, new Block(pos.x + 2 * BlockSize, pos.y + BlockSize, color)},
        {nullptr, nullptr, new Block( pos.x + 2 * BlockSize, pos.y + 2 * BlockSize, color)},
    },
    {
        {nullptr, nullptr, nullptr},
        {new Block(pos.x, pos.y + BlockSize, color), new Block(pos.x + BlockSize, pos.y + BlockSize, color), new Block(pos.x + 2 * BlockSize, pos.y + BlockSize, color)},
        {new Block(pos.x, pos.y + 2* BlockSize, color), nullptr, nullptr},
    }
};
    SetShape(vector);
}


JPiece::JPiece():Pieces(sf::Color::Magenta)
{
    sf::Vector2f pos = GetPosition();
    sf::Color color = GetColor();
    std::vector<std::vector<std::vector<Block*>>> vector = 
{
    {
        {nullptr, nullptr, new Block(pos.x + 2 * BlockSize, pos.y, color)},
        {nullptr, nullptr, new Block(pos.x + 2 * BlockSize, pos.y + BlockSize, color)},
        {nullptr, new Block(pos.x + BlockSize, pos.y + 2 * BlockSize, color), new Block( pos.x + 2 * BlockSize, pos.y + 2 * BlockSize, color)}
    },
    {
        {nullptr, nullptr, nullptr},
        {new Block(pos.x, pos.y + BlockSize, color),  new Block(pos.x + BlockSize, pos.y + BlockSize, color),  new Block(pos.x + 2 * BlockSize, pos.y + BlockSize, color)},
        {nullptr, nullptr, new Block(pos.x + 2 * BlockSize, pos.y +  2 * BlockSize, color)},
    },
    {
        {new Block(pos.x, pos.y, color), new Block(pos.x + BlockSize, pos.y , color), nullptr},
        {new Block(pos.x, pos.y + BlockSize, color), nullptr, nullptr},
        {new Block(pos.x , pos.y +  2 * BlockSize, color), nullptr, nullptr},
    },
    {
        {nullptr, nullptr, nullptr},
        {new Block(pos.x, pos.y + BlockSize, color), nullptr, nullptr},
        {new Block(pos.x, pos.y + 2 * BlockSize, color), new Block(pos.x + BlockSize, pos.y + 2 * BlockSize, color), new Block(pos.x + 2 * BlockSize, pos.y + 2 * BlockSize, color)},
    }
};
    
    SetShape(vector);
}


SPiece::SPiece():Pieces(sf::Color::Red)
{
    sf::Vector2f pos = GetPosition();
    sf::Color color = GetColor();
    std::vector<std::vector<std::vector<Block*>>> vector = 
{
    {
        {nullptr, nullptr, nullptr},
        {nullptr, new Block(pos.x + BlockSize, pos.y + BlockSize, color), new Block(pos.x + 2 * BlockSize, pos.y + BlockSize, color)},
        {new Block(pos.x , pos.y +  2 * BlockSize, color), new Block(pos.x + BlockSize, pos.y + 2 * BlockSize, color), nullptr}
    },
    {
        {new Block(pos.x , pos.y, color), nullptr, nullptr},
        {new Block(pos.x, pos.y + BlockSize, color), new Block(pos.x + BlockSize, pos.y + BlockSize, color), nullptr},
        {nullptr, new Block(pos.x + BlockSize, pos.y + 2 * BlockSize, color), nullptr},
    },
    {
        {nullptr, nullptr, nullptr},
        {nullptr, new Block(pos.x + BlockSize, pos.y + BlockSize, color), new Block(pos.x + 2 * BlockSize, pos.y + BlockSize, color)},
        {new Block(pos.x , pos.y +  2 * BlockSize, color), new Block(pos.x + BlockSize, pos.y + 2 * BlockSize, color), nullptr}
    },
    {
        {new Block(pos.x , pos.y, color), nullptr, nullptr},
        {new Block(pos.x, pos.y + BlockSize, color), new Block(pos.x + BlockSize, pos.y + BlockSize, color), nullptr},
        {nullptr, new Block(pos.x + BlockSize, pos.y + 2 * BlockSize, color), nullptr},
    }
};
    
    SetShape(vector);
}



ZPiece::ZPiece():Pieces(sf::Color::Green)
{
    sf::Vector2f pos = GetPosition();
    sf::Color color = GetColor();
    std::vector<std::vector<std::vector<Block*>>> vector = 
{
    {
        {nullptr, nullptr, nullptr},
        {new Block(pos.x, pos.y + BlockSize, color), new Block(pos.x + BlockSize, pos.y + BlockSize, color), nullptr},
        {nullptr, new Block(pos.x + BlockSize, pos.y + 2 * BlockSize, color), new Block(pos.x + 2* BlockSize, pos.y + 2 * BlockSize, color)}
    },
    {
        {nullptr, nullptr, new Block(pos.x + 2 * BlockSize, pos.y, color)},
        {nullptr, new Block(pos.x + BlockSize, pos.y + BlockSize, color), new Block(pos.x + 2 * BlockSize, pos.y + BlockSize, color)},
        {nullptr, new Block(pos.x + BlockSize, pos.y + 2 * BlockSize, color), nullptr},
    },
    {
        {nullptr, nullptr, nullptr},
        {new Block(pos.x, pos.y + BlockSize, color), new Block(pos.x + BlockSize, pos.y + BlockSize, color), nullptr},
        {nullptr, new Block(pos.x + BlockSize, pos.y + 2 * BlockSize, color), new Block(pos.x + 2* BlockSize, pos.y + 2 * BlockSize, color)}
    },
    {
        {nullptr, nullptr, new Block(pos.x + 2 * BlockSize, pos.y, color)},
        {nullptr, new Block(pos.x + BlockSize, pos.y + BlockSize, color), new Block(pos.x + 2 * BlockSize, pos.y + BlockSize, color)},
        {nullptr, new Block(pos.x + BlockSize, pos.y + 2 * BlockSize, color), nullptr},
    }
};
    
    SetShape(vector);
}



IPiece::IPiece():Pieces(sf::Color::Blue)
{
    sf::Vector2f pos = GetPosition();
    sf::Color color = GetColor();
    std::vector<std::vector<std::vector<Block*>>> vector = 
{
    {
        {nullptr, new Block(pos.x + BlockSize, pos.y, color), nullptr},
        {nullptr, new Block(pos.x + BlockSize, pos.y + BlockSize, color), nullptr},
        {nullptr, new Block(pos.x + BlockSize, pos.y + 2 * BlockSize, color), nullptr}
    },
    {
        {nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr},
        {new Block(pos.x , pos.y +  2 * BlockSize, color), new Block(pos.x + BlockSize, pos.y + 2 * BlockSize, color), new Block(pos.x + 2 * BlockSize, pos.y + 2 *BlockSize, color)},
    },
    {
        {nullptr, new Block(pos.x + BlockSize, pos.y, color), nullptr},
        {nullptr, new Block(pos.x + BlockSize, pos.y + BlockSize, color), nullptr},
        {nullptr, new Block(pos.x + BlockSize, pos.y + 2 * BlockSize, color), nullptr}
    },
    {
        {nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr},
        {new Block(pos.x , pos.y +  2 * BlockSize, color), new Block(pos.x + BlockSize, pos.y + 2 * BlockSize, color), new Block(pos.x + 2 * BlockSize, pos.y + 2 *BlockSize, color)},
    }
};
    
    SetShape(vector);
}



OPiece::OPiece():Pieces(sf::Color::Yellow)
{   
    sf::Vector2f pos = GetPosition();
    sf::Color color = GetColor();
    std::vector<std::vector<std::vector<Block*>>> vector = 
{
    {
        {nullptr, nullptr, nullptr},
        {new Block(pos.x, pos.y + BlockSize, color), new Block(pos.x + BlockSize, pos.y + BlockSize, color), nullptr},
        {new Block(pos.x , pos.y +  2 * BlockSize, color), new Block(pos.x + BlockSize, pos.y + 2 * BlockSize, color), nullptr}
    },
    {
        {nullptr, nullptr, nullptr},
        {new Block(pos.x, pos.y + BlockSize, color), new Block(pos.x + BlockSize, pos.y + BlockSize, color), nullptr},
        {new Block(pos.x , pos.y +  2 * BlockSize, color), new Block(pos.x + BlockSize, pos.y + 2 * BlockSize, color), nullptr}
    },
    {
        {nullptr, nullptr, nullptr},
        {new Block(pos.x, pos.y + BlockSize, color), new Block(pos.x + BlockSize, pos.y + BlockSize, color), nullptr},
        {new Block(pos.x , pos.y +  2 * BlockSize, color), new Block(pos.x + BlockSize, pos.y + 2 * BlockSize, color), nullptr}
    },
    {
        {nullptr, nullptr, nullptr},
        {new Block(pos.x, pos.y + BlockSize, color), new Block(pos.x + BlockSize, pos.y + BlockSize, color), nullptr},
        {new Block(pos.x , pos.y +  2 * BlockSize, color), new Block(pos.x + BlockSize, pos.y + 2 * BlockSize, color), nullptr}
    }
};
    
    SetShape(vector);
}


TPiece::TPiece():Pieces(sf::Color::Cyan)
{
    sf::Vector2f pos = GetPosition();
    sf::Color color = GetColor();
    std::vector<std::vector<std::vector<Block*>>> vector = 
{
    {
        {nullptr, nullptr, nullptr},
        {nullptr, new Block(pos.x + BlockSize, pos.y + BlockSize, color), nullptr},
        {new Block(pos.x , pos.y +  2 * BlockSize, color), new Block(pos.x + BlockSize, pos.y + 2 * BlockSize, color), new Block(pos.x + 2 * BlockSize, pos.y + 2 *BlockSize, color)}
    },
    {
        {nullptr, nullptr, new Block(pos.x + 2 *BlockSize, pos.y, color)},
        {nullptr, new Block(pos.x + BlockSize, pos.y + BlockSize, color), new Block(pos.x + 2 * BlockSize, pos.y + BlockSize, color)},
        {nullptr, nullptr, new Block( pos.x + 2 * BlockSize, pos.y + 2 * BlockSize, color)},
    },
    {
        {nullptr, nullptr, nullptr},
        {new Block(pos.x, pos.y + BlockSize, color), new Block(pos.x + BlockSize, pos.y + BlockSize, color), new Block(pos.x + 2 * BlockSize, pos.y + BlockSize, color)},
        {nullptr, new Block(pos.x + BlockSize, pos.y + 2 * BlockSize, color), nullptr}
    },
    {
        {new Block(pos.x , pos.y, color), nullptr, nullptr},
        {new Block(pos.x, pos.y + BlockSize, color), new Block(pos.x + BlockSize, pos.y + BlockSize, color), nullptr},
        {new Block(pos.x , pos.y +  2 * BlockSize, color), nullptr, nullptr},
    }
};
    
    SetShape(vector);
}

