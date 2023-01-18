#include <vector>
#include <limits.h>
using namespace std;
vector<vector<int>> matrixAddition(vector<vector<int>> matrix1, vector<vector<int>> matrix2)
{
    int r1 = matrix1.size();
    int c1 = matrix1[0].size();
    int r2 = matrix2.size();
    int c2 = matrix2[0].size();
    if (r1 != r2 || c1 != c2)
    {
        vector<vector<int>> mat{{INT_MAX}};
        return mat;
    }
    else
    {
        for (int i = 0; i < r1; i++)
        {
            for (int j = 0; j < c1; j++)
            {
                matrix1[i][j] += matrix2[i][j];
            }
        }
        return matrix1;
    }
}