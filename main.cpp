#include "main.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

Grid::Grid(): grid{} 
{
    this->size_y = ROWS;
    this->size_x = COLS;
    this->population = 0;
}

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
    for (int x=0; x<this->size_x; x++) {
        for (int y=0; y<this->size_y; y++) {
            bool next_state = false;
            int neighbors = num_neighbors(x, y);
            if (this->grid[x][y] == 1) {
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
    this->grid = next_grid;
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
    this->grid = new_grid;
    population = 0;
}




Viz::Viz(): sim_grid(), mode(EDIT), count_gen(0)
{
    this->window.create(
        sf::VideoMode(sim_grid.size_x * CELL_SIZE, sim_grid.size_y * CELL_SIZE), 
        "Conway's Game of Life"
        );
    if(!font.loadFromFile("futura.ttf")) {
        fprintf(stderr, "Couldn't load font from path.");
        exit(1); 
    }
}

Viz::~Viz() {}

void Viz::draw_grid()
{
    // TODO: Rector so that it dynamically adjusts when users changes window size
    sf::RectangleShape line;
    line.setFillColor(sf::Color(100, 100, 100));

    // Vertical Lines
    for (int x=0; x<sim_grid.size_x; x++) {
        line.setSize(sf::Vector2f(1, window.getSize().y));
        line.setPosition(x * CELL_SIZE, 0);
        window.draw(line);
    }
    // Horizontal Lines 
    for (int y=0; y<sim_grid.size_y; y++) {
        line.setSize(sf::Vector2f(window.getSize().x, 1));
        line.setPosition(0, y * CELL_SIZE);
        window.draw(line);
    }
}

void Viz::draw_info()
{
    std::string mode_str = (mode == EDIT) ? "Mode: EDIT" : "Mode: RUN";
    std::string population_str = "Population: " + std::to_string(sim_grid.population);
    std::string info_str = mode_str + "\n" + population_str + "\n"; 

    sf::Text info_text;
    info_text.setFont(font);
    info_text.setCharacterSize(20);
    info_text.setFillColor(sf::Color::White);
    info_text.setPosition(10, 10);
    info_text.setString(info_str);
    window.draw(info_text);

}

void Viz::render()
{
    window.clear();
    for (int x=0; x<sim_grid.size_x; x++) {
        for (int y=0; y<sim_grid.size_y; y++) 
        {
            sf::RectangleShape cell;
            cell.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            cell.setPosition(x*CELL_SIZE, y*CELL_SIZE);

            if (sim_grid.grid[x][y]) {
                // Fill White
                cell.setFillColor(sf::Color(255, 255, 255));
            } else {
                cell.setFillColor(sf::Color(0, 0, 0));
            }

            window.draw(cell);
        }
    }
    draw_grid();
    draw_info();
}

void Viz::run() 
{
    while (this->window.isOpen()) {

        // Event Handling
        sf::Event e;
        while (this->window.pollEvent(e)) {
            switch (e.type) {
                case sf::Event::Closed:
                    this->window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (e.key.code == sf::Keyboard::M) {
                        mode = (mode == RUN) ? EDIT : RUN;
                    }
                    if (e.key.code == sf::Keyboard::R) {
                        sim_grid.reset_grid();
                    }
                    break;
                case sf::Event::MouseButtonPressed:
                    if (mode == EDIT) {
                        if (e.mouseButton.button == sf::Mouse::Left) {
                            int mouse_x = e.mouseButton.x;
                            int mouse_y = e.mouseButton.y;

                            int win_x = window.getSize().x;
                            int win_y = window.getSize().y;

                            if (mouse_x >= 0 && mouse_x < win_x && mouse_y >=0 && mouse_y < win_y) {
                                this->sim_grid.toggle_cell(mouse_x / CELL_SIZE, mouse_y / CELL_SIZE);
                            }
                        }

                        
                    }
                default:
                    break;
            }
        }

        if (mode == RUN) {
            std::this_thread::sleep_for(std::chrono::milliseconds(DT));   // TODO: this needs to be place somewhere else b/c there's a lad
            sim_grid.step();
        } 
        render();
        this->window.display();
    }
}

int main() {
    Viz v;
    v.run();
    return 0;
}

