    

#pragma once
#ifndef INTERVIEW_GRID_HPP
#define INTERVIEW_GRID_HPP

#include "common.hpp"
#include <iostream>

//al posto di char mossa mettere enum 
// posizione futura la deve fare il robot 
// il robot deve conoscere la sua velocità, e il suo ID 
// creare gliglia dinamica, il robot può andare dove vuole quindi può 


namespace dolomiti::interview::p1 {

    enum class StatoCella : char {
        VUOTA = '+', OSTACOLO = 'X', ROBOT1 = 'A', ROBOT2 = 'B', TRAIL1 = '-', TRAIL2 = '2'
    };

    std::ostream& operator<<(std::ostream& output, const StatoCella& stato);

    class Grid
    {
    public:
        explicit Grid(int size);

        void Set(StatoCella value, const Position& pos);
        StatoCella GetValue(const Position& pos) const;
  
        bool posizioneNonValida(Position pos) const;
        bool occupata(Position pos) const;
        bool ostacolo(Position pos) const;
        bool stessaposizionerobot(Position pos) const;
        bool stessacella(Position pos) const;

    private:

        struct Cell
        {
            Cell(StatoCella v) : value(v) {};
            Cell() : value(StatoCella::VUOTA) {};

            StatoCella value;
        };

        int numero; 
        std::vector<std::vector<Cell>> cells_;
    };

} 

#endif  // INTERVIEW_GRID_HPP
