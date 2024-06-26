#include "robot.hpp"
#include <iostream>


namespace dolomiti::interview::p1{

	Robot::Robot(int x,int y) {
		posa.x =x;
		posa.y =y;
	}


	void Robot::riempiposizione(int x,int y){
		posa = Position(x,y);

	}
	

	
	

	Position Robot::posizione(){
		return posa;
	}

	

	void Robot::muovererobot(char mossa, int s){

	    if(mossa == 'R'){
	    	posa.x = posa.x + s;
	    }
	    else if(mossa == 'L'){
	    	posa.x = posa.x - s;
	    }
	    else if(mossa == 'U'){
	    	posa.y = posa.y - s;
	    }
	    else if(mossa == 'D'){
	    	posa.y = posa.y + s;
	    }
	    else if(mossa == 'S'){
	    	posa.y = posa.y;
	    	posa.x = posa.x;
	    }


	}





}