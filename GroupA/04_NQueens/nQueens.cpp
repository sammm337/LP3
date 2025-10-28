#include <iostream>
#include <vector>

using namespace std;

void printSolution(const vector<vector<int> >& board) {
    int N = board.size();
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << (board[i][j] ? "Q " : ". ");
        }
        cout << endl;
    }
}

bool isSafe(const vector<vector<int> >& board, int row, int col) {
    int N = board.size();
    int i, j;

    for (j = 0; j < col; ++j) {
        if (board[row][j])
            return false;
    }

    for (i = row, j = col; i >= 0 && j >= 0; --i, --j) {
        if (board[i][j])
            return false;
    }

    for (i = row, j = col; i < N && j >= 0; ++i, --j) {
        if (board[i][j])
            return false;
    }

    return true;
}

bool solveNQUtil(vector<vector<int> >& board, int col) {
    int N = board.size();

    if (col == N) {
        return true;
    }

    for (int row = 0; row < N; ++row) {
        if (isSafe(board, row, col)) {
            board[row][col] = 1;

            if (solveNQUtil(board, col + 1)) {
                return true;
            }

            board[row][col] = 0;
        }
    }

    return false;
}

void solveNQ(int N, int firstQueenRow) {
    if (firstQueenRow < 0 || firstQueenRow >= N) {
        cout << "Invalid row for first queen." << endl;
        return;
    }

    vector<vector<int> > board(N, vector<int>(N, 0));

    board[firstQueenRow][0] = 1;

    if (solveNQUtil(board, 1)) {
        cout << "Solution found for N = " << N << " with first queen at (row=" << firstQueenRow << ", col=0):\n";
        printSolution(board);
    } else {
        cout << "No solution exists for N = " << N << " with first queen at (row=" << firstQueenRow << ", col=0)." << endl;
    }
}


int main() {
    int N = 8;
    int firstQueenRow = 0;

    solveNQ(N, firstQueenRow);
    
    cout << "\n--- Trying another combination ---\n";
    
    N = 4;
    firstQueenRow = 1;
    solveNQ(N, firstQueenRow);
    
    return 0;
}
