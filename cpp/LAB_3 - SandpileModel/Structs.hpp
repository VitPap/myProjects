#pragma once

#include <cstdint>
#include <limits>

struct Flags {

    inline static bool is_max_iter_used = false;
    inline static bool is_freq_used = false;
    inline static bool is_output_used = false;
    inline static bool is_input_used = false;
};

struct Matrix {
    
    int16_t row_size = 0;
    int16_t column_size = 0;
    int** main_matrix;

    ~Matrix() {
        for (int i = 0; i < column_size; ++i) {
            delete[] main_matrix[i];
        }
        delete[] main_matrix;
    }
};

struct Arguments {
    
    inline static char* input;
    inline static char* output;
    inline static uint64_t max_iter = 0;
    inline static uint64_t freq = 0;

    ~Arguments() {
        delete[] output;
        delete[] input;
    }
};

