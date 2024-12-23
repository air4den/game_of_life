#include "grid.hpp"

Grid::Grid(): size_y(ROWS), size_x(COLS), grid{}, population(0) {}

std::vector<std::pair<int, int>> Grid::directions = {
    {-1,-1}, {-1,0}, {-1, 1},
    {0, -1},          {0, 1},
    {1, -1}, {1, 0}, {1, 1}
};

Grid::~Grid() {}

int Grid::num_neighbors(int x, int y) 
{
    int num_neighbors = 0;
    for (const auto &dir : directions) {
        int new_y = y + dir.second;
        int new_x = x + dir.first;
        if (new_x >=0 && new_x < this->size_x && new_y >=0 && new_y < this->size_y) {
            num_neighbors += grid[new_x][new_y] ? 1 : 0;
        }
    }
    return num_neighbors;
}

void Grid::step() 
{
    Array2D next_grid  = {};
    int pop = 0;
    for (int x=0; x<size_x; x++) {
        for (int y=0; y<size_y; y++) {
            bool next_state = false;
            int neighbors = num_neighbors(x, y);
            if (grid[x][y] == 1) {
                // Cases where cell is alive
                if (neighbors >= 2 && neighbors <= 3) {
                    next_state = true;
                    pop++;
                }
            } else {
                // Cases where cell is dead
                if (neighbors == 3) {
                    next_state = true;
                    pop++;
                }
            }
            next_grid[x][y] = next_state;
        }
    }
    population = pop;
    grid = next_grid;
}

void Grid::toggle_cell(int x, int y) 
{
    if(grid[x][y]) {
        grid[x][y] = false;
        population -= 1;
    } else {
        grid[x][y] = true;
        population += 1;
    }
}

void Grid::reset_grid()
{
    Array2D new_grid = {};
    grid = new_grid;
    population = 0;
}