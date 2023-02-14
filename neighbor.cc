#include <assert.h>
#include <stdio.h>
#include <strings.h>
#include "sudoku.h"
#include <algorithm>

static void mark_adjacent(bool adjacent[ROW][COL], int row, int col)
{
  for (int i = 0; i < NUM; ++i) {
    adjacent[row][i] = true;
    adjacent[i][col] = true;
  }
  int top = (row/3)*3;
  int left = (col/3)*3;
  adjacent[top][left] = true;
  adjacent[top][left+1] = true;
  adjacent[top][left+2] = true;
  adjacent[top+1][left] = true;
  adjacent[top+1][left+1] = true;
  adjacent[top+1][left+2] = true;
  adjacent[top+2][left] = true;
  adjacent[top+2][left+1] = true;
  adjacent[top+2][left+2] = true;
}

static void collect_neighbors(const bool adjacent[ROW][COL], int row, int col, int myneighbors[NEIGHBOR])
{
  int n = 0;
  for (int y = 0; y < ROW; ++y) {
    for (int x = 0; x < COL; ++x) {
      if (adjacent[y][x] && !(y == row && x == col)) {
        assert(n < NEIGHBOR);
        myneighbors[n++] = y*COL + x;
      }
    }
  }
  assert(n == NEIGHBOR);
}

static void print_neighbors(const bool adjacent[ROW][COL], int row, int col, int myneighbors[NEIGHBOR])
{
  for (int y = 0; y < ROW; ++y) {
    for (int x = 0; x < COL; ++x) {
      if (y == row && x == col)
        putchar('X');
      else
        putchar(adjacent[y][x] ? 'o' : '.');
    }
    printf("\n");
  }
  for (int i = 0; i < NEIGHBOR; ++i) {
    printf("%2d, ", myneighbors[i]);
  }
  puts("\n");
}

/*public*/
 void init_neighbors(Sudoku* sudo)
{
  for (int row = 0; row < ROW; ++row) {
    for (int col = 0; col < COL; ++col) {
      bool adjacent[ROW][COL];
      bzero(adjacent, sizeof adjacent);
      mark_adjacent(adjacent, row, col);

      int me = row*COL + col;
      collect_neighbors(adjacent, row, col, sudo->neighbors[me]);

      if (DEBUG_MODE)
        print_neighbors(adjacent, row, col, sudo->neighbors[me]);
    }
  }
}

bool solved(Sudoku* sudo)
{
  for (int row = 0; row < ROW; ++row) {
    // check row
    int occurs[10] = { 0 };
    for (int col = 0; col < COL; ++col) {
      int val = sudo->chess[row][col];
      assert(1 <= val && val <= NUM);
      ++occurs[val];
    }
    if (std::count(occurs, occurs+10, 1) != NUM)
      return false;
  }

  for (int col = 0; col < COL; ++col) {
    int occurs[10] = { 0 };
    for (int row = 0; row < ROW; ++row) {
      int val = sudo->chess[row][col];
      assert(1 <= val && val <= NUM);
      ++occurs[val];
    }

    if (std::count(occurs, occurs+10, 1) != NUM)
      return false;
  }

  for (int row = 0; row < ROW; row += 3) {
    for (int col = 0; col < COL; col += 3) {
      int occurs[10] = { 0 };
      ++occurs[sudo->chess[row  ][col]];
      ++occurs[sudo->chess[row  ][col+1]];
      ++occurs[sudo->chess[row  ][col+2]];
      ++occurs[sudo->chess[row+1][col]];
      ++occurs[sudo->chess[row+1][col+1]];
      ++occurs[sudo->chess[row+1][col+2]];
      ++occurs[sudo->chess[row+2][col]];
      ++occurs[sudo->chess[row+2][col+1]];
      ++occurs[sudo->chess[row+2][col+2]];

      if (std::count(occurs, occurs+10, 1) != NUM)
        return false;
    }
  }
  return true;
}
