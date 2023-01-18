#include <vector>
using namespace std;
vector<vector<int>> scalarMultiplication(int scalar, vector<vector<int>> matrix)
{
    int r = matrix.size();
    int c = matrix[0].size();
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            matrix[i][j] *= scalar;
        }
    }
    return matrix;
}