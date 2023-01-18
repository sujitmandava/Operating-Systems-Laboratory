#include <bits/stdc++.h>
#include "matrixOperations.hpp"
#include "scalarOperations.hpp"
using namespace std;

typedef vector<vector<int>> Matrix;

vector<Matrix> readInput(vector<string> &inputFile);
Matrix parseMatrix(vector<string>, int rows, int cols);
char extractOperation(string s);
/*
TODO
1. Error logging
2. Writing output into output files
3. Writing expected output files
*/

int main(int argc, char *argv[])
{
    vector<string> inputFile;
    vector<Matrix> matrices = readInput(inputFile);
    // for (int i = 0; i < matrices.size(); i++)
    // {
    //     for (int j = 0; j < matrices[i].size(); j++)
    //     {
    //         for (int k = 0; k < matrices[i][j].size(); k++)
    //         {
    //             cout << matrices[i][j][k] << " ";
    //         }
    //         cout << "\n";
    //     }
    //     cout << "EOM\n";
    // }

    // cout << argv[1][1] << "\n";
    // cout << inputFile[0] << "\n";

    Matrix matrixOut;
    int matrixDet;
    char operation;

    if (argc == 1)
    {
        operation = extractOperation(inputFile[0]);
    }
    else
    {
        operation = argv[1][1];
    }

    if (operation == 'a')
    {
        if (matrices.size() == 3)
        {
            matrixOut = scalarAddition(matrices[1][0][0], matrices[2]);
        }
        else
        {
            // Not enough operands exception; outputting parsed matrix as is
            matrixOut = matrices[matrices.size() - 1];
        }
    }
    else if (operation == 's')
    {
        if (matrices.size() == 3)
        {
            matrixOut = scalarSubtraction(matrices[1][0][0], matrices[2]);
        }
        else
        {
            // Not enough operands exception; outputting parsed matrix as is
            matrixOut = matrices[matrices.size() - 1];
        }
    }
    else if (operation == 'm')
    {
        if (matrices.size() == 3)
        {
            matrixOut = scalarMultiplication(matrices[1][0][0], matrices[2]);
        }
        else
        {
            // Not enough operands exception; outputting parsed matrix as is
            matrixOut = matrices[matrices.size() - 1];
        }
    }
    else if (operation == 'd')
    {
        if (matrices.size() == 3)
        {
            matrixOut = scalarDivision(matrices[1][0][0], matrices[2]);
        }
        else
        {
            // Not enough operands exception; outputting parsed matrix as is
            matrixOut = matrices[matrices.size() - 1];
        }
    }
    else if (operation == 'A')
    {
        if (matrices.size() == 3)
        {
            matrixOut = matrixAddition(matrices[1], matrices[2]);
        }
        else
        {
            // Not enough operands exception; outputting parsed matrix as is
            matrixOut = matrices[matrices.size() - 1];
        }
    }
    else if (operation == 'S')
    {
        if (matrices.size() == 3)
        {
            matrixOut = matrixSubtraction(matrices[1], matrices[2]);
        }
        else
        {
            // Not enough operands exception; outputting parsed matrix as is
            matrixOut = matrices[matrices.size() - 1];
        }
    }
    else if (operation == 'M')
    {
        if (matrices.size() == 3)
        {
            matrixOut = matrixMultiplication(matrices[1], matrices[2]);
        }
        else
        {
            // Not enough operands exception; outputting parsed matrix as is
            matrixOut = matrices[matrices.size() - 1];
        }
    }
    else if (operation == 'T')
    {
        matrixOut = matrixTranspose(matrices[1]);
    }
    else if (operation == 'X')
    {
        matrixDet = matrixDeterminant(matrices[1]);
    }
    else if (operation == 'i')
    {
        // Exceptions
    }

    if (operation != 'X')
    {
        cout << matrixOut.size() << " " << matrixOut[0].size() << "\n";
        for (int j = 0; j < matrixOut.size(); j++)
        {
            for (int k = 0; k < matrixOut[j].size(); k++)
            {
                cout << matrixOut[j][k] << ", ";
            }
            if (j != matrixOut.size() - 1)
                cout << "\n";
        }
    }
    else
    {
        cout << matrixDet << "\n";
    }
}

