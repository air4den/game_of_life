#include "grid.hpp"

#include <SFML/Graphics.hpp>
#include <tuple>

const std::string FONT_PATH = "./font/futura.ttf";

enum Viz_mode { RUN, EDIT };

class Viz {
    private:
        Grid sim_grid;
        Viz_mode mode;
        sf::RenderWindow window;
        sf::Font font;

        void render();
        void draw_grid();
        void draw_info();
    public:
        Viz();
        ~Viz();
        void run();
};