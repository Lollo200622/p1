#include "common.hpp"

namespace dolomiti::interview::p1 {
Position
EstimateFinalPosition(const Position &, const std::vector<Move> &, const Grid &)
{
    // TODO
    return Position(0,0);
}

std::vector<Move>
GetMoves(const std::string &)
{
    // TODO
    return std::vector<Move>();
}

bool
DoPathsCollide(const Position &, const Position &, const std::vector<Move> &,
               const std::vector<Move> &, const Grid &)
{
    // TODO
    return false;
}
bool
CanReachDestination(const Position &, const std::vector<Move> &, const Grid &)
{
    // TODO
    return false;
}
Position posizionefutura(Position fut, char mos){
	 if(mos == 'R'){
    	fut.x = fut.x + 1;
    }
    else if(mos == 'L'){
    	fut.x = fut.x - 1;
    }
    else if(mos == 'U'){
    	fut.y = fut.y - 1;
    }
    else if(mos == 'D'){
    	fut.y = fut.y + 1;
    }
    else if(mos == 'S'){
        fut.y = fut.y;
        fut.x = fut .x;
    }
    return fut;
}



}