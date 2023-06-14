#include "PiecesFactory.hpp"


PiecesFactory::PiecesFactory()
{
    Add(0, []() { return std::make_shared<LPiece>(); });
    Add(1, []() { return std::make_shared<JPiece>(); });
    Add(2, []() { return std::make_shared<SPiece>(); });
    Add(3, []() { return std::make_shared<ZPiece>(); });
    Add(4, []() { return std::make_shared<IPiece>(); });
    Add(5, []() { return std::make_shared<OPiece>(); });
    Add(6, []() { return std::make_shared<TPiece>(); });
}

void PiecesFactory::Add(int key, std::function<std::shared_ptr<Pieces>()> create)
{
    m_map[key] = create;
}

std::shared_ptr<Pieces> PiecesFactory::Create(int key) const
{
    auto it = m_map.find(key);
    if (it != m_map.end())
    {
        return (it->second)();
    }
    return nullptr;
}