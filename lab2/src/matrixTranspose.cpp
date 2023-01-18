#include <vector>
#include <limits.h>
using namespace std;
vector<vector<int>> matrixTranspose(vector<vector<int>> matrix)
{
    int r = matrix.size();
    int c = matrix[0].size();
    vector<vector<int>> mat(c, vector<int>(r));

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            mat[j][i] = matrix[i][j];
        }
    }
    return mat;
}