#include <lib/Array3D.h>
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>

TEST(Array3DTestSuite, MakingArrayTest) {
    Array3D array = Array3D::make_array(1, 1, 1);
    array[0][0][0] = 0;
    ASSERT_EQ(array[0][0][0], 0);
}

TEST(Array3DTestSuite, AssignmentElemTest) {
    Array3D array = Array3D::make_array(1, 1, 1);
    array[0][0][0] = 1423;
    ASSERT_EQ(array[0][0][0], 1423);
}

TEST(Array3DTestSuite, IstreamElemTest) {
    Array3D array = Array3D::make_array(2, 2, 2);
    std::istringstream input("125");
    std::streambuf* original_cin = std::cin.rdbuf(input.rdbuf());
    std::cin >> array[0][0][0];
    std::cin.rdbuf(original_cin);
    ASSERT_EQ(array[0][0][0], 125);
}

TEST(Array3DTestSuite, OstreamElemTest) {
    Array3D array = Array3D::make_array(2, 2, 2);
    std::ostringstream output;
    std::streambuf* original_cout = std::cout.rdbuf(output.rdbuf());
    array[0][0][0] = 125;
    std::cout << array[0][0][0];
    std::cout.rdbuf(original_cout);
    ASSERT_EQ(output.str(), "125");
}

TEST(Array3DTestSuite, CopyArrayTest) {
    Array3D arr1 = Array3D::make_array(2, 2, 1);
    arr1[0][0][0] = 6;
    arr1[0][1][0] = 8;
    arr1[1][0][0] = 4;
    arr1[1][1][0] = 1;
    Array3D arr2;
    arr2 = arr1;
    arr2[0][1][0] = 421;
    ASSERT_EQ(arr2[0][1][0], 421);
    ASSERT_EQ(arr1[0][1][0], 8);
}

TEST(Array3DTestSuite, SumArraysTest) {
    Array3D arr1 = Array3D::make_array(2, 1, 1);
    Array3D arr2 = Array3D::make_array(2, 1, 1);
    arr1[0][0][0] = 6;
    arr1[1][0][0] = 18;
    arr2[0][0][0] = 13;
    arr2[1][0][0] = 4;
    Array3D arr3 = arr1 + arr2;
    ASSERT_EQ(arr3[0][0][0], 19);
    ASSERT_EQ(arr3[1][0][0], 22);
}

TEST(Array3DTestSuite, SubArraysTest) {
    Array3D arr1 = Array3D::make_array(2, 1, 1);
    Array3D arr2 = Array3D::make_array(2, 1, 1);
    arr1[0][0][0] = 6;
    arr1[1][0][0] = 18;
    arr2[0][0][0] = 4;
    arr2[1][0][0] = 13;
    Array3D arr3 = arr1 - arr2;
    ASSERT_EQ(arr3[0][0][0], 2);
    ASSERT_EQ(arr3[1][0][0], 5);
}

TEST(Array3DTestSuite, MultArrayTest) {
    Array3D arr1 = Array3D::make_array(2, 1, 1);
    arr1[0][0][0] = 6;
    arr1[1][0][0] = 18;
    Array3D arr2 = arr1 * 2;
    ASSERT_EQ(arr2[0][0][0], 12);
    ASSERT_EQ(arr2[1][0][0], 36);
}

TEST(Array3DTestSuite, BigNumbersTest) {
    Array3D arr1 = Array3D::make_array(2, 2, 1);
    arr1[0][0][0] = 100000;
    arr1[1][1][0] = 65535;
    arr1[1][0][0] = 65536;
    arr1[0][1][0] = 131000;
    ASSERT_EQ(arr1[1][1][0], 65535);
    ASSERT_EQ(arr1[0][0][0], 100000);
    ASSERT_EQ(arr1[1][0][0], 65536);
    ASSERT_EQ(arr1[0][1][0], 131000);
}

TEST(Array3DTestSuite, BigSizeTest) {
    Array3D arr1 = Array3D::make_array(1000, 1000, 1000);
    arr1[999][999][999] = 100000;
    arr1[0][0][0] = 130999;
    arr1[500][500][500] = 65536;
    arr1[750][750][750] = 65535;
    ASSERT_EQ(arr1[999][999][999], 100000);
    ASSERT_EQ(arr1[0][0][0], 130999);
    ASSERT_EQ(arr1[500][500][500], 65536);
    ASSERT_EQ(arr1[750][750][750], 65535);
}

TEST(Array3DTestSuite, OutOfRangeZAxisTest) {
    Array3D arr1 = Array3D::make_array(1, 3, 1);

    EXPECT_THROW(arr1[0][0][2], std::out_of_range);
}

TEST(Array3DTestSuite, OutOfRangeYAxisTest) {
    Array3D arr1 = Array3D::make_array(8, 1, 1);

    EXPECT_THROW(arr1[0][2][0], std::out_of_range);
}

TEST(Array3DTestSuite, OutOfRangeXAxisTest) {
    Array3D arr1 = Array3D::make_array(1, 4, 5);

    EXPECT_THROW(arr1[3][0][0], std::out_of_range);
}

TEST(Array3DTestSuite, SumArraysWithDifferentSizesErrorTest) {
    Array3D arr1 = Array3D::make_array(1, 5, 6);
    Array3D arr2 = Array3D::make_array(2, 1, 7);

    EXPECT_THROW((arr1 + arr2), std::runtime_error);
}

TEST(Array3DTestSuite, SubtractArraysWithDifferentSizesErrorTest) {
    Array3D arr1 = Array3D::make_array(6, 1, 2);
    Array3D arr2 = Array3D::make_array(7, 5, 2);

    EXPECT_THROW((arr1 - arr2), std::runtime_error);
}
