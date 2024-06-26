#pragma once

#include <iostream>
#include "Lib/TTaskScheduler.hpp"
#include <gtest/gtest.h>
#include <sstream>

using namespace std;

TEST(TTaskSchedulerTestSuite, example) {
    float a = 1;
    float b = -2;
    float c = 0;

    TTaskScheduler scheduler;

    auto id1 = scheduler.add([](float a, float c) {return -4 * a * c; }, a, c);

    auto id2 = scheduler.add([](float b, float v) {return b * b + v; }, b, scheduler.getFutureResult(id1));

    auto id3 = scheduler.add([](float b, float d) {return -b + std::sqrt(d); }, b, scheduler.getFutureResult(id2));

    auto id4 = scheduler.add([](float b, float d) {return -b - std::sqrt(d); }, b, scheduler.getFutureResult(id2));

    auto id5 = scheduler.add([](float a, float v) { return v / (2 * a); }, a, scheduler.getFutureResult(id3));

    auto id6 = scheduler.add([](float a, float v) { return v / (2 * a); }, a, scheduler.getFutureResult(id4));

    scheduler.executeAll();

    ASSERT_EQ(scheduler.getResult<float>(id5), 2);
    ASSERT_EQ(scheduler.getResult<float>(id6), 0);
}

TEST(TTaskSchedulerTestSuite, twoFunc) {
    float a = 2;
    float b = 4;

    TTaskScheduler scheduler;

    auto id1 = scheduler.add([](float a, float b) {return a * b; }, a, b);
    auto id2 = scheduler.add([](float a, float b) {return b + a; }, a, b);
    auto id3 = scheduler.add([](float a, float b) {return a * b; }, scheduler.getFutureResult(id1), scheduler.getFutureResult(id2));
    scheduler.executeAll();

    ASSERT_EQ(scheduler.getResult<float>(id3), 48);
}

TEST(TTaskSchedulerTestSuite, strings) {
    std::string a = "a";
    std::string b = "b";

    TTaskScheduler scheduler;

    auto id1 = scheduler.add([](std::string a, std::string b) {return a + b; }, a, b);
    auto id2 = scheduler.add([](std::string a, std::string b) {return a + a + b + b; }, a, b);
    scheduler.executeAll();

    ASSERT_EQ(scheduler.getResult<std::string>(id1), "ab");
    ASSERT_EQ(scheduler.getResult<std::string>(id2), "aabb");
}

/*TEST(TTaskSchedulerTestSuite, tripleForOne) {
    float a = 2;

    TTaskScheduler scheduler;

    auto id1 = scheduler.add([](float a) {return a * a * a; }, a);
    scheduler.executeAll();

    ASSERT_EQ(scheduler.getResult<float>(id1), 8);
}*/