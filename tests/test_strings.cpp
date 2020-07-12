#include "test_tools.hpp"

#include <ngu_teambook/strings/suffix_array.hpp>


namespace strings = ngu_teambook::strings;

void TestSuffixArray(fs::path in, fs::path out)
{
    using namespace std;
    string s;
    std::ifstream(in) >> s;
    vector<int> true_result(s.size());
    {
        std::ifstream fin(out);
        for (int &x : true_result) fin >> x;
    }
    auto your_result(strings::SortCycleShifts(s + char(1)));
    your_result.erase(your_result.begin());
    for (int& x : your_result) ++x;
    EXPECT_EQ(your_result.size(), true_result.size());
    if (your_result.size() == true_result.size())
        for (int i(0); i < your_result.size(); ++i)
        {
            EXPECT_EQ(your_result[i], true_result[i]);
            if (your_result[i] != true_result[i]) break;
        }
}

std::tuple<const char*, fs::path, std::function<void(fs::path, fs::path)>> test_suits[] = {
        {"SuffixArray", "strings/suffix_array", TestSuffixArray},
};

int main(int argc, char** argv)
{
    for (auto args : test_suits)
        std::apply(RegisterTests, args);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}