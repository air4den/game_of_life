#include "grid.hpp"

Grid::Grid(): size_y(ROWS_Y), size_x(COLS_X), grid(COLS_X, std::vector<bool>(ROWS_Y, false)), population(0) {}

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
    Array2D next_grid(size_x, std::vector<bool>(size_y, false));
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
    Array2D new_grid(size_x, std::vector<bool>(size_y, false));
    grid = new_grid;
    population = 0;
}

void Grid::resize_grid(int new_x, int new_y)
{
    grid.resize(new_x);
    for (int col=0; col<new_x; col++) {
        grid[col].resize(new_y, false);
    }
    size_x = new_x;
    size_y = new_y;
}

void Grid::reset_grid_gospergun()
{
    Array2D new_grid(size_x, std::vector<bool>(size_y, false));
    std::vector<std::tuple<int, int>> gun_cells = 
    {
        {1, 6}, {2, 6}, {1, 7}, {2, 7},
        {11, 6}, {11, 7}, {11, 8}, {12, 5}, {12, 9}, {13, 4}, {13, 10}, {14, 4}, {14, 10},
        {15, 7}, {16, 5}, {16, 9}, {17, 6}, {17, 7}, {17, 8}, {18, 7},
        {21, 4}, {21, 5}, {21, 6}, {22, 4}, {22, 5}, {22, 6}, 
        {23, 3}, {23, 7}, {25, 2}, {25, 3}, {25, 7}, {25, 8},
        {35, 4}, {35, 5}, {36, 4}, {36, 5}, 
    };
    int x, y;
    for (const auto &vec : gun_cells) {
        x = std::get<0>(vec);
        y = std::get<1>(vec);
        new_grid[x][y] = true;
    }
    grid = new_grid;
}