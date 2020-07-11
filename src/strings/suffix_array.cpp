#include <ngu_teambook/strings/suffix_array.hpp>

#include <algorithm>
#include <numeric>

namespace ngu_teambook::strings
{
    std::vector<int> SortCycleShifts(std::string_view s)
    {
        using namespace std;
        int n(s.size());
        vector<int> classes(n), next_classes(n);
        vector<int> sorted(n), sorted2(n);
        int num_classes(256);
        vector<int> digit_sort(num_classes, 0);
        for (char c : s) ++digit_sort[c];
        partial_sum(digit_sort.begin(), digit_sort.end(), digit_sort.begin());
        for (int i(0); i < n; ++i)
            sorted[--digit_sort[s[i]]] = i;
        classes[sorted[0]] = 0;
        num_classes = 1;
        for (int i(0); i < n; ++i)
        {
            num_classes += s[sorted[i]] != s[sorted[i - 1]];
            classes[sorted[i]] = num_classes - 1;
        }
        for (int len(1); len < n; len *= 2)
        {
            for (int i(0); i < n; ++i)
            {
                sorted2[i] = sorted[i] - len;
                if (sorted2[i] < 0) sorted2[i] += n;
            }
            digit_sort.assign(num_classes, 0);
            for (int c : classes) ++digit_sort[c];
            partial_sum(digit_sort.begin(), digit_sort.end(), digit_sort.begin());
            for (int i(n - 1); i >= 0; --i)
                sorted[--digit_sort[classes[sorted2[i]]]] = sorted2[i];
            next_classes[sorted[0]] = 0;
            num_classes = 1;
            for (int i(1); i < n; ++i)
            {
                int pos1(sorted[i] + len), pos2(sorted[i - 1] + len);
                if (pos1 >= n) pos1 -= n;
                if (pos2 >= n) pos2 -= n;
                if (classes[sorted[i]] != classes[sorted[i - 1]] or classes[pos1] != classes[pos2])
                    ++num_classes;
                next_classes[sorted[i]] = num_classes - 1;
            }
            classes.swap(next_classes);
        }
        return sorted;
    }

    std::vector<int> BuildSuffixArray(std::string s, char unique_char)
    {
        s.push_back(unique_char);
        auto result(SortCycleShifts(s));
        result.erase(result.begin());
        return result;
    }
}