#include "grid.hpp"
#include <iostream>

namespace dolomiti::interview::p1 {

std::ostream& operator<<(std::ostream& output, const StatoCella& stato) {
    output << static_cast<char>(stato);
    return output;
}

Grid::Grid(int size) : cells_(size, std::vector<Cell>(size, StatoCella::VUOTA)), numero(size) {}

void Grid::Set(StatoCella value, const Position& pos) {
    cells_[pos.x][pos.y].value = value;
}

StatoCella Grid::GetValue(const Position& pos) const {
    return cells_[pos.x][pos.y].value;
}

bool Grid::posizioneNonValida(Position pos) const {
    return pos.x >= numero || pos.y >= numero || pos.x < 0 || pos.y < 0;
}

bool Grid::occupata(Position pos) const {
    return GetValue(pos) != StatoCella::VUOTA;
}

bool Grid::ostacolo(Position pos) const {
    return GetValue(pos) == StatoCella::OSTACOLO;
}

bool Grid::stessaposizionerobot(Position pos) const {
    return GetValue(pos) == StatoCella::ROBOT1 || GetValue(pos) == StatoCella::ROBOT2;
}

bool Grid::stessacella(Position pos) const {
    StatoCella value = GetValue(pos);
    return value == StatoCella::ROBOT1 || value == StatoCella::ROBOT2 || value == StatoCella::TRAIL1 || value == StatoCella::TRAIL2;
}

} // namespace dolomiti::interview::p1
