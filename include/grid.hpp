#pragma once
#ifndef INTERVIEW_GRID_HPP
#define INTERVIEW_GRID_HPP

#include "common.hpp"
#include <iostream>

namespace dolomiti::interview::p1 {


enum class StatoCella {
    VUOTA, OSTACOLO, ROBOT1, ROBOT2, TRAIL1, TRAIL2
};

std::ostream& operator<<(std::ostream& output, const StatoCella& stato);



class Grid
{
public:
    explicit Grid(int size);

    void Set(StatoCella value, const Position& pos);
    StatoCella GetValue(const Position& pos);
  
    bool posizioneNonValida(Position pos);
    //bool ostacolononvalido(Position pos);
    //bool PosizioneRnonvalida(Position rob);
    bool occupata(Position st);
    bool ostacolo(Position st);
    bool stessaposizionerobot(Position same);
    bool stessacella(Position bos);
    
    /*static Grid create(int size, StatoCella value) {
        Grid grid(size);
        for (int i=0; i<size; ++i) {
            for (int j=0; j<size; ++j) {
                grid.Set(value, Position(i, j));
            }     
        }
        return grid;
    }*/
    


private:

    struct Cell
    {
        Cell(StatoCella v) : value(v){};
        Cell() : value(StatoCella::VUOTA){};

        StatoCella value;
    };


    int numero; 
    std::vector<std::vector<Cell>> cells_;
};

}  // namespace dolomiti::interview::a1



#endif  // INTERVIEW_GRID_HPP
