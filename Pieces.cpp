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

    if (direction == LEFT)
    {
        SetPosition(-BlockSize, 0);
        m_position.x -= BlockSize;
    }

    else if (direction == RIGHT)
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
    std::vector<std::vector<std::vector<Block*>>> vector = 
{
    {
        {new Block(0,0, GetColor()), nullptr, nullptr},
        {new Block(0, BlockSize, GetColor()), nullptr, nullptr},
        {new Block(0, 2 * BlockSize, GetColor()), new Block(BlockSize, 2 * BlockSize, GetColor()), nullptr}
    },
    {
        {nullptr, nullptr, nullptr},
        {nullptr, nullptr, new Block(2 * BlockSize, BlockSize, GetColor())},
        {new Block(0, 2 * BlockSize, GetColor()), new Block(BlockSize, 2 * BlockSize, GetColor()), new Block(2 * BlockSize, 2 *BlockSize, GetColor())},
    },
    {
        {nullptr, new Block(BlockSize,0, GetColor()), new Block( 2 * BlockSize,0, GetColor())},
        {nullptr, nullptr, new Block(2 * BlockSize, BlockSize, GetColor())},
        {nullptr, nullptr, new Block(2 * BlockSize, 2 * BlockSize, GetColor())},
    },
    {
        {nullptr, nullptr, nullptr},
        {new Block(0,BlockSize, GetColor()), new Block(BlockSize,BlockSize, GetColor()), new Block(2 * BlockSize, BlockSize, GetColor())},
        {new Block(0, 2* BlockSize, GetColor()), nullptr, nullptr},
    }
};
    SetShape(vector);
}


JPiece::JPiece():Pieces(sf::Color::Magenta)
{
    std::vector<std::vector<std::vector<Block*>>> vector = 
{
    {
        {nullptr, nullptr, new Block(2 * BlockSize,0, GetColor())},
        {nullptr, nullptr, new Block(2 * BlockSize, BlockSize, GetColor())},
        {nullptr, new Block(BlockSize, 2 * BlockSize, GetColor()), new Block(2 * BlockSize, 2 * BlockSize, GetColor())}
    },
    {
        {nullptr, nullptr, nullptr},
        {new Block(0, BlockSize, GetColor()),  new Block(BlockSize, BlockSize, GetColor()),  new Block(2 * BlockSize, BlockSize, GetColor())},
        {new Block(0, 2 * BlockSize, GetColor()),nullptr, nullptr},
    },
    {
        {nullptr, new Block(BlockSize,0, GetColor()), new Block( 2 * BlockSize,0, GetColor())},
        {nullptr, nullptr, new Block(2 * BlockSize, BlockSize, GetColor())},
        {nullptr, nullptr, new Block(2 * BlockSize, 2 * BlockSize, GetColor())},
    },
    {
        {new Block(0,0, GetColor()), new Block(BlockSize,0, GetColor()), new Block(2 * BlockSize,0, GetColor())},
        {new Block(0, BlockSize, GetColor()), nullptr, nullptr},
        {nullptr, nullptr, nullptr},
    }
};
    
    SetShape(vector);
}


SPiece::SPiece():Pieces(sf::Color::Red)
{
std::vector<std::vector<std::vector<Block*>>> vector = 
{
    {
        {nullptr, nullptr, nullptr},
        {nullptr, new Block(BlockSize, BlockSize, GetColor()), new Block(2 * BlockSize, BlockSize, GetColor())},
        {new Block(0, 2 * BlockSize, GetColor()), new Block(BlockSize, 2 * BlockSize, GetColor()), nullptr}
    },
    {
        {new Block(0, 0, GetColor()), nullptr, nullptr},
        {new Block(0, BlockSize, GetColor()), new Block(BlockSize, BlockSize, GetColor()), nullptr},
        {nullptr, new Block(BlockSize, 2 * BlockSize, GetColor()), nullptr},
    },
    {
        {nullptr, nullptr, nullptr},
        {nullptr, new Block(BlockSize, BlockSize, GetColor()), new Block(2 * BlockSize, BlockSize, GetColor())},
        {new Block(0, 2 * BlockSize, GetColor()), new Block(BlockSize, 2 * BlockSize, GetColor()), nullptr}
    },
    {
        {new Block(0, 0, GetColor()), nullptr, nullptr},
        {new Block(0, BlockSize, GetColor()), new Block(BlockSize, BlockSize, GetColor()), nullptr},
        {nullptr, new Block(BlockSize, 2 * BlockSize, GetColor()), nullptr},
    }
};
    
    SetShape(vector);
}



