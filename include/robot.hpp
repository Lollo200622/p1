#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "common.hpp"

namespace dolomiti::interview::p1{

	class Robot{

	public: 
		Robot(int x, int y);
		void riempiposizione(int x,int y);
		
		void muovererobot(char mossa, int s);
		Position posizione();
		


	private:
 		Position posa;
};

}

#endif