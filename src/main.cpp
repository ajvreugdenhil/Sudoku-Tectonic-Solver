/* 
 * Sudoku tectonic solver
 * Written by Arjan Vreugdenhil
 */

#include <iostream>
#include <fstream>
#include <string>
#include <signal.h>
#include "sudokutectonic.hpp"

/*
Structure of the internal field is as follows:
0,0,0,0,x=5 ->  array with vertical arrays
0,0,0,0         [x][y]
0,0,0,0
0,0,0,0
y=5
*/

square** globalField;
std::string inputFile = "puzzle4.csv";

void sighandler(int s){
           printf("\nCaught signal %d\n\n",s);
           printField(globalField, 12, 12);
           exit(1); 
}

int main(int argc, const char *argv[])
{
    signal(SIGABRT, &sighandler);
	signal(SIGTERM, &sighandler);
	signal(SIGINT, &sighandler);

    if (argc == 2)
    {
        inputFile = argv[1];
    }

    int maximumFieldX = 200;
    int maximumFieldY = 200;
    square** field = new square*[maximumFieldX];
    for (int i = 0; i < maximumFieldX; i++)
    {
        field[i] = new square[maximumFieldY];
    }

    int rows;
    int columns;
    std::string line;
    std::ifstream myfile(inputFile);
    if (myfile.is_open())
    {
        // We start with the shape ID grid
        int rowNr = 0;
        while ( std::getline(myfile, line) && (line != ""))
        {
            int columnNr = 0;
            std::string currentNumber = "";
            for (int i = 0; i < (int)line.size() + 1; i++)
            {
                if ((line[i] == ',') || (i == (int)line.size()))
                {
                    field[columnNr][rowNr].shapeID = stoi(currentNumber);
                    currentNumber = "";
                    columnNr++;
                    columns = columnNr;
                }
                else
                {
                    currentNumber += line[i];
                }
            }
            rowNr++;
            rows = rowNr;
        }
        // Then we import the values grid
        rowNr = 0;
        while ( std::getline(myfile, line))
        {
            int columnNr = 0;
            std::string currentNumber = "";
            for (int i = 0; i < (int)line.size() + 1; i++)
            {
                if ((line[i] == ',') || (i == (int)line.size()))
                {
                    field[columnNr][rowNr].value = stoi(currentNumber);
                    currentNumber = "";
                    columnNr++;
                }
                else
                {
                    currentNumber += line[i];
                }
            }
            rowNr++;
        }

        myfile.close();
    }

    globalField = field;
    std::cout << "Imported puzzle:\n";
    printField(field, columns, rows);
    if(solve(field, columns, rows))
    {
        std::cout << "Solution found:\n";
    }
    else
    {
        std::cout << "Solution not found.\n";
    }
    printField(field, columns, rows);

    // Clean up
    
    for (int i = 0; i < 200; i++)
    {
        delete[] field[i];
    }
    
    delete[] field;
}
