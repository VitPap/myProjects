#include <lib/StlAdaptors.h>
#include <gtest/gtest.h>
using namespace StlAdaptors;


TEST(StlAdaptorsTestSuite, Transform_1) {
    std::vector<int> vr = {1, 2, 3, 4, 5, 6};

    auto result = vr | transform([](int x) { return x*x; });

    std::vector<int> answer = {1, 4, 9, 16, 25, 36};
    ASSERT_EQ(result, answer);
}
TEST(StlAdaptorsTestSuite, Transform_2) {
    std::string str =  "123456";

    auto result = transform(str, [](char x) { return x-1; });
    std::string answer = "012345";

    ASSERT_EQ(result, answer);
}

TEST(StlAdaptorsTestSuite, Take_1) {
    std::vector<int> vr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    auto result = vr | take(7);
    std::vector<int> answer = {1, 2, 3, 4, 5, 6, 7};

    ASSERT_EQ(result, answer);
}

TEST(StlAdaptorsTestSuite, Take_2) {
    std::string str = "abqwdqdb";

    auto result = take(str, 4);
    std::string answer = "abqw";

    ASSERT_EQ(result, answer);
}

TEST(StlAdaptorsTestSuite, Filter_1) {
    std::vector<int> vr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

    auto result = vr | filter([](int x) { return x % 4 == 3; });

    std::vector<int> answer = {3, 7, 11};

    ASSERT_EQ(result, answer);
}

TEST(StlAdaptorsTestSuite, Filter_2) {
    std::string str = "abcdefgabfgdc";
    auto result = filter(str, [](char x) { return x <= 'd'; });
    std::string answer = "abcdabdc";

    ASSERT_EQ(result, answer);
}


TEST(StlAdaptorsTestSuite, Drop_1) {

    std::vector<int> vr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto result = vr | drop(6);
    std::vector<int> answer = {7, 8, 9, 10};

    ASSERT_EQ(result, answer);
}

TEST(StlAdaptorsTestSuite, Drop_2) {

    std::string str = "abasdbqdfbasd";
    auto result = drop(str, 5);

    std::string answer = "bqdfbasd";

    ASSERT_EQ(result, answer);
}

TEST(StlAdaptorsTestSuite, Reverse_1) {
    std::vector<char> vr = {'a', '1', 'b', 'c', '4'};

    auto result = vr | reverse();

    std::vector<char> answer = {'4', 'c', 'b', '1', 'a'};

    ASSERT_EQ(result, answer);
}

TEST(StlAdaptorsTestSuite, Reverse_2) {

    std::string str = "palindrom";
    auto result = reverse(str);
    std::string answer = "mordnilap";

    ASSERT_EQ(result, answer);
}

TEST(StlAdaptorsTestSuite, Keys_1) {

    std::map<int, char> mp = {{1, 'b'}, {8, 'q'}, {3, 'e'}, {11, 'b'}, {5, 'y'}};
    auto result = mp | keys();
    std::vector<int> answer = {1, 3, 5, 8, 11};

    ASSERT_EQ(result, answer);
}

TEST(StlAdaptorsTestSuite, Keys_2) {
    std::map<std::string, char> mp = {{"1", 'b'}, {"8", 'q'}, {"3", 'e'}, {"11", 'b'}, {"5", 'y'}};

    auto result = keys(mp);
    std::vector<std::string> answer = {"1", "11", "3", "5", "8"};
    ASSERT_EQ(result, answer);
}

TEST(StlAdaptorsTestSuite, Values_1) {

    std::map<int, char> mp = {{1, 'b'}, {8, 'q'}, {3, 'e'}, {11, 'b'}, {5, 'y'}};
    auto result = mp | values();
    std::vector<char> answer = {'b', 'e', 'y', 'q', 'b'};
    ASSERT_EQ(result, answer);
}

TEST(StlAdaptorsTestSuite, Values_2) {

    std::map<std::string, char> mp = {{"1", 'b'}, {"8", 'q'}, {"3", 'e'}, {"11", 'b'}, {"5", 'y'}};
    auto result = values(mp);
    std::vector<char> answer = {'b', 'b', 'e', 'y', 'q'};

    ASSERT_EQ(result, answer);
}

TEST(StlAdaptorsTestSuite, PipeLine) {

    std::vector<int> vr = {1, 2, 3, 4, 5, 6};
    auto result = vr | transform([](int x) {return x * x;}) | reverse() | take(3);
    std::vector<int> answer = {36, 25, 16}
    ;
    ASSERT_EQ(result, answer);
}

TEST(StlAdaptorsTestSuite, Composition) {

    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    auto result = take(reverse(transform(v, [](int x) {return x * x;})), 4);
    std::vector<int> answer = {36, 25, 16, 9};
    ASSERT_EQ(result, answer);
}
