#pragma once

#include <string_view>
#include <vector>

namespace ngu_teambook::strings
{
    std::vector<int> SortCycleShifts(std::string_view a);
    std::vector<int> BuildLCP(std::string_view a, const std::vector<int>& suffix_array);
}