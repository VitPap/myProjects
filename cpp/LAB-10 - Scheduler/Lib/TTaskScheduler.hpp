#pragma once
#include <vector>
#include <iostream>
#include "Task.hpp"

class TTaskScheduler {
private:
    std::vector<ITask*> tasks;

public:
    template<typename Func, typename Args>
    auto add(Func func, Args arg_1, Task<Args>* task_2) {
        auto task = new Task<Args>(func, nullptr, task_2, arg_1, NULL, 1, 0, 0, 1);

        tasks.push_back(task);
        return task;
    }
    template<typename Func, typename Args>
    auto add(Func func, Args arg_1, Args arg_2) {
        auto task = new Task<Args>(func, nullptr, nullptr, arg_1, arg_2, 1, 1, 0, 0);

        tasks.push_back(task);
        return task;
    }
    template<typename Func, typename Args>
    auto add(Func func, Args arg_1) {
        auto task = new Task<Args>(func, nullptr, nullptr, arg_1, NULL, 1, 0, 0, 0);

        tasks.push_back(task);
        return task;
    }
    template<typename Func, typename Args>
    auto add(Func func, Task<Args>* task_1) {
        auto task = new Task<Args>(func, task_1, nullptr, NULL, NULL, 0, 0, 1, 0);

        tasks.push_back(task);
        return task;
    }
    template<typename Func, typename Args>
    auto add(Func func, Task<Args>* task_1, Task<Args>* task_2) {
        auto task = new Task<Args>(func, task_1, task_2, NULL, NULL, 0, 0, 1, 1);

        tasks.push_back(task);
        return task;
    }
    template<typename Func, typename Args>
    auto add(Func func, Task<Args>* task_1, Args arg_2) {
        auto task = new Task<Args>(func, task_1, nullptr, NULL, arg_2, 0, 1, 1, 0);

        tasks.push_back(task);
        return task;
    }

    void executeAll() {
        for (const auto& task : tasks) {
            task->Execute();
        }
    }
       
    template<typename Args>
    Args getResult(Task<Args>* task) {
        task->Execute();
        return task->answer;
    }

    template<typename Args>
    Task<Args>* getFutureResult(Task<Args>* task) {
        return task;
    }
};