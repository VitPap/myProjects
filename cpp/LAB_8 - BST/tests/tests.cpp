#include "tests.h"

using namespace std;

TEST(BinarySearchTreeTestSuite, empty1) {
    BinarySearchTree<int> tree(tree_type::post_order);
    
    ASSERT_EQ(tree.empty(), true);
}

TEST(BinarySearchTreeTestSuite, empty2) {
    BinarySearchTree<int> tree(tree_type::post_order);

    tree.Insert(1);
    tree.Insert(2);
    ASSERT_EQ(tree.empty(), false);
}

TEST(BinarySearchTreeTestSuite, empty3) {
    BinarySearchTree<int> tree(tree_type::post_order);

    tree.Insert(1);
    tree.Insert(2);

    tree.Delete(1);
    tree.Delete(2);
    ASSERT_EQ(tree.empty(), true);
}

TEST(BinarySearchTreeTestSuite, contains) {
    BinarySearchTree<int> tree(tree_type::post_order);

    tree.Insert(1);
    tree.Insert(2);
    ASSERT_EQ(tree.contains(6), false);
    ASSERT_EQ(tree.contains(2), true);
    tree.Delete(1);
    tree.Delete(2);
    ASSERT_EQ(tree.contains(2), false);
}
TEST(BinarySearchTreeTestSuite, size) {
    BinarySearchTree<int> tree(tree_type::post_order);

    tree.Insert(1);
    tree.Insert(2);
    ASSERT_EQ(tree.size(), 2);
    tree.Insert(6);
    tree.Insert(5);
    tree.Insert(5);
    ASSERT_EQ(tree.size(), 5);
    tree.Delete(5);
    ASSERT_EQ(tree.size(), 4);
    tree.Delete(2);
    ASSERT_EQ(tree.size(), 3);
}

TEST(BinarySearchTreeTestSuite, exist) {
    BinarySearchTree<int> tree(tree_type::post_order);

    tree.Insert(6);
    tree.Insert(1);
    ASSERT_EQ(tree.IsExistValue(6), true);
    ASSERT_EQ(tree.IsExistValue(1), true);
    ASSERT_EQ(tree.IsExistValue(5), false);
    ASSERT_EQ(tree.IsExistValue(8), false);
    ASSERT_EQ(tree.IsExistValue(0), false);
    tree.Insert(5);
    tree.Insert(4);
    tree.Insert(3);
    ASSERT_EQ(tree.IsExistValue(6), true);
    ASSERT_EQ(tree.IsExistValue(1), true);
    ASSERT_EQ(tree.IsExistValue(5), true);
    ASSERT_EQ(tree.IsExistValue(8), false);
    ASSERT_EQ(tree.IsExistValue(0), false);
    tree.Insert(8);
    ASSERT_EQ(tree.IsExistValue(6), true);
    ASSERT_EQ(tree.IsExistValue(1), true);
    ASSERT_EQ(tree.IsExistValue(5), true);
    ASSERT_EQ(tree.IsExistValue(8), true);
    ASSERT_EQ(tree.IsExistValue(0), false);
    tree.Delete(8);
    tree.Delete(4);
    tree.Delete(1);
    ASSERT_EQ(tree.IsExistValue(6), true);
    ASSERT_EQ(tree.IsExistValue(1), false);
    ASSERT_EQ(tree.IsExistValue(5), true);
    ASSERT_EQ(tree.IsExistValue(8), false);
    ASSERT_EQ(tree.IsExistValue(4), false);
}

TEST(BinarySearchTreeTestSuite, pre_order) {
    BinarySearchTree<int> tree(tree_type::pre_order);

    tree.Insert(2);
    tree.Insert(1);
    tree.Insert(6);
    tree.Insert(7);
    tree.Insert(4);
    tree.Insert(3);
    tree.Insert(5);

    vector <int> result = { 2, 1, 6, 4, 3, 5, 7 };
    vector <int> rev_result = { 7, 5, 3, 4, 6, 1, 2};
    {
        vector <int> prog;
        for (auto it : tree) {
            prog.push_back(it);
        }
        ASSERT_EQ(prog, result);
    }

    {
        vector <int> prog;
        auto it = tree.cbegin();
        for (; it != tree.cend(); ++it) {
            prog.push_back(*it);
        }
        ASSERT_EQ(prog, result);
    }

    {
        vector <int> prog;
        auto it = tree.rbegin();
        for (; it != tree.rend(); ++it) {
            prog.push_back(*it);
        }
        ASSERT_EQ(prog, rev_result);
    }

    {
        vector <int> prog;
        auto it = tree.crbegin();
        for (; it != tree.crend(); ++it) {
            prog.push_back(*it);
        }
        ASSERT_EQ(prog, rev_result);
    }

    {
        vector <int> prog;
        auto it = tree.rend();
        --it;
        for (; ; --it) {
            prog.push_back(*it);
            if (it == tree.rbegin()) {
                break;
            }
        }
        ASSERT_EQ(prog, result);
    }

    {
        vector <int> prog;
        auto it = tree.end();
        --it;
        for (; ; --it) {
            prog.push_back(*it);
            if (it == tree.begin()) {
                break;
            }
        }
        ASSERT_EQ(prog, rev_result);
    }
}

