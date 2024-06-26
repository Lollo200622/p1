#include <iostream>
#include <string>
#include <vector>

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

int main() {
    int n;
    std::cout << "Inserisci la dimensione della griglia: ";
    std::cin >> n;

    while (n <= 0) {
        std::cout << "Dimensione della griglia non valida. Reinserisci: ";
        std::cin >> n;
    }

    Grid mappa(n);

    int numOstacoli;
    std::cout << "Quanti ostacoli vuoi inserire? ";
    std::cin >> numOstacoli;

    for (int i = 0; i < numOstacoli; ++i) {
        std::cout << "Inserisci la posizione dell'ostacolo " << i + 1 << "\n";
        int x, y;
        std::cout << "X: ";
        std::cin >> x;
        std::cout << "Y: ";
        std::cin >> y;

        while (mappa.posizioneNonValida(Position(x, y))) {
            std::cout << "Posizione non valida. Reinserisci.\n";
            std::cout << "X: ";
            std::cin >> x;
            std::cout << "Y: ";
            std::cin >> y;
        }

        mappa.Set(StatoCella::OSTACOLO, Position(x, y));
    }

    int numRobots;
    std::cout << "Quanti robot vuoi inserire? ";
    std::cin >> numRobots;

    std::vector<Robot> robots;

    for (int i = 0; i < numRobots; ++i) {
        std::cout << "Inserisci la posizione iniziale del robot " << i + 1 << "\n";
        int x, y;
        std::cout << "X: ";
        std::cin >> x;
        std::cout << "Y: ";
        std::cin >> y;

        while (mappa.posizioneNonValida(Position(x, y)) || mappa.occupata(Position(x, y))) {
            std::cout << "Posizione del robot non valida. Reinserisci.\n";
            std::cout << "X: ";
            std::cin >> x;
            std::cout << "Y: ";
            std::cin >> y;
        }

        char id;
        std::cout << "Inserisci l'ID per il robot " << i + 1 ;
        std::cin >> id;

       
        int speed;
        std::cout << "Inserisci la velocità del robot " << i + 1 << ": ";
        std::cin >> speed;

        while (speed <= 0) {
            std::cout << "La velocità del robot deve essere maggiore di 0. Reinserisci: ";
            std::cin >> speed;
        }

        robots.emplace_back(x, y, id, speed);
        mappa.Set(StatoCella(id), Position(x, y));
    }

    std::cout << "Griglia iniziale:" << std::endl;
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
                char moveChar = moves[j][i];
                Move move;
                if (moveChar == 'R') {
                    move = Move::RIGHT;
                } else if (moveChar == 'L') {
                    move = Move::LEFT;
                } else if (moveChar == 'U') {
                    move = Move::UP;
                } else if (moveChar == 'D') {
                    move = Move::DOWN;
                } else if (moveChar == 'S') {
                    move = Move::STAY;
                } else {
                    continue; // Ignora movimenti non validi
                }

                Position p = robots[j].posizione();
                Position f = robots[j].posizioneFutura(move);

                if (mappa.posizioneNonValida(f)) {
                    std::cout << "Il robot " << robots[j].getID() << " è fuori dalla griglia." << std::endl;
                    continue;
                }
                if (mappa.ostacolo(f)) {
                    std::cout << "Il robot " << robots[j].getID() << " incontra un ostacolo." << std::endl;
                    continue;
                }

                bool collision = false;
                for (int k = 0; k < numRobots; ++k) {
                    if (k != j && posizioneUguale(robots[k].posizione(), f)) {
                        std::cout << "Il robot " << robots[j].getID() << " incontra il robot " << robots[k].getID() << "." << std::endl;
                        collision = true;
                        break;
                    }
                }

                std::vector<Position> posizioniIntermedie = calcolaPosizioniIntermedie(p, f, robots[j].getSpeed());

                for (const auto& pos : posizioniIntermedie) {
                    if (mappa.ostacolo(pos)) {
                        std::cout << "Il robot " << robots[j].getID() << " incontra un ostacolo durante il movimento." << std::endl;
                        collision = true;
                        break;
                    }
                    for (int k = 0; k < numRobots; ++k) {
                        if (k != j && posizioneUguale(robots[k].posizione(), pos)) {
                            std::cout << "Il robot " << robots[j].getID() << " incontra il robot " << robots[k].getID() << " durante il movimento." << std::endl;
                            collision = true;
                            break;
                        }
                    }
                    if (collision) {
                        break;
                    }
                }

                
               if (!collision) {
                    for (const auto& posIntermedia : posizioniIntermedie) {
                    mappa.Set(StatoCella::TRAIL1, posIntermedia);
                }
                  robots[j].muovereRobot(move);
               mappa.Set(StatoCella::TRAIL1, p);
               mappa.Set(StatoCella(robots[j].getID()), f);
           }
            }
        }
    }

    std::cout << "Griglia finale:" << std::endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << mappa.GetValue(Position(j, i)) << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < numRobots; ++i) {
        Position finale = robots[i].posizione();
        std::cout << "Posizione finale del robot " << robots[i].getID() << ": " << finale.x << "," << finale.y << std::endl;
    }

    return 0;
}
