#include <iostream>
#include "Pieces.hpp"

Block::Block(int x, int y, sf::Color color):m_blocksize(BlockSize),m_position(x,y), m_color(color)
{}

void Block::Render(sf::RenderWindow& window)
{
    sf::RectangleShape block(sf::Vector2f(BlockSize, BlockSize));
    block.setFillColor(m_color);
    block.setPosition(m_position.x, m_position.y);
    window.draw(block);
}

void Block::SetPosition(int x, int y)
{
    m_position.x += x;
    m_position.y += y;
}

sf::Vector2f Block::GetPosition()
{
    return m_position;
}

bool Block::CheckCollision(const Block& other) //checks only y axis for now
{
    if (m_position.y + BlockSize == other.m_position.y && m_position.x  == other.m_position.x)
    {
        return true;
    }
    return false;
}

Pieces::Pieces(const sf::Color color):m_color(color), m_current_state(0), m_position(150,0)
{
}

Pieces::~Pieces()
{
}

std::vector<std::vector<Block *>> Pieces::GetState()
{
    return m_state[m_current_state];
}


void Pieces::SetPosition(int x, int y)
{
    for (int row = 0; row < PIECE_SIZE; row++) 
    {
        for (int col = 0; col < PIECE_SIZE; col++) 
        {
            if ((m_state[0])[row][col] != nullptr) 
            {
                m_state[0][row][col]->SetPosition(x,y);
            }
            if ((m_state[1])[row][col] != nullptr) 
            {
                m_state[1][row][col]->SetPosition(x,y);
            }
            if ((m_state[2])[row][col] != nullptr) 
            {
                m_state[2][row][col]->SetPosition(x,y);
            }
            if ((m_state[3])[row][col] != nullptr) 
            {
                m_state[3][row][col]->SetPosition(x,y);
            }
            
        }
    }
}


void Pieces::SetShape(std::vector<std::vector<std::vector<Block*>>> state)
{
    m_state = state;
}


void Pieces::Render(sf::RenderWindow& window)
{
    for (int row = 0; row < PIECE_SIZE; row++) 
    {
        for (int col = 0; col < PIECE_SIZE; col++) 
        {
            if ((m_state[m_current_state])[row][col] != nullptr) 
            {
                m_state[m_current_state][row][col]->Render(window);
            }
        }
    }
}

sf::Color Pieces::GetColor()const
{
    return m_color;
}

void Pieces::Rotate(Direction direction)
{
    if (direction == LEFT)
    {
        m_current_state = (m_current_state - 1) % NumOfShapes;
    }
    else
    {
        m_current_state = (m_current_state + 1) % NumOfShapes;
    }
}

void Pieces::Move(Direction direction)
{

    if (m_position.x >= 10 && direction == LEFT)
    {
        SetPosition(-BlockSize, 0);
        m_position.x -= BlockSize;
    }

    else if (m_position.x <= 275 && direction == RIGHT)
    {
        SetPosition(BlockSize, 0);
        m_position.x += BlockSize;
    }

    else if (direction == DOWN)
    {
        SetPosition(0, BlockSize);
        m_position.y += BlockSize;
    }
}

sf::Vector2f Pieces::GetPosition()
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

