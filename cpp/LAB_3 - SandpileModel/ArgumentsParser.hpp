#pragma once

#include "Structs.hpp"
#include <charconv>
#include <iostream>
#include <cmath>
#include <cstring>

bool MakeArguments(char** possible_arguments, int size);
void Clear(char*& name, char*& value);
bool ParseArguments(char*& name, char*& value, int& value_size);