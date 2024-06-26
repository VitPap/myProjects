#include <iostream>
#include <gtest/gtest.h>
#include "Lib/IndexBuilder.cpp"
#include "Lib/IndexSearch.cpp"

using namespace std;

TEST(SearchEngineTests, build_1) {
    IndexBuilder idx;
    idx.build_index(
            "C:\\Vitaly\\myProjects\\cpp\\labwork11\\example",
            "C:\\Vitaly\\myProjects\\cpp\\labwork11\\index\\");



}
TEST(SearchEngineTests, build_2) {
    IndexBuilder idx;
    idx.build_index(
"C:\\Vitaly\\myProjects\\cpp\\labwork11",
            "C:\\Vitaly\\myProjects\\cpp\\labwork11\\index\\");
}

TEST(SearchEngineTests, invalid_query_1) {
    IndexBuilder idx;
    idx.build_index(
            "C:\\Vitaly\\myProjects\\cpp\\labwork11\\example",
            "C:\\Vitaly\\myProjects\\cpp\\labwork11\\index\\");

    IndexSearch idx_search;
    try {
        auto result = idx_search.SearchDoc("(gram and grusha)", "C:\\Vitaly\\myProjects\\cpp\\labwork11\\index\\");
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("incorrect query"));
    }
}

TEST(SearchEngineTests, invalid_query_2) {
    IndexBuilder idx;
    idx.build_index(
            "C:\\Vitaly\\myProjects\\cpp\\labwork11\\example",
            "C:\\Vitaly\\myProjects\\cpp\\labwork11\\index\\");

    IndexSearch idx_search;
    try {
        auto result = idx_search.SearchDoc("gram OR grusha )", "C:\\Vitaly\\myProjects\\cpp\\labwork11\\index\\");
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("incorrect query"));
    }
}
TEST(SearchEngineTests, invalid_query_3) {
    IndexBuilder idx;
    idx.build_index(
            "C:\\Vitaly\\myProjects\\cpp\\labwork11\\example",
            "C:\\Vitaly\\myProjects\\cpp\\labwork11\\index\\");

    IndexSearch idx_search;
    try {
        auto result = idx_search.SearchDoc("(gram OR and grusha)", "C:\\Vitaly\\myProjects\\cpp\\labwork11\\index\\");
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("incorrect query"));
    }
}
TEST(SearchEngineTests, invalid_query_4) {
    IndexBuilder idx;
    idx.build_index(
            "C:\\Vitaly\\myProjects\\cpp\\labwork11\\example",
            "C:\\Vitaly\\myProjects\\cpp\\labwork11\\index\\");

    IndexSearch idx_search;
    try {
        auto result = idx_search.SearchDoc("(gram AND grusha", "C:\\Vitaly\\myProjects\\cpp\\labwork11\\index\\");
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("incorrect query"));
    }
}
TEST(SearchEngineTests, invalid_query_5) {
    IndexBuilder idx;
    idx.build_index(
            "C:\\Vitaly\\myProjects\\cpp\\labwork11\\example",
            "C:\\Vitaly\\myProjects\\cpp\\labwork11\\index\\");

    IndexSearch idx_search;
    try {
        auto result = idx_search.SearchDoc("gram (AND maiqw)", "C:\\Vitaly\\myProjects\\cpp\\labwork11\\index\\");
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("incorrect query"));
    }
}