/*
    Structure:
        (DONE)
        Read input file line by line
        Parse line
            If whitespace/newline or comment, do nothing
            If scalar then store for scalar operation
            Parse and store two matrices
        (DONE)


        Check operation in argv
        If operation and input data dont match, log error
        Else
            Operate
                If illegal math operations log error

    matrixAddition.cpp
    scalarAddition.cpp
    matrixSubtraction.cpp
    scalarSubtraction.cpp
    matrixMultiplication.cpp
    scalarMultiplication.cpp
    scalarDivision.cpp
    matrixTranspose.cpp
    matrixDeterminant.cpp


    matrixOperations.h
    scalarOperations.h
*/

vector<Matrix> readInput(vector<string> &inputFile)
{
    vector<Matrix> matrices(1); // 0th index tells us whether its a scalar + matrix or matrix + matrix operation
    matrices[0] = {{1}};        // Assume matrix + matrix operation
    int scalarIndex = 1;        // Place to store matrix
    string currLine;
    int lc = 0;

    while (getline(cin, currLine, '\n'))
    {
        inputFile.push_back(currLine);
        // lc++;
        // if (lc == 8)
        // {
        //     break;
        // }
    }

    for (int i = 0; i < inputFile.size(); i++)
    {
        bool commentFlag = false;
        bool numRead = false;
        // cout << inputFile[i] << "\n";
        vector<int> currNums;
        int currNum = 0;

        for (auto c : inputFile[i])
        {
            // Do for characters
            if (c == '#')
            {
                commentFlag = true;
                break;
            }
            else if ('0' <= c && c <= '9')
            {
                numRead = true;
                currNum = 10 * currNum + (c - '0');
            }
            else
            {
                if (numRead)
                {
                    currNums.push_back(currNum);
                    currNum = 0;
                }
                numRead = false;
            }
        }

        if (commentFlag == true)
        {
            continue;
        }

        if (numRead)
        {
            currNums.push_back(currNum);
            currNum = 0;
        }

        if (currNums.size() == 1) // Only one number => Scalar for scalar operations
        {
            matrices[0] = {{0}}; // Scalar operation flag;
            matrices.push_back({currNums});
            scalarIndex = matrices.size() - 1;
        }
        else if (currNums.size() == 2) // Matrix Dimensions
        {
            vector<string> matrixAsStrings;
            for (int count = 0; count < currNums[0]; count++)
            {
                matrixAsStrings.push_back(inputFile[++i]);
            }

            // 0 contains rows 1 contains columns
            // if (matrices[0][0][0] == 0) // Scalar operation
            // {
            // matrices[2] = parseMatrix(matrixAsStrings, currNums[0], currNums[1]);
            // }
            // else
            // {
            matrices.push_back(parseMatrix(matrixAsStrings, currNums[0], currNums[1]));
            // currIndex += 1;
            // }
        }

        if (matrices.size() == 3)
        {
            break;
        }
    }
    if (matrices[0][0][0] == 0) // Scalar
    {
        if (scalarIndex == 2)
            swap(matrices[scalarIndex], matrices[1]);
    }
    return matrices;
}

Matrix parseMatrix(vector<string> matrixAsStrings, int rows, int cols)
{
    Matrix matrix(rows, vector<int>(cols, 0));
    for (int i = 0; i < rows; i++)
    {
        bool numRead = false;
        vector<int> currNums;
        int currNum = 0;

        for (auto c : matrixAsStrings[i])
        {
            if ('0' <= c && c <= '9')
            {
                numRead = true;
                currNum = 10 * currNum + (c - '0');
            }
            else
            {
                if (numRead)
                {
                    currNums.push_back(currNum);
                    currNum = 0;
                }
                numRead = false;
            }
        }
        matrix[i] = currNums;
    }

    return matrix;
}

char extractOperation(string s)
{
    // By convention, string s is of format "Option: -a"
    unordered_set<char> legalOperations = {'a', 's', 'm', 'd', 'A', 'S', 'M', 'T', 'X'};
    for (int i = s.length() - 1; i >= 0; i--)
    {
        if (legalOperations.find(s[i]) != legalOperations.end())
        {
            return s[i];
        }
    }
    return 'i';
}