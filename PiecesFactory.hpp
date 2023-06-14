#ifndef __PIECESFACTORY__
#define __PIECESFACTORY__

#include <functional> // std::function
#include <map> // std::map
#include <memory> // std::shared_ptr

#include "Pieces.hpp"

class PiecesFactory
{
public:
    PiecesFactory();
    void Add(int key, std::function<std::shared_ptr<Pieces>()> create);
    std::shared_ptr<Pieces> Create(int key) const;
private:
    std::map<int, std::function<std::shared_ptr<Pieces>()> > m_map;
};

#endif //__PIECESFACTORY__