TEST(SearchEngineTests, query_1) {
    IndexBuilder idx;
    idx.build_index(
            "C:\\Vitaly\\myProjects\\cpp\\labwork11\\example",
            "C:\\Vitaly\\myProjects\\cpp\\labwork11\\index\\");

    IndexSearch idx_seacrh;
    auto result = idx_seacrh.SearchDoc("(gram AND grusha)", "C:\\Vitaly\\myProjects\\cpp\\labwork11\\index\\");

    ASSERT_EQ(result.str(), "Required documents don`t exists");
}
TEST(SearchEngineTests, query_2) {
    IndexBuilder idx;
    idx.build_index(
            "C:\\Vitaly\\myProjects\\cpp\\labwork11\\example",
            "C:\\Vitaly\\myProjects\\cpp\\labwork11\\index\\");
    IndexSearch idx_seacrh;
    auto result = idx_seacrh.SearchDoc("(gram AND vector)", "C:\\Vitaly\\myProjects\\cpp\\labwork11\\index\\");

    ASSERT_EQ(result.str(), "Required documents don`t exists");
}
TEST(SearchEngineTests, query_3) {
    IndexBuilder idx;
    idx.build_index(
            "C:\\Vitaly\\myProjects\\cpp\\labwork11\\example",
            "C:\\Vitaly\\myProjects\\cpp\\labwork11\\index\\");
    IndexSearch idx_seacrh;
    auto result = idx_seacrh.SearchDoc("(gram OR same)", "C:\\Vitaly\\myProjects\\cpp\\labwork11\\index\\");

    ASSERT_EQ(result.str(),
                    "Path to document: \"C:\\\\Vitaly\\\\myProjects\\\\cpp\\\\labwork11\\\\example\\\\462\\\\reviws.txt\" 2.541\n"
                    "same : 128 189 189 \n"
                    "Path to document: \"C:\\\\Vitaly\\\\myProjects\\\\cpp\\\\labwork11\\\\example\\\\y34\\\\passport.txt\" 1.45844\n"
                    "gram : 3 \n"
                    "Path to document: \"C:\\\\Vitaly\\\\myProjects\\\\cpp\\\\labwork11\\\\example\\\\passport.txt\" 1.45844\n"
                    "gram : 3 \n"
                    "Path to document: \"C:\\\\Vitaly\\\\myProjects\\\\cpp\\\\labwork11\\\\example\\\\y34\\\\exasd.txt\" 1.44957\n"
                    "gram : 5 \n"
                    "Path to document: \"C:\\\\Vitaly\\\\myProjects\\\\cpp\\\\labwork11\\\\example\\\\exasd.txt\" 1.44957\n"
                    "gram : 5 \n"
                    "Path to document: \"C:\\\\Vitaly\\\\myProjects\\\\cpp\\\\labwork11\\\\example\\\\5sdfv\\\\asdbq1.txt\" 1.4408\n"
                    "gram : 3 \n"
                    "Path to document: \"C:\\\\Vitaly\\\\myProjects\\\\cpp\\\\labwork11\\\\example\\\\462\\\\asdvqwb\\\\gomel.txt\" 1.43214\n"
                    "gram : 3 \n"
                    "Path to document: \"C:\\\\Vitaly\\\\myProjects\\\\cpp\\\\labwork11\\\\example\\\\5sdfv\\\\asdbq.txt\" 1.40676\n"
                    "gram : 10 \n"
                    "Path to document: \"C:\\\\Vitaly\\\\myProjects\\\\cpp\\\\labwork11\\\\example\\\\462\\\\asdvqwb\\\\asd.txt\" 1.3985\n"
                    "gram : 5 \n");
}
TEST(SearchEngineTests, query_4) {
    IndexBuilder idx;
    idx.build_index(
            "C:\\Vitaly\\myProjects\\cpp\\labwork11\\example",
            "C:\\Vitaly\\myProjects\\cpp\\labwork11\\index\\");

    IndexSearch idx_seacrh;
    auto result = idx_seacrh.SearchDoc("(go AND back) OR asd", "C:\\Vitaly\\myProjects\\cpp\\labwork11\\index\\");

    ASSERT_EQ(result.str(),
              "Path to document: \"C:\\\\Vitaly\\\\myProjects\\\\cpp\\\\labwork11\\\\example\\\\462\\\\reviws.txt\" 4.07701\n"
              "go : 94 \n"
              "back : 106 150 150 225 302 302 \n"
              "Path to document: \"C:\\\\Vitaly\\\\myProjects\\\\cpp\\\\labwork11\\\\example\\\\462\\\\qbq.txt\" 2.23541\n"
              "asd : 2 \n");
}
