#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int n;
vector<int> queens;

bool is_attack(int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        if (queens[i] == col || abs(queens[i] - col) == row - i)
        {
            return true;
        }
    }
    return false;
}

int conflict(int row)
{
    int count = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = i + 1; j < row; j++)
        {
            if (abs(queens[i] - queens[j]) == j - i || queens[i] == queens[j])
            {
                count++;
            }
        }
    }
    return count;
}

void hill_climbing()
{
    int curr_conflicts = conflict(n);
    int best_row, best_col;
    while (curr_conflicts > 0)
    {
        best_row = -1;
        best_col = -1;
        int min_conflicts = INT_MAX;
        for (int row = 0; row < n; row++)
        {
            for (int col = 0; col < n; col++)
            {
                if (is_attack(row, col))
                {
                    continue;
                }
                queens[row] = col;
                int new_conflicts = conflict(n);
                if (new_conflicts < min_conflicts)
                {
                    min_conflicts = new_conflicts;
                    best_row = row;
                    best_col = col;
                }
            }
        }
        if (best_row == -1)
        {
            break;
        }
        queens[best_row] = best_col;
        curr_conflicts = min_conflicts;
    }
}

int main()
{
    srand(time(0));
    n = 8;
    queens.resize(n);
    for (int i = 0; i < n; i++)
    {
        queens[i] = rand() % n;
    }
    hill_climbing();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (queens[i] == j)
            {
                cout << "Q ";
            }
            else
            {
                cout << ". ";
            }
        }
        cout << endl;
    }
    return 0;
}