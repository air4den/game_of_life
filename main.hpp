#include <array>
#include <tuple>
#include <SFML/Graphics.hpp>

const int ROWS = 50;
const int COLS = 50;
const int CELL_SIZE = 16; 
const int DT = 200;     // milliseconds

enum Viz_mode { RUN, EDIT };

using Array2D = std::array<std::array<bool, COLS>, ROWS>;

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

class Viz {
    private:
        Grid sim_grid;
        Viz_mode mode;
        int count_gen;
        sf::RenderWindow window;
        sf::Font font;

        void render();
        void draw_grid();
        void draw_info();
    public:
        Viz();
        ~Viz();
        void run();
        std::tuple<int, int> get_cell_from_mouse();

};