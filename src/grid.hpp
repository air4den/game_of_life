#include "main.hpp"
#include <vector>

class Grid {
    private:
        static std::vector<std::pair<int, int>> directions;
    public:
        int size_y;
        int size_x;
        Array2D grid;
        int population;

        Grid();
        ~Grid();
        int num_neighbors(int x, int y);
        void step();
        void toggle_cell(int x, int y);
        void reset_grid();
};