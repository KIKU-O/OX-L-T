#pragma once
#include "Figure.h"
class Tile : public Object
{
private:
    static unsigned int Counter;
public:
    unsigned int ID = 0;
    enum Occupation
    {
        FREE,
        OCCUPIED_BY_WHITE,
        OCCUPIED_BY_BLACK
    } gOccupation = Occupation::FREE;
    enum Type
    {
        STANDART,
        TOP_EDGE,
        BOTTOM_EDGE
    } gType = Type::STANDART;
public:
    Tile(const std::string& tName, const oxygine::Resources& tResources, const oxygine::Vector2& tOffset, const oxygine::Vector2& tSize, Tile::Color tColor = Tile::Color::BLACK, Tile::Occupation tOccupation = Tile::Occupation::OCCUPIED_BY_BLACK);
    ~Tile();
};