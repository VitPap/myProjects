#pragma once

#include "Structs.hpp"
#include "Bmp.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>

void SandPile(std::ifstream& input, Matrix& main_matrix);
void MakeMatrixSize(std::ifstream& input, Matrix& main_matrix);
void FillMatrix(std::ifstream& input, Matrix& main_matrix);
int** Resize(int** matrix, Matrix& main_matrix, int &right, int &down, int &left, int &up);
void Collapse(bool& was_collapsed, Matrix& main_matrix);