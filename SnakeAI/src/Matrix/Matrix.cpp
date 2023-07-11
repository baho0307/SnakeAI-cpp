#include "Matrix.h"

Matrix::Matrix()
{

}

Matrix::Matrix(int r, int c)
{
    rows = r;
    cols = c;
    matrix = std::vector<std::vector<float>>(r, std::vector<float>(c));
}

Matrix::Matrix(std::vector<std::vector<float>> m)
{
    matrix = m;
    rows = matrix.size();
    cols = matrix[0].size();
}

Matrix Matrix::dot(Matrix n)
{
    Matrix result = Matrix(rows, n.cols);

    if (cols == n.rows) 
    {
        for (int i = 0; i < rows; i++) 
        {
            for (int j = 0; j < n.cols; j++) 
            {
                float sum = 0;
                for (int k = 0; k < cols; k++)
                    sum += matrix[i][k] * n.matrix[k][j];
                result.matrix[i][j] = sum;
            }
        }
    }
    return result;
}

void Matrix::randomize()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);

    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++)
            matrix[i][j] = dis(gen);
    }
}

Matrix Matrix::singleColumnMatrixFromArray(std::vector<float> arr)
{
    Matrix n = Matrix(arr.size(), 1);
    for (int i = 0; i < arr.size(); i++)
        n.matrix[i][0] = arr[i];
    return n;
}

std::vector<float> Matrix::toArray()
{
    std::vector<float> arr = std::vector<float>(rows * cols);
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++)
            arr[j + i * cols] = matrix[i][j];
    }
    return arr;
}

Matrix Matrix::addBias()
{
    Matrix n = Matrix(rows + 1, 1);

    for (int i = 0; i < rows; i++)
        n.matrix[i][0] = matrix[i][0];
    n.matrix[rows][0] = 1;
    return n;
}

Matrix Matrix::activate()
{
    Matrix n = Matrix(rows, cols);

    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++)
            n.matrix[i][j] = relu(matrix[i][j]);
    }
    return n;
}

float Matrix::relu(float x)
{
    return std::fmax(0.0, x);
}

void Matrix::mutate(float mutationRate)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    std::random_device rd1;
    std::mt19937 gen1(rd());
    std::normal_distribution<> dis1;

    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            float rand = dis(gen);
            if (rand < mutationRate) 
            {
                matrix[i][j] += dis1(gen1) / 5;
                if (matrix[i][j] > 1)
                    matrix[i][j] = 1;
                else if (matrix[i][j] < -1)
                    matrix[i][j] = -1;
            }
        }
    }
}

Matrix Matrix::crossover(Matrix partner)
{
    Matrix child = Matrix(rows, cols);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, cols);
    std::uniform_int_distribution<std::mt19937::result_type> dist2(0, rows);

    int randC = dist(dev);
    int randR = dist2(dev);

    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            if ((i < randR) || (i == randR && j <= randC))
                child.matrix[i][j] = matrix[i][j];
            else
                child.matrix[i][j] = partner.matrix[i][j];
        }
    }
    return child;
}

Matrix Matrix::clone()
{
    Matrix clone = Matrix(rows, cols);

    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++)
            clone.matrix[i][j] = matrix[i][j];
    }
    return clone;
}

