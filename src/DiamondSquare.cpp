/// <DIAMOND SQUARE>
#include "System.cpp"
#include<memory>
using arr_ptr_type = std::shared_ptr<int[]>;
unsigned int roudness = 1;
void squareStep(std::shared_ptr<arr_ptr_type[]>Array, int x, int y, int reach, unsigned int Width)
{
	int count = 0;
	float avg = 0.0f;
	if (edgeCondition(x, y, reach, Width))
	{
		Array[x][y] = 0;
		return;
	}
	if (x - reach >= 0 && y - reach >= 0)
	{
		avg += Array[x - reach][y - reach];
		count++;
	}
	if (x - reach >= 0 && y + reach < Width)
	{
		avg += Array[x - reach][y + reach];
		count++;
	}
	if (x + reach < Width && y - reach >= 0)
	{
		avg += Array[x + reach][y - reach];
		count++;
	}
	if (x + reach < Width && y + reach < Width)
	{
		avg += Array[x + reach][y + reach];
		count++;
	}
	avg += random(int(-roudness * reach), int(roudness * reach));
	avg /= count;
	if (avg < 0)
		avg = 0;
	else
		Array[x][y] = round(avg);
}
void diamondStep(std::shared_ptr<arr_ptr_type[]>Array, int x, int y, int reach, unsigned int Width)
{
	int count = 0;
	float avg = 0.0f;
	if (edgeCondition(x, y, reach, Width))
	{
		Array[x][y] = 0;
		return;
	}

	{
		if (x - reach >= 0)
		{
			avg += Array[x - reach][y];
			count++;
		}
		if (x + reach < Width)
		{
			avg += Array[x + reach][y];
			count++;
		}
		if (y - reach >= 0)
		{
			avg += Array[x][y - reach];
			count++;
		}
		if (y + reach < Width)
		{
			avg += Array[x][y + reach];
			count++;
		}
		avg += random(-roudness * reach, roudness * reach);
		avg /= count;
		if (avg < 0)
			avg = 0;
		else
			Array[x][y] = (int)avg;
	}
}
void diamondSquare(std::shared_ptr<arr_ptr_type[]> Array, int size, unsigned int Width)
{
	int half = size / 2;
	if (half < 1)
		return;
	for (int y = half; y < Width; y += size)
		for (int x = half; x < Width; x += size)
			squareStep(Array, x % Width, y % Width, half, Width);
	int col = 0;
	for (int x = 0; x < Width; x += half)
	{
		col++;
		//If this is an odd column.
		if (col % 2 == 1)
			for (int z = half; z < Width; z += size)
				diamondStep(Array, x % Width, z % Width, half, Width);
		else
			for (int z = 0; z < Width; z += size)
				diamondStep(Array, x % Width, z % Width, half, Width);
	}
	diamondSquare(Array, size / 2, Width);
}
/// </DIAMOND SQUARE>