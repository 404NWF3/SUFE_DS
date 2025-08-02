#include <iostream>
#include <vector>

using namespace std;

const int N = 8;
vector<vector<int>> solutions;
vector<vector<int>> board(N, vector<int>(N, 0));

bool isSafe(int row, int col) {
    for (int i = 0; i < row; ++i) {
        if (board[i][col] == 1) {
            return false;
        }
    }

    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    for (int i = row - 1, j = col + 1; i >= 0 && j < N; --i, ++j) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    return true;
}

void backtrack(int row) {
    if (row == N) {
        vector<int> solution;
        for (const vector<int>& r : board) {
            for (int v : r) {
                solution.push_back(v);
            }
        }
        solutions.push_back(solution);
        return;
    }

    for (int col = 0; col < N; ++col) {
        if (isSafe(row, col)) {
            board[row][col] = 1;
            backtrack(row + 1);
            board[row][col] = 0;
        }
    }
}

void printSolutions() {
    for (const vector<int>& solution : solutions) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cout << solution[i * N + j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

int main() {
    backtrack(0);
    printSolutions();
    return 0;
}
