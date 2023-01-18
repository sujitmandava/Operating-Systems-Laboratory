#include <vector>
#include <limits.h>
using namespace std;
int matrixDeterminant(vector<vector<int>> matrix)
{
    int r = matrix.size();
    int c = matrix[0].size();
    int det = 0, b = 0;
    vector<vector<int>> mat(r - 1, vector<int>(c - 1));

    if (c != r)
    {
        return INT_MIN;
    }

    if (r == 1)
    {
        return matrix[0][0];
    }
    // return -1;
    else
    {
        for (int i = 0; i < c; i++)
        {
            for (int j = 1; j < r; j++)
            {
                b = 0;
                for (int k = 0; k < c; k++)
                {
                    if (k != i)
                    {
                        mat[j - 1][b] = matrix[j][k];
                        b++;
                    }
                }
            }

            if (i % 2 == 0)
            {
                det += matrix[0][i] * matrixDeterminant(mat);
            }
            else
            {
                det -= matrix[0][i] * matrixDeterminant(mat);
            }
        }
        return det;
    }
}