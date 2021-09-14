#pragma once
#include<memory>
#include "System.cpp"
int roudness = 1;
template<class T>
class Matrix
{
public:
    using num_type = T;
    using size_type = std::size_t;
    using arr_ptr_type = std::unique_ptr<num_type[]>;
private:
    size_type n, m;
    std::unique_ptr<arr_ptr_type[]> Array;
public:
    Matrix(std::size_t n, std::size_t m) : n(n), m(m), Array(std::make_unique<arr_ptr_type[]>(n))
    {
        for (std::size_t i = 0; i < n; ++i)
            Array[i] = std::make_unique<num_type[]>(m);
    }
    num_type& operator()(size_type i, size_type j) {
        return Array[i][j];
    }

    size_type getRowCount() { return n; }
    size_type getColCount() { return m; }
    void show()
    {
        for (size_type i = 0; i < n; i++) {
            for (size_type j = 0; j < m; j++)
                std::cout << Array[i][j] << ' ' << std::setw(2);
            std::cout << '\n';
        }
    }
    void fill(T value)
    {
        for (size_type i = 0; i < n; i++)
            for (size_type j = 0; j < m; j++)
                Array[i][j] = value;
    }
    void Scaling(T max_value)
    {
        T max = Array[0][0];
        for (size_type i = 0; i < n; i++)
            for (size_type j = 0; j < m; j++)
                if (max < Array[i][j])
                    max = Array[i][j];
        float div = float(max_value) / float(max);
        for (size_type i = 0; i < n; i++)
            for (size_type j = 0; j < m; j++)
                Array[i][j] *= div;

    }
    void squareStep(int x, int y, int reach, unsigned int Width)
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
    void diamondStep(int x, int y, int reach, unsigned int Width)
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
    void diamondSquare(int size, unsigned int Width)
    {
        int half = size / 2;
        if (half < 1)
            return;
        for (int y = half; y < Width; y += size)
            for (int x = half; x < Width; x += size)
                squareStep(x % Width, y % Width, half, Width);
        int col = 0;
        for (int x = 0; x < Width; x += half)
        {
            col++;
            //If this is an odd column.
            if (col % 2 == 1)
                for (int z = half; z < Width; z += size)
                    diamondStep(x % Width, z % Width, half, Width);
            else
                for (int z = 0; z < Width; z += size)
                    diamondStep(x % Width, z % Width, half, Width);
        }
        diamondSquare(size / 2, Width);
    }
    void Generate()
    {
        srand(time(0));
        int Width = n;
        int size = Width / 2;
        diamondSquare(size, Width);
    }
    T Max()
    {
        T max = Array[0][0];
        for (size_type i = 0; i < n; i++)
            for (size_type j = 0; j < m; j++)
                if (Array[i][j] > max)
                    max = Array[i][j];

        return max;
    }
};
