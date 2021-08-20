#pragma once
#include<memory>
using arr_ptr_type = std::shared_ptr<int[]>;
void squareStep(shared_ptr<arr_ptr_type[]>Array, int x, int y, int reach, unsigned int Width);

void diamondStep(shared_ptr<arr_ptr_type[]>Array, int x, int y, int reach, unsigned int Width);

void diamondSquare(shared_ptr<arr_ptr_type[]> Array, int size, unsigned int Width);