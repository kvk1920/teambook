#pragma once

#include <array>
#include <cassert>
#include <cstddef>
#include <cstring>
#include <string_view>
#include <vector>

namespace ngu_teambook::strings
{

template <std::size_t N>
class Hash
{
public:
    struct Value : public std::array<int64_t, N>
    {
        int len;
        explicit Value(int len = 0) : len(len)
        {
            std::fill(std::array<int64_t, N>::begin(), std::array<int64_t, N>::end(), 0);
        }
        Value(int len, std::array<int64_t, N> h)
        : len(len)
        , std::array<int64_t, N>(h)
        {}
        bool operator==(const Value& other) const noexcept
        {
            if (!len) return !other.len;
            return other.len == len and (static_cast<const std::array<int64_t, N>&>(*this) == static_cast<const std::array<int64_t, N>&>(other));
        }
    };

    static void Init(int max_size, std::array<std::pair<int64_t, int64_t>, N> base_mod_list)
    {
        pw_.resize(max_size);
        for (int i(0); i < N; ++i) mods_[i] = base_mod_list[i].second;
        std::fill(pw_[0].begin(), pw_[0].end(), 1);
        for (int i(1); i < max_size; ++i)
            for (int j(0); j < N; ++j)
                pw_[i][j] = pw_[i - 1][j] * base_mod_list[j].first % base_mod_list[j].second;
    }

    std::vector<std::array<int64_t, N>> h;

    explicit Hash(std::string_view s) : h(s.size())
    {
        assert(h.size() <= pw_.size());
        if (s.empty()) return;
        for (int i(0); i < N; ++i)
            h[0][i] = s[0] % mods_[i];
        for (int i(1); i < s.size(); ++i)
            for (int j(0); j < N; ++j)
                h[i][j] = (h[i - 1][j] * pw_[1][j] + s[i]) % mods_[j];
    }

    Value Substr(int l, int r) const // [l, r)
    {
        if (l == r) { return Value(0); }
        Value result{ r - l, h[r - 1]};
        if (l)
        {
            for (int i(0); i < N; ++i)
            {
                result[i] -= h[l - 1][i] * pw_[r - l][i] % mods_[i];
                if (result[i] < 0) result[i] += mods_[i];
            }
        }
        return result;
    }
private:
    static int64_t mods_[N];
    static std::vector<Value> pw_;
};

template <std::size_t N>
int64_t Hash<N>::mods_[N];
template <std::size_t N>
std::vector<typename Hash<N>::Value> Hash<N>::pw_;


}