#pragma once
#ifndef INTERVIEW_GRID_HPP
#define INTERVIEW_GRID_HPP

#include "common.hpp"
#include <iostream>

namespace dolomiti::interview::p1 {


enum class StatoCella {
    VUOTA, OSTACOLO, ROBOT1, ROBOT2, TRAIL1, ROBOT
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

/*
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

#include "common.hpp"
#include "grid.hpp"
#include "robot.hpp"

using namespace dolomiti::interview::p1;

bool posizioneUguale(const Position& a, const Position& b) {
    return a.x == b.x && a.y == b.y;
}

int main(int argc, char **argv) {
    int n;
    std::cout << "Inserisci la dimensione della griglia: ";
    std::cin >> n;

    while (n <= 0) {
        std::cout << "Inserisci la dimensione della griglia: ";
        std::cin >> n;
    }

    Grid mappa(n);

    int numost;
    std::cout << "Quanti ostacoli vuoi inserire? ";
    std::cin >> numost;

    for (int i = 0; i < numost; i++) {
        std::cout << "Inserisci la posizione dell'ostacolo " << i + 1 << "\n";
        int x1, y1;
        std::cout << "X: ";
        std::cin >> x1;
        std::cout << "Y: ";
        std::cin >> y1;

        while (mappa.posizioneNonValida(Position(x1, y1))) {
            std::cout << "Posizione non valida. Inserisci di nuovo.\n";
            std::cout << "X: ";
            std::cin >> x1;
            std::cout << "Y: ";
            std::cin >> y1;
        }

        mappa.Set(StatoCella::OSTACOLO, Position(x1, y1));
    }

    int numRobots;
    std::cout << "Quanti robot vuoi inserire? ";
    std::cin >> numRobots;

    std::vector<Robot> robots;
    std::vector<int> robotNumbers;

    for (int i = 0; i < numRobots; ++i) {
        std::cout << "Inserisci la posizione iniziale del robot " << i + 1 << "\n";
        int x, y;
        std::cout << "X: ";
        std::cin >> x;
        std::cout << "Y: ";
        std::cin >> y;

        while (mappa.posizioneNonValida(Position(x, y)) || mappa.occupata(Position(x, y))) {
            std::cout << "Posizione del robot non valida. Inserisci di nuovo.\n";
            std::cout << "X: ";
            std::cin >> x;
            std::cout << "Y: ";
            std::cin >> y;
        }

        int robotNumber;
        std::cout << "Inserisci il numero per il robot " << i + 1 << " (>= 5): ";
        std::cin >> robotNumber;

        while (robotNumber < 5) {
            std::cout << "Il numero del robot deve essere maggiore o uguale a 5. Inserisci di nuovo: ";
            std::cin >> robotNumber;
        }

        robots.emplace_back(x, y);
        robotNumbers.push_back(robotNumber); 
        mappa.Set(StatoCella(robotNumber), Position(x, y));
    }

       std::cout << "Grid :" << std::endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << mappa.GetValue(Position(j, i)) << " ";
        }
        std::cout << std::endl;
    }

    std::vector<std::string> moves(numRobots);
    for (int i = 0; i < numRobots; ++i) {
        std::cout << "Inserisci le mosse del robot " << i + 1 << ": ";
        std::cin >> moves[i];
    }

    int maxMoves = 0;
    for (const auto &moveStr : moves) {
        if (moveStr.length() > maxMoves) {
            maxMoves = moveStr.length();
        }
    }

    for (int i = 0; i < maxMoves; ++i) {
        for (int j = 0; j < numRobots; ++j) {
            if (i < moves[j].length()) {
                char move = moves[j][i];
                Position p = robots[j].posizione();
                Position f = posizionefutura(p, move);

                if (mappa.posizioneNonValida(f)) {
                    std::cout << "Il robot " << robotNumbers[j] << " è fuori dalla griglia." << std::endl;
                    continue;
                }
                if (mappa.ostacolo(f)) {
                    std::cout << "Il robot " << robotNumbers[j] << " incontra un ostacolo." << std::endl;
                    continue;
                }
                bool collision = false;
                for (int k = 0; k < numRobots; ++k) {
                    if (k != j && posizioneUguale(robots[k].posizione(), f)) {
                        std::cout << "Il robot " << robotNumbers[j] << " incontra il robot " << robotNumbers[k] << "." << std::endl;
                        collision = true;
                        break;
                    }
                }
                if (collision) continue;

                robots[j].muovererobot(move);
                mappa.Set(StatoCella::TRAIL1, p);
                mappa.Set(StatoCella(robotNumbers[j]), robots[j].posizione()); 
            }
        }
    }

    std::cout << "Grid finale:" << std::endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << mappa.GetValue(Position(j, i)) << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < numRobots; ++i) {
        Position finale = robots[i].posizione();
        std::cout << "Posizione finale del robot " << robotNumbers[i] << ": " << finale.x << "," << finale.y << std::endl;
    }

    return 0;
}
*/