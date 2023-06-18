#ifndef __TETRIS_HPP__
#define __TETRIS_HPP__

#include <SFML/Graphics.hpp>
#include <map>
#include <list>
#include "PiecesFactory.hpp"

class Tetris
{
public:
    Tetris(sf::RenderWindow *window);
    bool CanMove(const std::shared_ptr<Pieces>& piece, Direction direection);
    bool CheckEndGame(const std::shared_ptr<Pieces>& piece);
    bool CheckScore();
    void Run();

private:
    sf::RenderWindow *m_window;
    sf::Clock m_clock;
    PiecesFactory m_factory;
    size_t m_score;
    std::list<std::shared_ptr<Pieces>> m_dropped;
    BOARD m_board;
    bool m_isRunning;
};



#endif //__TETRIS_HPP__