ZPiece::ZPiece():Pieces(sf::Color::Green)
{
   std::vector<std::vector<std::vector<Block*>>> vector = 
{
    {
        {nullptr, nullptr, nullptr},
        {new Block(0, BlockSize, GetColor()), new Block(BlockSize, BlockSize, GetColor()), nullptr},
        {nullptr, new Block(BlockSize, 2 * BlockSize, GetColor()), new Block(2* BlockSize, 2 * BlockSize, GetColor())}
    },
    {
        {nullptr, nullptr, new Block(2 * BlockSize, 0, GetColor())},
        {nullptr, new Block(BlockSize, BlockSize, GetColor()), new Block(2 * BlockSize, BlockSize, GetColor())},
        {nullptr, new Block(BlockSize, 2 * BlockSize, GetColor()), nullptr},
    },
    {
        {nullptr, nullptr, nullptr},
        {new Block(0, BlockSize, GetColor()), new Block(BlockSize, BlockSize, GetColor()), nullptr},
        {nullptr, new Block(BlockSize, 2 * BlockSize, GetColor()), new Block(2* BlockSize, 2 * BlockSize, GetColor())}
    },
    {
        {nullptr, nullptr, new Block(2 * BlockSize, 0, GetColor())},
        {nullptr, new Block(BlockSize, BlockSize, GetColor()), new Block(2 * BlockSize, BlockSize, GetColor())},
        {nullptr, new Block(BlockSize, 2 * BlockSize, GetColor()), nullptr},
    }
};
    
    SetShape(vector);
}



IPiece::IPiece():Pieces(sf::Color::Blue)
{
    std::vector<std::vector<std::vector<Block*>>> vector = 
{
    {
        {nullptr, new Block(BlockSize, 0, GetColor()), nullptr},
        {nullptr, new Block(BlockSize, BlockSize, GetColor()), nullptr},
        {nullptr, new Block(BlockSize, 2 * BlockSize, GetColor()), nullptr}
    },
    {
        {nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr},
        {new Block(0, 2 * BlockSize, GetColor()), new Block(BlockSize, 2 * BlockSize, GetColor()), new Block(2 * BlockSize, 2 *BlockSize, GetColor())},
    },
    {
        {nullptr, new Block(BlockSize, 0, GetColor()), nullptr},
        {nullptr, new Block(BlockSize, BlockSize, GetColor()), nullptr},
        {nullptr, new Block(BlockSize, 2 * BlockSize, GetColor()), nullptr}
    },
    {
        {nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr},
        {new Block(0, 2 * BlockSize, GetColor()), new Block(BlockSize, 2 * BlockSize, GetColor()), new Block(2 * BlockSize, 2 *BlockSize, GetColor())},
    }
};
    
    SetShape(vector);
}



OPiece::OPiece():Pieces(sf::Color::Yellow)
{   
    std::vector<std::vector<std::vector<Block*>>> vector = 
{
    {
        {nullptr, nullptr, nullptr},
        {new Block(0, BlockSize, GetColor()), new Block(BlockSize, BlockSize, GetColor()), nullptr},
        {new Block(0, 2 * BlockSize, GetColor()), new Block(BlockSize, 2 * BlockSize, GetColor()), nullptr}
    },
    {
        {nullptr, nullptr, nullptr},
        {new Block(0, BlockSize, GetColor()), new Block(BlockSize, BlockSize, GetColor()), nullptr},
        {new Block(0, 2 * BlockSize, GetColor()), new Block(BlockSize, 2 * BlockSize, GetColor()), nullptr}
    },
    {
        {nullptr, nullptr, nullptr},
        {new Block(0, BlockSize, GetColor()), new Block(BlockSize, BlockSize, GetColor()), nullptr},
        {new Block(0, 2 * BlockSize, GetColor()), new Block(BlockSize, 2 * BlockSize, GetColor()), nullptr}
    },
    {
        {nullptr, nullptr, nullptr},
        {new Block(0, BlockSize, GetColor()), new Block(BlockSize, BlockSize, GetColor()), nullptr},
        {new Block(0, 2 * BlockSize, GetColor()), new Block(BlockSize, 2 * BlockSize, GetColor()), nullptr}
    }
};
    
    SetShape(vector);
}


TPiece::TPiece():Pieces(sf::Color::Cyan)
{
    std::vector<std::vector<std::vector<Block*>>> vector = 
{
    {
        {nullptr, nullptr, nullptr},
        {nullptr, new Block(BlockSize, BlockSize, GetColor()), nullptr},
        {new Block(0, 2 * BlockSize, GetColor()), new Block(BlockSize, 2 * BlockSize, GetColor()), new Block(2 * BlockSize, 2 *BlockSize, GetColor())}
    },
    {
        {nullptr, nullptr, new Block(2 *BlockSize, 0, GetColor())},
        {nullptr, new Block(BlockSize, BlockSize, GetColor()), new Block(2 * BlockSize, BlockSize, GetColor())},
        {nullptr, nullptr, new Block(2 * BlockSize, 2 * BlockSize, GetColor())},
    },
    {
        {nullptr, nullptr, nullptr},
        {new Block(0, BlockSize, GetColor()), new Block(BlockSize, BlockSize, GetColor()), new Block(2 * BlockSize, BlockSize, GetColor())},
        {nullptr, new Block(BlockSize, 2 * BlockSize, GetColor()), nullptr}
    },
    {
        {new Block(0, 0, GetColor()), nullptr, nullptr},
        {new Block(0, BlockSize, GetColor()), new Block(BlockSize, BlockSize, GetColor()), nullptr},
        {new Block(0, 2 * BlockSize, GetColor()), nullptr, nullptr},
    }
};
    
    SetShape(vector);
}

