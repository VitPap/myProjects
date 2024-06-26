#pragma once
#include <vector>
#include <iostream>
#include "TTaskScheduler.hpp"
class ITask {
public:
    virtual void Execute() {
    }

};

template<typename Args>
class Task : public ITask {
private:
    class IFunc {
    public:
        virtual Args make_one(Args args) = 0;
        virtual Args make_two(Args args_1, Args args_2) = 0;
    };
    template<typename Func>
    class Func_1 : public IFunc {
    private:
        Func func;
    public:
        Args make_one(Args arg) override {
            return func(arg);
        }
        Args make_two(Args args_1, Args args_2) override {
            return args_1;
        }
        Func_1(Func&& func_) : func(func_) {}

    };
    template<typename Func>
    class Func_2 : public IFunc {
    private:
        Func func;
    public:
        Args make_two(Args args_1, Args args_2) override {
            return func(args_1, args_2);
        }

        Args make_one(Args args) override {
            return args;
        }
        Func_2(Func&& func_) : func(func_) {}
    };

    IFunc* ifunc{};
    Task* func_1{};
    Task* func_2{};
    Args arg_1{};
    Args arg_2{};
    bool is_arg1_filled{};
    bool is_arg2_filled{};
    bool is_func1_filled{};
    bool is_func2_filled{};
    bool is_executed{};

public:
    Args answer{};
    void Execute() override {
        if (is_executed) {
            return;
        }
        is_executed = true;
        if (is_func1_filled && is_arg2_filled) {
            func_1->Execute();
            answer = ifunc->make_two(func_1->answer, arg_2);
        } else if (is_func2_filled && is_arg1_filled) {
            func_2->Execute();
            answer = ifunc->make_two(arg_1, func_2->answer);
        } else if (is_arg1_filled && is_arg2_filled) {
            answer = ifunc->make_two(arg_1, arg_2);
        } else if (is_arg1_filled) {
            answer = ifunc->make_one(arg_1);
        } else if (is_func1_filled && is_func2_filled) {
            func_1->Execute();
            func_2->Execute();
            answer = ifunc->make_two(func_1->answer, func_2->answer);
        } else if (is_func1_filled) {
            func_1->Execute();
            answer = ifunc->make_one(func_1->answer);
        } 
        
    }
    template<typename Func>
    Task(Func&& ifunc_, Task* func_1, Task* func_2, Args arg_1, Args arg_2, bool is_arg1, bool is_arg2, bool is_func1, bool is_func2) : func_1(func_1), func_2(func_2), arg_1(arg_1), arg_2(arg_2) {
        is_arg1_filled = is_arg1;
        is_arg2_filled = is_arg2;
        is_func1_filled = is_func1;
        is_func2_filled = is_func2;
        if ((is_arg1_filled || is_func1_filled) && (is_arg2_filled || is_func2_filled)) {
            ifunc = new Func_2<Func>(std::forward<Func>(ifunc_));
        } else {
            ifunc = new Func_1<Func>(std::forward<Func>(ifunc_));
        }
    }

};
