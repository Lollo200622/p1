#include "grid.hpp"

#include <iostream>

namespace dolomiti::interview::p1 {

//int Grid::contatore = 0;

std::ostream& operator<<(std::ostream& output, const StatoCella& stato) {
    output << static_cast<int>(stato);
    return output;
}

Grid::Grid(int size) : cells_(size, std::vector<Cell>(size, StatoCella::VUOTA)) {
		//std::cout << "grid constructor "<< size;
		numero = size; 
		//contatore++;
		
}
void Grid::Set(StatoCella value, const Position& pos)
{
    cells_[pos.x][pos.y] = value;
}

StatoCella
Grid::GetValue(const Position& pos)
{
    return cells_[pos.x][pos.y].value;
}


bool Grid::posizioneNonValida(Position pos){
	if(pos.x>=numero || pos.y>=numero || pos.x<0 || pos.y<0){
		return true;
    }
    else {
		return false ;
	}
}

bool Grid::occupata(Position st){
	if(GetValue(Position(st.x , st.y))!=StatoCella::VUOTA){
		return true;
	}
	else {
		return false; 
	}	
}
 


/*bool Grid::PosizioneRnonvalida(Position rob){
	
	if( rob.x>=numero || rob.y>=numero || rob.x<0 || rob.y<0){
		return true ; 
	}
	else {
		return false ; 
	}
}*/

bool Grid::ostacolo(Position st){
	if(GetValue(Position(st.x , st.y))==StatoCella::OSTACOLO){
		return true;
	}
	else {
		return false; 
	}
}

bool Grid::stessaposizionerobot(Position same){
	if(GetValue(Position(same.x , same.y))==StatoCella::ROBOT1){
		return true;
	}
	else {
		return false; 
	}
}


bool Grid::stessacella(Position bos) {
    StatoCella value = GetValue(bos);
    return (value == StatoCella::ROBOT1 || value == StatoCella::ROBOT2); 
}















 } // namespace dolomiti::interview::a1