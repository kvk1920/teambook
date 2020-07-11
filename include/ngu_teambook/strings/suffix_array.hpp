#pragma once

#include <string_view>
#include <vector>

namespace ngu_teambook::strings
{
    std::vector<int> SortCycleShifts(std::string_view a);
    std::vector<int> BuildSuffixArray(std::string s, char unique_char = char(1));
}