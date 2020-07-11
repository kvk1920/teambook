#include <ngu_teambook/strings/suffix_array.hpp>

#include <gtest/gtest.h>

#include <algorithm>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;
namespace strings = ngu_teambook::strings;

class SuffixArrayTest : public ::testing::Test
{
public:
    explicit SuffixArrayTest(fs::path in, fs::path out) : in_(in), out_(out) {}

    void TestBody() override
    {
        using namespace std;
        string s;
        std::ifstream(in_) >> s;
        vector<int> true_result(s.size());
        {
            std::ifstream fin(out_);
            for (int& x : true_result) fin >> x;
        }
        auto your_result(strings::BuildSuffixArray(s));
        EXPECT_EQ(your_result.size(), true_result.size());
        if (your_result.size() == true_result.size()) for (int i(0); i < your_result.size(); ++i)
            EXPECT_EQ(your_result[i], true_result[i]);
    }
private:
    fs::path in_, out_;
};

inline std::vector<fs::path> GetTestNames(const fs::path& path)
{
    fs::directory_iterator it(path);
    std::vector<fs::path> result;
    for (const auto& entry : it)
        result.push_back(entry.path());
    std::sort(result.begin(), result.end());
    return result;
}

void RegisterSuffixArrayTests()
{
    auto test_names(GetTestNames("strings/suffix_array"));
    for (int i(0); i < test_names.size(); i += 2)
    {
        const auto& input(test_names[i]);
        const auto& output(test_names[i + 1]);
        std::string j(test_names[i].filename().string());
        ::testing::RegisterTest(
                "SuffixArray", ("Test" + j).c_str(),
                nullptr, j.c_str(),
                __FILE__, __LINE__,
                [=]() -> SuffixArrayTest* { return new SuffixArrayTest(input, output); }
                );
    }
}

int main(int argc, char** argv)
{
    RegisterSuffixArrayTests();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}