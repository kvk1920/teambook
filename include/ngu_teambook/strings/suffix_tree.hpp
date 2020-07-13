#pragma once

#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace ngu_teambook::strings
{

struct SuffixTree
{
    struct Position
    {
        int v, dist;
    };

    struct Vertex
    {
        std::map<char, int> nxt;
        std::string_view edge;
        int parent, link;
        explicit Vertex(std::string_view s, int parent = -1, int link = -1)
        : edge(s)
        , parent(parent)
        , link(link)
        {}
    };
    std::vector<Vertex> vertices = {Vertex("")};
    std::vector<std::string> all_strings;
    std::string_view cur_s;
    Position last_not_leaf = {0, 0};

    explicit SuffixTree(int num_of_strings = 1)
    {
        all_strings.reserve(num_of_strings);
    }

    void AddString(std::string new_s, bool reset_lnf = true);
    int GetLink(int v);
    Position GoDown(Position pos, std::string_view s);
    bool CanGo(Position pos, char c);
    int SplitEdge(Position pos);
};

}