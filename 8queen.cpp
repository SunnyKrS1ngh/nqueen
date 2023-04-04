#include <bits/stdc++.h>
using namespace std;
int n = 8;

bool isSafe(int row, int col, vector<string> board)
{
    int duprow = row;
    int dupcol = col;
    while (dupcol >= 0)
    {
        if (board[duprow][dupcol] == 'x')
        {
            return false;
        }
        dupcol--;
    }
    dupcol = col;
    while (duprow >= 0 && dupcol >= 0)
    {
        if (board[duprow][dupcol] == 'x')
        {
            return false;
        }
        duprow--;
        dupcol--;
    }
    duprow = row;
    dupcol = col;
    while (duprow < n && dupcol >= 0)
    {
        if (board[duprow][dupcol] == 'x')
        {
            return false;
        }
        duprow++;
        dupcol--;
    }
    return true;
}

int attacked(int row, int col, vector<string> board)
{
    int a = 0;
    int duprow = row;
    int dupcol = col;
    for (int i = 0; i < n; i++)
    {
        if (i != col && board[row][i] == 'x')
        {
            a++;
        }
    }
    dupcol = col;
    while (duprow >= 0 && dupcol >= 0)
    {
        if (board[duprow][dupcol] == 'x')
        {
            a++;
        }
        duprow--;
        dupcol--;
    }
    duprow = row;
    dupcol = col;
    while (duprow < n && dupcol >= 0)
    {
        if (board[duprow][dupcol] == 'x')
        {
            a++;
        }
        duprow++;
        dupcol--;
    }
    return a;
}

void solve(int col, vector<string> &board, vector<vector<string>> &ans)
{
    if (col == n)
    {
        ans.push_back(board);
        return;
    }
    for (int row = 0; row < n; row++)
    {
        if (isSafe(row, col, board))
        {
            board[row][col] = 'x';
            solve(col + 1, board, ans);
            board[row][col] = 'o';
        }
    }
}

bool hillClimb(int row, vector<string> &board)
{
    if (row == n)
    {
        return true;
    }
    int currenth = INT_MAX;
    int next_row = row + 1;
    int best_col = -1;
    for (int col = 0; col < n; col++)
    {
        if (isSafe(row, col, board))
        {
            int heur = 0;
            for (int i = 0; i < n; i++)
            {
                if (!isSafe(next_row, i, board))
                {
                    heur++;
                }
            }
            if (heur < currenth)
            {
                currenth = heur;
                best_col = col;
            }
        }
    }
    if (best_col = -1)
    {
        return false;
    }
    board[best_col][row] = 'x';
    if (hillClimb(next_row, board))
    {
        return true;
    }
    board[best_col][row] = 'o';
    return false;
}

void hillClimb2(int col, vector<string> &board)
{
    if (col == n)
    {
        return;
    }
    int curr_heur = INT_MAX;
    int best_row = -1;
    for (int row = 0; row < n; row++)
    {
        if (isSafe(row, col, board))
        {
            board[row][col] = 'x';
            int heur = attacked(row, col, board);
            if (heur < curr_heur)
            {
                curr_heur = heur;
                best_row = row;
            }
            board[row][col] = 'o';
        }
    }
    board[best_row][col] = 'x';
    hillClimb2(col + 1, board);
    board[best_row][col] = 'o';
}

int main()
{

    vector<string> board(n);
    string s(n, 'o');
    for (int i = 0; i < n; i++)
    {
        board[i] = s;
    }
    vector<string> boarddup = board;
    hillClimb(0, boarddup);
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         cout << board[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    vector<vector<string>> ans;
    solve(0, board, ans);
    int sol = 0;
    for (int i = 0; i < n; i++)
    {
        sol++;
        cout << "#" << sol << endl;
        for (int j = 0; j < n; j++)
        {
            cout << ans[i][j] << endl;
        }
        cout << endl;
    }

    return 0;
}
