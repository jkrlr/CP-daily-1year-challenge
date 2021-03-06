#include <bits/stdc++.h>
using namespace std;

/* Time =)(N^N), Space = (N^2)
bool IsSafe(int row, int col, vector<string> board, int n)
{
    // check for upper diagonal
    int duprow = row;
    int dupcol = col;

    while (row >= 0 && col >= 0)
    {
        if (board[row][col] == 'Q')
            return false;
        row--;
        col--;
    }

    row = duprow;
    col = dupcol;

    while (col >= 0)
    {
        if (board[row][col] == 'Q')
            return false;
        col--;
    }

    row = duprow;
    col = dupcol;
    while (row < n && col >= 0)
    {
        if (board[row][col] == 'Q')
            return false;
        row++;
        col--;
    }
    return true;
}

void solveNQueen(int col, vector<string> &board, vector<vector<string>> &ans, int n)
{
    // Base Case
    if (col == n)
    {
        // Store the pattern
        ans.push_back(board);
        return;
    }

    // Recursive Case
    // Try to place Queen at each column
    for (int row = 0; row < n; row++)
    {
        if (IsSafe(row, col, board, n))
        {
            board[row][col] = 'Q';
            solveNQueen(col + 1, board, ans, n);
            board[row][col] = '.';
        }
    }
}

int nQueen(int n)
{
    vector<vector<string>> ans;
    vector<string> board(n);

    string s(n, '.');
    for (int i = 0; i < n; i++)
    {
        board[i] = s;
    }

    solveNQueen(0, board, ans, n);
    return ans.size();
} */

// More Efficient Solution using Hashing : Time = O(N!), Space = (N^2)

void solveNQueen(int col, vector<string> &board, vector<vector<string>> &ans, vector<int> &leftRow, vector<int> &upperDiagonal, vector<int> &lowerDiagonal, int n)
{
    // Base Case
    if (col == n)
    {
        // Store the pattern
        ans.push_back(board);
        return;
    }

    // Recursive Case
    // Try to place Queen at each column
    for (int row = 0; row < n; row++)
    {
        if (leftRow[row] == 0 && lowerDiagonal[row + col] == 0 && upperDiagonal[n - 1 + col - row] == 0)
        {
            board[row][col] = 'Q';
            leftRow[row] = 1;
            lowerDiagonal[row + col] = 1;
            upperDiagonal[n - 1 + col - row] = 1;

            solveNQueen(col + 1, board, ans, leftRow, upperDiagonal, lowerDiagonal, n);

            board[row][col] = '.';
            leftRow[row] = 0;
            lowerDiagonal[row + col] = 0;
            upperDiagonal[n - 1 + col - row] = 0;
        }
    }
}

int nQueen(int n)
{
    vector<vector<string>> ans;
    vector<string> board(n);

    string s(n, '.');
    for (int i = 0; i < n; i++)
    {
        board[i] = s;
    }

    vector<int> leftRow(n, 0), upperDiagonal(2 * n - 1, 0), lowerDiagonal(2 * n - 1, 0);

    solveNQueen(0, board, ans, leftRow, upperDiagonal, lowerDiagonal, n);
    return ans.size();
}