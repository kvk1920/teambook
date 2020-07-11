#pragma once

#include <string_view>
#include <vector>

namespace ngu_teambook::strings
{
    std::vector<int> BuildSuffixArray(std::string_view a);
}