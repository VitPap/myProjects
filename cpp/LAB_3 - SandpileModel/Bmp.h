#pragma once

#include "Structs.hpp"
#include <fstream>
#include <cstring>
#include <iostream>
#include <cstdint>
#include <cmath>
#include <charconv>

void save(char* filename, Matrix& main_matrix);
char* getFileName(int64_t pictures_cnt);