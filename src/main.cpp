#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

#include "common.hpp"
#include "grid.hpp"
#include "robot.hpp"

using namespace dolomiti::interview::p1;

bool posizioneUguale(const Position& a, const Position& b) {
    return a.x == b.x && a.y == b.y;
}

std::vector<Position> calcolaPosizioniIntermedie(const Position& start, const Position& end, int speed) {
    std::vector<Position> posizioni;
    int dx = (end.x - start.x) / speed;
    int dy = (end.y - start.y) / speed;

    for (int i = 1; i < speed; ++i) {
        posizioni.push_back(Position(start.x + i * dx, start.y + i * dy));
    }
    return posizioni;
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
    std::vector<int> robotSpeeds;

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

        int robotSpeed;
        std::cout << "Inserisci la velocità del robot " << i + 1 << ": ";
        std::cin >> robotSpeed;

        while (robotSpeed <= 0) {
            std::cout << "La velocità del robot deve essere maggiore di 0. Inserisci di nuovo: ";
            std::cin >> robotSpeed;
        }

        robots.emplace_back(x, y);
        robotNumbers.push_back(robotNumber); 
        robotSpeeds.push_back(robotSpeed);
        mappa.Set(StatoCella(robotNumber), Position(x, y));
    }

    std::cout << "Grid iniziale:" << std::endl;
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
                Position f = posizionefutura(p, move, robotSpeeds[j]);

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

                std::vector<Position> posizioniIntermedie = calcolaPosizioniIntermedie(p, f, robotSpeeds[j]);
                 bool movimentoValido = true;
                for (const auto& posIntermedia : posizioniIntermedie) {
                    if (mappa.ostacolo(posIntermedia) || mappa.occupata(posIntermedia)) {
                        std::cout << "Il robot " << robotNumbers[j] << " incontra un ostacolo o un altro robot nella posizione intermedia." << std::endl;
                        collision = true;
                        movimentoValido = false;
                        break;
                    }
                }

               
                
               // if (collision) continue;
                if (!collision) {
                    for (const auto& posIntermedia : posizioniIntermedie) {
                    mappa.Set(StatoCella::TRAIL1, posIntermedia);
                }
                robots[j].muovererobot(move, robotSpeeds[j]);
               mappa.Set(StatoCella::TRAIL1, p);
               mappa.Set(StatoCella(robotNumbers[j]), robots[j].posizione()); 
           }
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
