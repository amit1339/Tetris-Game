#ifndef __PIECES_HPP__
#define __PIECES_HPP__

#include <SFML/Graphics.hpp>
#include <vector>

enum Direction {
    LEFT,
    RIGHT,
    DOWN
    };

const int ROW_SIZE = 3;
const int COL_SIZE = 3;
const int BlockSize = 25;
const size_t NumOfShapes = 4;

class Block
{
public:
    Block(int x, int y, sf::Color color);
    void Render(sf::RenderWindow& window);
    void SetPosition(int x, int y);
    bool CheckCollision(const Block& other);
    sf::Vector2f GetPosition();
private:
    const int m_blocksize;
    sf::Vector2f m_position;
    sf::Color m_color;
};


class Pieces
{
public:
    friend class Tetris;
    Pieces(const sf::Color color);
    virtual ~Pieces();
    void Move(Direction direction);
    void Rotate(Direction direction);
    void SetPosition(int x, int y);
    sf::Color GetColor() const;
    std::vector<std::vector<Block *>> GetState();
    sf::Vector2f GetPosition();
    void Render(sf::RenderWindow &window);
    void SetShape(std::vector<std::vector<std::vector<Block*>>> state);
    std::vector<sf::Vector2f> GetBlockPositions();
private:
    sf::Color m_color;
    std::vector<std::vector<std::vector<Block*>>> m_state;
    size_t m_current_state;
    sf::Vector2f m_position;
};

class LPiece : public Pieces
{
public:
    LPiece();
};


class JPiece : public Pieces
{
public:
    JPiece();
};


class SPiece : public Pieces
{
public:
    SPiece();
};


class ZPiece : public Pieces
{
public:
    ZPiece();
};


class IPiece : public Pieces
{
public:
    IPiece();
};


class OPiece : public Pieces
{
public:
    OPiece();
};


class TPiece : public Pieces
{
public:
    TPiece();
};


#endif //__PIECES_H__ 