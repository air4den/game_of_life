# Conway's Game of Life

Conway's Game of Life is a _classic_ cellular automaton and is turing complete! Watch evolution unfold based on a set of rules. Here is my C++ implementation. 

<img src=images/gosper.gif height=250>

### Rules
- Live Cells:
    - If has fewer than 2 neighbors: dies from underpopulation
    - If has greater than 3 neighbors: dies from overpopulation
- Dead Cells
    - If exactly 3 live neighbors: alive via reproduction

I highly recommend reading more about Conway's Game of Life [here](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life).


## Build & Run
Install [SFML](https://www.sfml-dev.org/documentation/3.0.0/) and Make if you don't have them already. 

`make run` OR `make build` && `./game_of_life` to compile run.

`make clean` to clean.


## Controls
- `M`, `Space` keys to toggle between modes:
    - `EDIT`: Change the initial cell configuration. Click on each cell to toggle its state.
    - `RUN`: Watch the simulation progress. Every generation is calculated from the states of the previous generation. 
- `R` key: Reset grid with all dead cells. 
- `1` key: Preset configuration for [Gosper Gun configuration](https://en.wikipedia.org/wiki/Gun_(cellular_automaton)). 


## Example Patterns

We can have a lot of fun with the different patterns possible through _Game of Life_. The are generally divided into three categories: still lifes, oscillators, and spaceships. These are just a few examples of the many patterns that exist!

| | Still Life | | 
| :---: | :---: | :---: |
Block | Beehive | Boat |
<img src=images/block.png width=75> | <img src=images/bee_hive.png width=75> | <img src=images/bee_hive.png width=75> | 

| | Oscillators | | 
| :---: | :---: | :---: |
| Blinker | Beacon | Pulsar |
| <img src=images/blinker.gif width=75> | <img src=images/beacon.gif width=75> | <img src=images/pulsar.gif width=75> | 
| Period: 2 | 2 | 3 | 

| Spaceships | 
| :---: |
| Glider | 
| <img src=images/glider.gif width=75> | 