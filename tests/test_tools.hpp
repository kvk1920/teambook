#pragma once

#include <gtest/gtest.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <functional>

namespace fs = std::filesystem;

class Test : public ::testing::Test
{
public:
    explicit Test(fs::path in, fs::path out, std::function<void(fs::path, fs::path)> test_body)
    : in_(std::move(in)), out_(std::move(out)), test_body_(std::move(test_body)) {}

    void TestBody() override
    {
        test_body_(in_, out_);
    }
protected:
    fs::path in_, out_;
    std::function<void(fs::path, fs::path)> test_body_;
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

inline void RegisterTests(const char* test_suit, fs::path path, std::function<void(fs::path, fs::path)> f)
{
    auto test_names(GetTestNames(path));
    for (int i(0); i < test_names.size(); i += 2)
    {
        const auto& input(test_names[i]);
        const auto& output(test_names[i + 1]);
        std::string j(test_names[i].filename().string());
        ::testing::RegisterTest(
                test_suit, ("Test" + j).c_str(),
                nullptr, nullptr,
                __FILE__, __LINE__,
                [=]() -> Test* { return new Test(input, output, f); }
        );
    }
}