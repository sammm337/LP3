// #include <bits/stdc++.h>
#include <vector>
#include<iostream>
using namespace std;

int COL;
int ROW;
int N = 4;

void printSolution(vector<vector<int> > board) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++)
      if (board[i][j])
        cout << "Q ";
      else
        cout << ". ";
    printf("\n");
  }
}

bool isSafe(vector<vector<int> > board, int row, int col) {
  static int directions[8][2] = {
        {0, 1}, {0, -1},    // horizontal
        {1, 0}, {-1, 0},    // vertical
        {1, 1}, {-1, -1},   // main diagonal
        {1, -1}, {-1, 1}    // anti-diagonal
    };

    for (auto& dir : directions) {
        int i = row + dir[0], j = col + dir[1];
        while (i >= 0 && i < N && j >= 0 && j < N) {
            if (board[i][j])
                return false;
            i += dir[0];
            j += dir[1];
        }
    }
    return true;
}

bool Place(vector<vector<int> > & board, int col){
    if(col >= N) return true;
    if(col == COL){
        if(Place(board , col + 1 )) return true;
        return false;
    }else{
        for(int i = 0; i < N; i ++){
            if(isSafe(board , i, col)){
                board[i][col] = 1;
                if(Place(board , col + 1)) return true;
                board[i][col] = 0;
            }
        }
    }
    return false;
}

 
bool solveNQ() {
  cout << "Enter size of board: ";
  cin >> N;
  cout << "Enter row and col of first queen to be placed:\nrow (1-" << N
       << "): ";
  cin >> ROW;
  ROW--;
  cout << "\ncol(1-" << N << "): ";
  cin >> COL;
  COL--;
  cout << endl;
  vector<vector<int> > board(N, vector<int>(N, 0));

  board[ROW][COL] = 1;

  if (Place(board, 0) == false) {
    cout << "Solution does not exist";
    return false;
  }

  printSolution(board);
  return true;
}

int main() {
  solveNQ();
  return 0;
}