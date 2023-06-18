#ifndef __PIECES_HPP__
#define __PIECES_HPP__

#include <SFML/Graphics.hpp>
#include <vector>

typedef Block* BOARD[10][20];

enum Direction {
    LEFT,
    RIGHT,
    DOWN,
    ROTATE_LEFT,
    ROTATE_RIGHT
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
    //bool CheckCollision(const Block& other);
    std::pair<int,int> GetPosition();
    std::shared_ptr<Pieces>& Block::GetPiece();
private:
    const int m_blocksize;
    std::pair<int,int> m_position;
    sf::Color m_color;
    std::shared_ptr<Pieces>& m_piece;
};


class Pieces
{
public:
    friend class Tetris;
    Pieces(const sf::Color color);
    virtual ~Pieces();
    void Move(Direction direction, BOARD& board);
    void SetPosition(int x, int y);
    sf::Color GetColor() const;
    size_t GetCurrentState() const;
    std::pair<int,int> GetPosition();
    void Render(sf::RenderWindow &window);
    void SetShape(std::vector<std::vector<std::vector<Block*>>> state);
    std::vector<Block *> GetBlocks();
private:
    sf::Color m_color;
    std::vector<std::vector<std::vector<Block*>>> m_shapes_vector;
    size_t m_current_state;
    std::pair<int,int> m_position;
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