## Interview problem set

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