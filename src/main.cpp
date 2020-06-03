/* 
 * Sudoku tectonic solver
 * MIVD, here I come
 */
#include <iostream>
#include <fstream>
#include <string>

#include <signal.h>

#include "sudokutectonic.hpp"

#define INPUTFILE "puzzle4.csv"
/*
0,0,0,0,x=5 ->  array with vertical arrays
0,0,0,0,0       [x][y]
0,0,0,0,0
0,0,0,0,0
y=5,0,0,0
*/

square** globalField;
void sighandler(int s){
           printf("Caught signal %d\n",s);
           printField(globalField, 12, 12);
           exit(1); 

}

int main(int argc, const char *argv[])
{
    signal(SIGABRT, &sighandler);
	signal(SIGTERM, &sighandler);
	signal(SIGINT, &sighandler);

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
    std::ifstream myfile(INPUTFILE);
    if (myfile.is_open())
    {
        // We start with the shape id grid
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
                    // Save the very last column number. that's the amount of columns
                    columnNr++;
                    columns = columnNr;
                }
                else
                {
                    currentNumber += line[i];
                }
            }
            // Save the last row number. same as columns
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
    //std::cout << "\n" << fieldIsValid(field, columns, rows) << "\n";
    
    if(solve(field, columns, rows))
    {
        std::cout << "solution was found!!!!1!\n";
    }
    else
    {
        std::cout << "solution not found\n";
    }
    printField(field, columns, rows);
    
}
