#include <vector>
#include <limits.h>
using namespace std;
vector<vector<int>> matrixMultiplication(vector<vector<int>> matrix1, vector<vector<int>> matrix2)
{
    int r1 = matrix1.size();
    int c1 = matrix1[0].size();
    int r2 = matrix2.size();
    int c2 = matrix2[0].size();
    vector<vector<int>> mat(r1, vector<int>(c2, 0));
    if (c1 != r2)
    {
        vector<vector<int>> mat1{{INT_MAX}};
        return mat1;
    }
    else
    {
        for (int i = 0; i < r1; i++)
        {
            for (int j = 0; j < c2; j++)
            {
                mat[i][j] = 0;
                for (int k = 0; k < r2; k++)
                {
                    mat[i][j] = mat[i][j] + (matrix1[i][k] * matrix2[k][j]);
                }
                // matrix1[i][j] -= matrix2[i][j];
            }
        }
        return mat;
    }
}