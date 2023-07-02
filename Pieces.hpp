#ifndef __PIECES_HPP__
#define __PIECES_HPP__

#include <SFML/Graphics.hpp>
#include <vector>

enum Direction {
    LEFT,
    RIGHT,
    DOWN,
    ROTATE_LEFT,
    ROTATE_RIGHT
    };

const int COL_SIZE = 19;
const int ROW_SIZE = 14;

const int BlockSize = 25;
const size_t NumOfShapes = 4;

class Block;
class Pieces;
typedef std::shared_ptr<Block> BOARD[ROW_SIZE][COL_SIZE];

class Block
{
public:
    Block(int x, int y, sf::Color color, Pieces *piece);
    void Render(sf::RenderWindow& window);
    void SetPosition(int x, int y);
    std::pair<int,int> GetPosition();
    void SetColor(sf::Color color);
    std::shared_ptr<Pieces> GetPiece();
private:
    const int m_blocksize;
    std::pair<int,int> m_position;
    sf::Color m_color;
    std::shared_ptr<Pieces> m_piece;
};

class Pieces
{
public:
    friend class Tetris;
    Pieces(const sf::Color color, int matrix_size=3);
    virtual ~Pieces();
    void Move(Direction direction, BOARD& board);
    void SetPosition(int x, int y);
    void RemoveBlock(std::shared_ptr<Block> &block);
    sf::Color GetColor() const;
    size_t GetCurrentState() const;
    void Render(sf::RenderWindow &window);
    void SetShape(std::vector<std::vector<std::shared_ptr<Block>>> state);
    std::vector<std::shared_ptr<Block>> GetBlocks();
    void FreeAllStates();

private:
    sf::Color m_color;
    std::vector<std::vector<std::shared_ptr<Block>>> m_shapes_vector;
    size_t m_current_state;
    int m_matrix_size;
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