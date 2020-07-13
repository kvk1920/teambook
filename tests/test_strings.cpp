#include "test_tools.hpp"

#include <ngu_teambook/strings/hash.hpp>
#include <ngu_teambook/strings/suffix_array.hpp>
#include <ngu_teambook/strings/suffix_tree.hpp>

namespace strings = ngu_teambook::strings;

void TestHash(fs::path in, fs::path out)
{
    using namespace std;
    using ll = int64_t;
    using Hash = strings::Hash<2>;
    ifstream fin(in);
    string s;
    int q;
    fin >> s >> q;
    Hash::Init(s.size(), {
        pair<ll, ll>{137, 1000000007},
        pair<ll, ll>{143, 1000000009},
    });
    Hash h(s);
    ifstream fout(out);
    vector<string> your_result(q);
    vector<string> true_result(q);
    for (int i(0); i < q; ++i)
    {
        int l1, r1, l2, r2;
        fin >> l1 >> r1 >> l2 >> r2;
        --l1, --l2;
        your_result[i] = (h.Substr(l1, r1) == h.Substr(l2, r2) ? "Yes" : "No");
        fout >> true_result[i];
    }
    EXPECT_EQ_VECTORS(your_result, true_result);
}

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
    EXPECT_EQ_VECTORS(your_result, true_result);
}

void TestLCP(fs::path in, fs::path out)
{
    using namespace std;
    int n;
    string s;
    vector<int> suffix_array;
    {
        ifstream fin(in);
        fin >> n >> s;
        suffix_array.resize(n);
        for (int& x : suffix_array) { fin >> x; --x; }
    }
    auto your_result(strings::BuildLCP(s, suffix_array));
    vector<int> true_result(n - 1);
    {
        ifstream fin(out);
        for (int& x : true_result) fin >> x;
    }
    EXPECT_EQ_VECTORS(your_result, true_result);
}

void TestSuffixTree(fs::path in, fs::path out)
{
    using namespace std;
    using namespace strings;
    string s;
    ifstream(in) >> s;
    SuffixTree tree(1);
    tree.AddString(s);
    vector<array<int, 3>> your_ans, true_ans;
    {
        ifstream fin(out);
        int n;
        fin >> n;
        true_ans.resize(n - 1);
        for (auto& v : true_ans) for (auto& param : v) fin >> param;
    }
    {
        int n(tree.vertices.size());
        your_ans.reserve(n - 1);
        int counter(-1);
        vector<int> num(n);
        std::vector<int> stck;
        stck.reserve(n);
        stck.push_back(0);
        while (!stck.empty())
        {
            int v(stck.back());
            stck.pop_back();

            num[v] = ++counter;
            if (v)
            {
                int l(tree.vertices[v].edge.data() - tree.all_strings[0].data());
                int r(l + tree.vertices[v].edge.size());
                your_ans.push_back({num[tree.vertices[v].parent], l, r});
            }
            for (auto it(tree.vertices[v].nxt.rbegin()); it != tree.vertices[v].nxt.rend(); ++it)
                stck.push_back(it->second);
        }
    }
    EXPECT_EQ(your_ans.size(), true_ans.size());
    Hash<2>::Init(s.size(), {pair<int64_t, int64_t>{137, 1000000009}, {143, 1000000007}});
    Hash<2> h(s);
    if (your_ans.size() == true_ans.size())
    {
        for (int i(0); i < your_ans.size(); ++i)
        {
            EXPECT_EQ(your_ans[i][0], true_ans[i][0]);
            auto your_hash(h.Substr(your_ans[i][1], your_ans[i][2]));
            auto true_hash(h.Substr(true_ans[i][1], true_ans[i][2]));
            EXPECT_EQ(your_hash, true_hash);
            if (your_hash != true_hash or your_ans[i][0] != true_ans[i][0])
                break;
        }
    }
}

std::tuple<const char*, fs::path, std::function<void(fs::path, fs::path)>> test_suits[] = {
        //{"SuffixArray", "strings/suffix_array", TestSuffixArray},
        //{"LCP", "strings/lcp", TestLCP},
        //{"Hash", "strings/hash", TestHash},
        {"SuffixTree", "strings/suffix_tree", TestSuffixTree},
};

int main(int argc, char** argv)
{
    for (auto args : test_suits)
        std::apply(RegisterTests, args);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}