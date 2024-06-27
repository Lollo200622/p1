#include "robot.hpp"

//al posto di char mossa mettere enum 
// posizione futura la deve fare il robot 
// il robot deve conoscere la sua velocità, e il suo ID 
// creare gliglia dinamica, il robot può andare dove vuole quindi può

namespace dolomiti::interview::p1 {

    Robot::Robot(int x, int y, int id, int speed)
        : posa(x, y), id(id), speed(speed) {
            
        }

    void Robot::riempiPosizione(int x, int y) {
        posa = Position(x, y);
    }

    Position Robot::posizione() const {
        return posa;
    }


    void Robot::muovereRobot(Move move) {
        if (move == Move::RIGHT) {
            posa.x += speed;
        } else if (move == Move::LEFT) {
            posa.x -= speed;
        } else if (move == Move::UP) {
            posa.y -= speed;
        } else if (move == Move::DOWN) {
            posa.y += speed;
        } else if (move == Move::STAY) {
            
        }
    }

    Position Robot::posizioneFutura(Move move) const {
        Position future = posa;
        if (move == Move::RIGHT) {
            future.x += speed;
        } else if (move == Move::LEFT) {
            future.x -= speed;
        } else if (move == Move::UP) {
            future.y -= speed;
        } else if (move == Move::DOWN) {
            future.y += speed;
        } else if (move == Move::STAY) {
           
        }
        return future;
    }
    int Robot::getID() const {
        return id;
    }

    int Robot::getSpeed() const {
        return speed;
    }

} // namespace dolomiti::interview::p1
