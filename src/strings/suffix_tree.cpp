#include <ngu_teambook/strings/suffix_tree.hpp>

using namespace std;

namespace ngu_teambook::strings
{

using Position = SuffixTree::Position;

Position SuffixTree::GoDown(Position pos, string_view s)
{
    while (!s.empty())
    {
        if (!pos.dist)
        {
            int v(vertices[pos.v].nxt[s[0]]);
            pos.v = v;
            pos.dist = vertices[v].edge.size();
        }
        else if (pos.dist <= s.size())
        {
            s.remove_prefix(pos.dist);
            pos.dist = 0;
        }
        else
        {
            pos.dist -= s.size();
            break;
        }
    }
    return pos;
}

namespace
{
inline string_view GetSuffix(string_view s, int n)
{
    return s.substr(s.size() - n);
}
}

int SuffixTree::GetLink(int v)
{
    if (auto link(vertices[v].link); link != -1)
        return link;
    Position link_pos;
    if (!vertices[v].parent)
    {
        auto path(vertices[v].edge);
        path.remove_prefix(1);
        link_pos = GoDown({0, 0}, path);
    }
    else
        link_pos = GoDown({GetLink(vertices[v].parent), 0}, vertices[v].edge);
    int link(SplitEdge(link_pos));
    return link;
}

int SuffixTree::SplitEdge(Position pos)
{
    if (!pos.dist) return pos.v;
    int v(pos.v); // child
    int u(vertices.size()); // new vertex
    int p(vertices[v].parent); // parent
    auto first_part(vertices[v].edge);
    first_part.remove_suffix(pos.dist);
    auto second_part(GetSuffix(vertices[v].edge, pos.dist));
    auto& vertex(vertices.emplace_back(first_part, p));
    vertex.nxt.emplace(second_part[0], v);
    vertices[v].parent = u;
    vertices[v].edge = second_part;
    vertices[p].nxt[first_part[0]] = u;
    return u;
}

bool SuffixTree::CanGo(Position pos, const char c)
{
    if (pos.dist)
    {
        return c == *(vertices[pos.v].edge.end() - pos.dist);
    }
    auto it(vertices[pos.v].nxt.find(c));
    if (it != end(vertices[pos.v].nxt))
        return true;
    return false;
}

void SuffixTree::AddString(string new_s, bool reset_lnf)
{
    vertices.reserve(vertices.size() + 2 * new_s.size());
    if (reset_lnf)
    {
        last_not_leaf = {0, 0};
        all_strings.emplace_back(move(new_s));
    }
    else
    {
        all_strings.back() += new_s;
    }
    cur_s = all_strings.back();
    int inf(cur_s.size());
    for (int i(0); i < inf; ++i)
    {
        char c(cur_s[i]);
        bool stay_in_root(false);
        while (!CanGo(last_not_leaf, c))
        {
            int v(SplitEdge(last_not_leaf));
            int u;
            if (!v)
            {
                stay_in_root = true;
                u = 0;
            }
            else
            {
                vertices[v].link = GetLink(v);
                u = vertices[v].link;
            }
            vertices[v].nxt.emplace(c, vertices.size());
            auto& leaf = vertices.emplace_back(cur_s.substr(i), v);
            last_not_leaf = {u, 0};
        }
        if (!stay_in_root)
        {
            last_not_leaf = GoDown(last_not_leaf, cur_s.substr(i, 1));
        }
    }
}

}