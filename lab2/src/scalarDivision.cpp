#include <vector>
#include <limits.h>
using namespace std;
vector<vector<int>> scalarDivision(int scalar, vector<vector<int>> matrix)
{
    int r = matrix.size();
    int c = matrix[0].size();
    
    if(scalar == 0)
    {
        vector<vector<int>> mat1{{INT_MAX}};
        return mat1;
    }
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            matrix[i][j] /= scalar;
        }
    }
    return matrix;
}