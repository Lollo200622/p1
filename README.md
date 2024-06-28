## Interview problem set


Funzionalità del programma 

- Definizione della dimensione della griglia.
- Impostazione delle coordinate della nuova origine della griglia.
- Inserimento di ostacoli nella griglia.
- Inserimento di robot con posizione iniziale e velocità specifiche.
- Movimentazione dei robot in base a una sequenza di mosse fornita dall'utente.
- Gestione delle collisioni con ostacoli e altri robot.
- Stampa della configurazione iniziale e finale della griglia.

 1)  Il programma inizia chiedendo all'utente di inserire la dimensione della griglia. La dimensione deve essere un numero intero positivo. Se l'utente inserisce una dimensione non valida, verrà richiesto di inserirla nuovamente.


std::cout << "Inserisci la dimensione della griglia: ";
std::cin >> n;

while (n <= 0) {
    std::cout << "Dimensione della griglia non valida. Reinserisci: ";
    std::cin >> n;
}


2)Successivamente, l'utente deve inserire le coordinate della nuova origine della griglia. Questo permette di spostare l'origine della griglia rispetto alla posizione predefinita (0, 0).


std::cout << "Inserisci le coordinate della nuova origine della griglia:" << std::endl;
int newx, newy;
std::cout << "X: ";
std::cin >> newx;
std::cout << "Y: ";
std::cin >> newy;

mappa.setOrigine(Position(newx, newy)); 
//Questo serve per passare la nuova posizione alla funzione set per memorizzarla e poi trasmetterla al set delle griglia

3) Il programma chiede poi quanti ostacoli l'utente vuole inserire nella griglia. Per ogni ostacolo, viene richiesto di inserire le coordinate. Se la posizione inserita è non valida, verrà richiesto di inserirla nuovamente.

std::cout << "Quanti ostacoli vuoi inserire? ";
std::cin >> numOstacoli;

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

4) L'utente inserisce il numero di robot che desidera aggiungere alla griglia. Per ogni robot, vengono richieste le coordinate iniziali e la velocità. Anche in questo caso, se la posizione è non valida o già occupata, l'utente dovrà reinserirla.


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

    int speed;
    std::cout << "Inserisci la velocità del robot " << i + 1 << ": ";
    std::cin >> speed;

    while (speed <= 0) {
        std::cout << "La velocità del robot deve essere maggiore di 0. Reinserisci: ";
        std::cin >> speed;
    }

    char automaticID = '0' + (i + 1);
    robots.emplace_back(x, y, automaticID, speed);
    mappa.Set(StatoCella(automaticID), Position(x, y));
}

5)  Il programma stampa la configurazione iniziale della griglia con gli ostacoli e i robot posizionati.

std::cout << "Griglia iniziale:" << std::endl;
mappa.Print();
Funzione:
void Grid::Print() const {
    for (int i = 0; i < numero; ++i) {
        for (int j = 0; j < numero; ++j) {
            std::cout << cells_[j][i].value << " ";
        }
        std::cout << std::endl;
    }
}


6)




## Problem 1

You have a mobile robot that moves in a grid-like environment. The robot can move up, down, left, or right by one unit at a time. Given a starting position `(x, y)` on the grid and a sequence of moves represented by characters `U` (up), `D` (down), `L` (left), and `R` (right), determine the final position of the robot after executing all the moves.

#### Example
```
Input:
Starting position: (0, 0)
Moves: "RRUUL"

Output:
Final position: (1, 2)
```

<details>
    <summary>Variant A</summary>

### Now with obstacles
You have a mobile robot that moves in a grid-like environment, similar to the previous exercise. However, this time, the grid can have obstacles represented by certain cells that the robot cannot traverse. Given a grid with obstacles, a starting position `(x, y)`, and a sequence of moves represented by characters `U` (up), `D` (down), `L` (left), and `R` (right), determine if the robot can reach its final destination without encountering any obstacles.

#### Example
```
Input:
Grid with obstacles:
0 0 0 0 0
0 1 0 1 0
X 0 0 0 0
Starting position: (0, 0)
Moves: "RRUUL"

Output:
Can reach destination? Yes
```
</details>

<details>
    <summary>Variant B</summary>

### With 2 robots
You have 2 mobile robots that moves in a grid-like environment, similar to the previous exercise. Given a grid with obstacles, and for each robot: a starting position `(x, y)` and a sequence of moves represented by characters `U` (up), `D` (down), `L` (left), and `R` (right), determine if the robots may collide.

#### Example
```
Input:
Grid with obstacles:
0 0 0 0 0
0 1 0 1 0
X 0 0 0 X
Starting position R1: (0, 0)
Moves: "RRUUR"
Starting position R2: (0, 4)
Moves: "LLUR"

Output:
Do robots collide? Yes
```
</details>

<details>
    <summary>Variant C</summary>

### At different speeds
You have 2 mobile robots that move in a grid-like environment, similar to the previous exercise. Given a grid with obstacles, and for each robot: a starting position `(x, y)`, a sequence of moves represented by characters `U` (up), `D` (down), `L` (left), and `R` (right), and a velocity, determine if the robots may collide.

#### Example
```
Input:
Grid with obstacles:
0 0 0 0 0
0 1 0 1 0
X 0 0 0 X
Starting position R1: (0, 0)
Moves: "RUUR"
Speed: 2
Starting position R2: (0, 4)
Moves: "LLUR"
Speed: 1

Output:
Do robots collide? No
```
</details>