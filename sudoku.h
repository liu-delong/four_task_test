#ifndef SUDOKU_H
#define SUDOKU_H

const bool DEBUG_MODE = false;
enum { ROW=9, COL=9, N = 81, NEIGHBOR = 20 };
const int NUM = 9;

struct Sudoku
{
    public:
        int neighbors[N][NEIGHBOR];
        int board[N];
        int spaces[N];
        int nspaces;
        int (*chess)[COL] = (int(*)[COL])board;
};



void init_neighbors(Sudoku* sudo);
void input(const char in[N], Sudoku* sudo);
//void init_cache(Sudoku* sudo);
bool available(int guess, int cell, Sudoku* sudo);

// bool solve_sudoku_basic(int which_space);
// bool solve_sudoku_min_arity(int which_space);
bool solve_sudoku_dancing_links(int unused, Sudoku* sudo);
bool solved(Sudoku* sudo);
#endif
