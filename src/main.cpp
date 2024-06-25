#include <iostream>
#include <string>
#include <vector>

#include "common.hpp"
#include "grid.hpp"
#include "robot.hpp"

using namespace dolomiti::interview::p1;



int
main(int argc, char **argv)
{

    int n;
    std::cout << "Inserisci la dimensione della griglia: ";
    std::cin >> n;



    while(n<=0){
        std::cout << "Inserisci la dimensione della griglia: ";
        std::cin >> n;      
     }

     Grid mappa(n);
     
    int numost;
    std::cout << "Quanti ostacoli vuoi inserire? ";
    std::cin >> numost;

    for (int i = 0; i < numost; i++) {
        std::cout << "Inserisci la posizione dell'ostacolo\n"<< i+1;
        int x1;
        int y1;
        std::cout << "X: ";
        std::cin >> x1;
        std::cout << "Y: ";
        std::cin >> y1;


        while(mappa.posizioneNonValida(Position(x1,y1))){
            std::cout << "Inserisci la posizione dell'ostacolo\n";
            std::cout << "X: ";
            std::cin >> x1;
            std::cout << "Y: ";
            std::cin >> y1;
        }

        mappa.Set(StatoCella::OSTACOLO, Position(x1,y1));
    }

 
    std::cout << "Inserisci la posizione inizale del robot\n";
    int x;
    int y;
    std::cout << "X: ";
    std::cin >> x;
    std::cout << "Y: ";
    std::cin >> y;

    Robot robot(x,y);
    
    
   while(mappa.posizioneNonValida(Position(x, y)) || mappa.occupata(Position(x, y))) {
        std::cout << "Posizione del robot non valida. Inserisci di nuovo.\n";
        std::cout << "X: ";
        std::cin >> x;
        std::cout << "Y: ";
        std::cin >> y;
    }

    robot.riempiposizione(x, y);
    mappa.Set(StatoCella::ROBOT1, Position(x, y));

    std::cout << "Inserisci la posizione inizale del secondo robot\n";
    int x2, y2;
    std::cout << "X: ";
    std::cin >> x2;
    std::cout << "Y: ";
    std::cin >> y2;

    Robot robot2(x2, y2);

    while(mappa.posizioneNonValida(Position(x2, y2)) || mappa.occupata(Position(x2, y2))) {
        std::cout << "Posizione del secondo robot non valida. Inserisci di nuovo.\n";
        std::cout << "X: ";
        std::cin >> x2;
        std::cout << "Y: ";
        std::cin >> y2;
    }

    robot2.riempiposizione(x2, y2);
    mappa.Set(StatoCella::ROBOT2, Position(x2, y2)); 
   
   
 


    std::cout << "Grid:" << std::endl; 
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << mappa.GetValue(Position(j,i)) << " ";
        }
        std::cout << std::endl;
    }


    std::string moves_str;
    std::cout << "Inserisci le mosse del primo robot: ";
    std::cin >> moves_str;


    std::string moves_str2;
    std::cout << "Inserisci le mosse del secondo robot: ";
    std::cin >> moves_str2;


    //Grid grid1, grid2;
    //grid1.GetValue(Position(0,0));
    //grid2.GetValue(Position(0,0));
    //Grid newGrid = grid1.create(3, StatoCella::ROBOT1);

   //moves_robot1: std::string
   //moves_robot2: std::string
   // .length()
   // i: 0; i<std::max(moves_robot2.length(), ...)
    


    int max_moves = std::max(moves_str.length(), moves_str2.length());

    for (int i = 0; i < max_moves; ++i) {
        if (i < moves_str.length()) {
            char move = moves_str[i];
            Position p = robot.posizione();
            Position f = posizionefutura(p, move);

            if (mappa.posizioneNonValida(f)) {
                std::cout << "Il primo robot è fuori dalla griglia." << std::endl;
                break;
            }
            if (mappa.ostacolo(f)) {
                std::cout << "Il primo robot incontra un ostacolo." << std::endl;
                break;
            }
            if (mappa.GetValue(f) == StatoCella::ROBOT2) {
                std::cout << "Il primo robot incontra il secondo robot." << std::endl;
                break;
            }

            robot.muovererobot(move);
            mappa.Set(StatoCella::VUOTA, p);  
            mappa.Set(StatoCella::ROBOT1, robot.posizione());  
        }

        if (i < moves_str2.length()) {
            char move = moves_str2[i];
            Position p = robot2.posizione();
            Position f = posizionefutura(p, move);

            if (mappa.posizioneNonValida(f)) {
                std::cout << "Il secondo robot è fuori dalla griglia." << std::endl;
                break;
            }
            if (mappa.ostacolo(f)) {
                std::cout << "Il secondo robot incontra un ostacolo." << std::endl;
                break;
            }
            if (mappa.GetValue(f) == StatoCella::ROBOT1) {
                std::cout << "Il secondo robot incontra il primo robot." << std::endl;
                break;
            }

            robot2.muovererobot(move);
            mappa.Set(StatoCella::VUOTA, p);  
            mappa.Set(StatoCella::ROBOT2, robot2.posizione()); 
        }

       
     
    }

    Position finale = robot.posizione();
    Position finale2 = robot2.posizione();
 

   

    std::cout << "Grid finale:" << std::endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << mappa.GetValue(Position(j, i)) << " ";
        }
        std::cout << std::endl;
    }


   std::cout << "Posizione finale primo robot  : " << finale.x << "," << finale.y ;
   std::cout << "\nPosizione finale secondo robot : " << finale2.x << "," << finale2.y << "\n" ;

 

    return 0;


}