TEST(BinarySearchTreeTestSuite, in_order) {
    BinarySearchTree<int> tree(tree_type::in_order);

    tree.Insert(2);
    tree.Insert(1);
    tree.Insert(6);
    tree.Insert(7);
    tree.Insert(4);
    tree.Insert(3);
    tree.Insert(5);

    vector <int> result = { 1, 2, 3, 4, 5, 6, 7 };
    vector <int> rev_result = { 7, 6, 5, 4, 3, 2, 1 };
    {
        vector <int> prog;
        for (auto it : tree) {
            prog.push_back(it);
        }
        ASSERT_EQ(prog, result);
    }

    {
        vector <int> prog;
        auto it = tree.end();
        --it;
        for (; ; --it) {
            prog.push_back(*it);
            if (it == tree.begin()) {
                break;
            }
        }
        ASSERT_EQ(prog, rev_result);
    }

    {
        vector <int> prog;
        auto it = tree.cbegin();
        for (; it != tree.cend(); ++it) {
            prog.push_back(*it);
        }
        ASSERT_EQ(prog, result);
    }

    {
        vector <int> prog;
        auto it = tree.rbegin();
        for (; it != tree.rend(); ++it) {
            prog.push_back(*it);
        }
        ASSERT_EQ(prog, rev_result);
    }

    {
        vector <int> prog;
        auto it = tree.crbegin();
        for (; it != tree.crend(); ++it) {
            prog.push_back(*it);
        }
        ASSERT_EQ(prog, rev_result);
    }

    {
        vector <int> prog;
        auto it = tree.rend();
        --it;
        for (; ; --it) {
            prog.push_back(*it);
            if (it == tree.rbegin()) {
                break;
            }
        }
        ASSERT_EQ(prog, result);
    }
}

TEST(BinarySearchTreeTestSuite, post_order) {
    BinarySearchTree<int> tree(tree_type::post_order);

    tree.Insert(2);
    tree.Insert(1);
    tree.Insert(6);
    tree.Insert(7);
    tree.Insert(4);
    tree.Insert(3);
    tree.Insert(5);

    vector <int> result = { 1, 3, 5, 4, 7, 6, 2 };
    vector <int> rev_result = { 2, 6, 7, 4, 5, 3, 1 };
    {
        vector <int> prog;
        for (auto it : tree) {
            prog.push_back(it);
        }
        ASSERT_EQ(prog, result);
    }

    {
        vector <int> prog;
        auto it = tree.end();
        --it;
        for (; ; --it) {
            prog.push_back(*it);
            if (it == tree.begin()) {
                break;
            }
        }
        ASSERT_EQ(prog, rev_result);
    }

    {
        vector <int> prog;
        auto it = tree.cbegin();
        for (; it != tree.cend(); ++it) {
            prog.push_back(*it);
        }
        ASSERT_EQ(prog, result);
    }

    {
        vector <int> prog;
        auto it = tree.rbegin();
        for (; it != tree.rend(); ++it) {
            prog.push_back(*it);
        }
        ASSERT_EQ(prog, rev_result);
    }

    {
        vector <int> prog;
        auto it = tree.crbegin();
        for (; it != tree.crend(); ++it) {
            prog.push_back(*it);
        }
        ASSERT_EQ(prog, rev_result);
    }

    {
        vector <int> prog;
        auto it = tree.rend();
        --it;
        for (; ; --it) {
            prog.push_back(*it);
            if (it == tree.rbegin()) {
                break;
            }
        }
        ASSERT_EQ(prog, result);
    }
}

TEST(BinarySearchTreeTestSuite, char) {
    BinarySearchTree<char> tree(tree_type::post_order);

    tree.Insert('b');
    tree.Insert('a');
    tree.Insert('f');
    tree.Insert('g');
    tree.Insert('d');
    tree.Insert('c');
    tree.Insert('e');

    vector <char> result = { 'a', 'c', 'e', 'd', 'g', 'f', 'b'};
    vector <char> rev_result = { 'b', 'f', 'g', 'd', 'e', 'c', 'a'};
    {
        vector <char> prog;
        for (auto it : tree) {
            prog.push_back(it);
        }
        ASSERT_EQ(prog, result);
    }

    {
        vector <char> prog;
        auto it = tree.end();
        --it;
        for (; ; --it) {
            prog.push_back(*it);
            if (it == tree.begin()) {
                break;
            }
        }
        ASSERT_EQ(prog, rev_result);
    }

    {
        vector <char> prog;
        auto it = tree.cbegin();
        for (; it != tree.cend(); ++it) {
            prog.push_back(*it);
        }
        ASSERT_EQ(prog, result);
    }

    {
        vector <char> prog;
        auto it = tree.rbegin();
        for (; it != tree.rend(); ++it) {
            prog.push_back(*it);
        }
        ASSERT_EQ(prog, rev_result);
    }

    {
        vector <char> prog;
        auto it = tree.crbegin();
        for (; it != tree.crend(); ++it) {
            prog.push_back(*it);
        }
        ASSERT_EQ(prog, rev_result);
    }

    {
        vector <char> prog;
        auto it = tree.rend();
        --it;
        for (; ; --it) {
            prog.push_back(*it);
            if (it == tree.rbegin()) {
                break;
            }
        }
        ASSERT_EQ(prog, result);
    }
}