# Sudoku-Tectonic-Solver

Quick project as a refresher & to prove my algorithm skills.
Puzzles are taken from a handout by the MIVD @ Deflab, 7 mrt 2019
More than a year has passed since, so I presume that presenting the solution is fair game. 

The program works by using recursion and back tracking. It's written in C++ & tested for memory leaks.

Input is a csv file with two blocks separated by a blank line.
The first block is a grid with shape IDs. 
The second block is a grid with the given values of the squares.

The input file is hard coded in main.cpp. Two other variables are hard coded in sudokutectonic.cpp. All three have to be adjusted when you're solving a new puzzle. The latter two can be determined programmatically and the former can be read from the command line arguments. This has yet to be implemented.