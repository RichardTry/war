#ifndef TILE_CONTENT_H_INCLUDED
#define TILE_CONTENT_H_INCLUDED

#include <string>
#include <unordered_map>

class TileContent
{
    public:
        unsigned int texture;
        std::unordered_map<std::string, std::string> string_meta;
        std::unordered_map<std::string, int> int_meta;
        std::unordered_map<std::string, float> float_meta;

        TileContent();
};

#endif // TILE_CONTENT_H_INCLUDED
