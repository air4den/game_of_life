#include <array>

#ifndef CONSTS
#define CONSTS

const int ROWS = 50;
const int COLS = 50;
const int CELL_SIZE = 16; 
const int DT = 200; // milliseconds

#endif

using Array2D = std::array<std::array<bool, COLS>, ROWS>;

