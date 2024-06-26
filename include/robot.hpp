#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "common.hpp"

namespace dolomiti::interview::p1 {

    class Robot {
    public:
        Robot(int x, int y, int id, int speed);

        void riempiPosizione(int x, int y);
        Position posizione() const;
        void muovereRobot(Move move);
        Position posizioneFutura(Move move) const;
        int getID() const;
        int getSpeed() const;

    private:
        Position posa;
        int id;
        int speed;
    };
 /* if (!collision) {
                    for (const auto& posIntermedia : posizioniIntermedie) {
                    mappa.Set(StatoCella::TRAIL1, posIntermedia);
                }
                  robots[j].muovereRobot(move);
               mappa.Set(StatoCella::TRAIL1, p);
               mappa.Set(StatoCella(robots[j].getID()), f);
           }*/
}

#endif // ROBOT_HPP


