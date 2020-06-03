#include <iostream>
#include "sudokutectonic.hpp"

// TODO: clean up these variables
//#define MAXVALUE 5
//static int shapeAmount = 10;
#define MAXVALUE 6
static int shapeAmount = 24;

bool fieldIsValid(struct square** field, int sizeX, int sizeY)
{
    // Check rows
    int maxInstancesPerRow = sizeX / MAXVALUE;
    for (int n = 1; n <= MAXVALUE; n++)
    {
        for (int row = 0; row < sizeY; row++)
        {
        int instances = 0;
            for (int column = 0; column < sizeX; column++)
            {
                if (field[column][row].value == n)
                {
                    instances++;
                    if (instances > maxInstancesPerRow)
                    {
                        return false;
                    }
                }
            }
        }
    }

    // Check columns
    int maxInstancesPerColumn = sizeY / MAXVALUE;
    for (int n = 1; n <= MAXVALUE; n++)
    {
        for (int column = 0; column < sizeX; column++)
        {
        int instances = 0;
            for (int row = 0; row < sizeY; row++)
            {
                if (field[column][row].value == n)
                {
                    instances++;
                    if (instances > maxInstancesPerColumn)
                    {
                        return false;
                    }
                }
            }
        }
    }

    // Check touching
    for (int row = 0; row < sizeY; row++)
    {
        for (int column = 0; column < sizeX; column++)
        {
            if (field[column][row].value == 0)
            {
                continue;
            }
            for (int rowMutation = -1; rowMutation <= 1; rowMutation++)
            {
                for (int columnMutation = -1; columnMutation <= 1; columnMutation++)
                {
                    if (rowMutation == 0 && columnMutation == 0)
                    {
                        continue;
                    }
                    int checkRow = row + rowMutation;
                    int checkColumn = column + columnMutation;
                    if (
                        checkRow > 0 && \
                        checkColumn > 0 && \
                        checkRow < sizeY && \
                        checkColumn < sizeX
                    )
                    {
                        if (field[checkColumn][checkRow].value == field[column][row].value)
                        {
                            return false;
                        }
                    }
                }
            }
        }
    }

    // Check shapes
    for (int shape = 0; shape < shapeAmount; shape++)
    {
        for (int n = 1; n <= MAXVALUE; n++)
        {
            int instances = 0;
            for (int row = 0; row < sizeY; row++)
            {
                for (int column = 0; column < sizeX; column++)
                {
                    if(field[column][row].shapeID == shape)
                    {
                        if(field[column][row].value == n)
                        {
                            instances++;
                            // TODO: Maybe upgrade this to more values per shape?
                            if (instances > 1)
                            {
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}

void printField(struct square** field, int sizeX, int sizeY)
{
    for (int row = 0; row < sizeY; row++)
    {
        for (int column = 0; column < sizeX; column++)
        {
            std::cout << field[column][row].value << "\t";
        }
        std::cout << "\n";
    }
}

bool fieldContainsEmptySpaces(struct square** field, int sizeX, int sizeY)
{
    for(int i = 0; i < sizeX; i++)
    {
        for(int j = 0; j < sizeY; j++)
        {
            if (field[i][j].value == 0)
            {
                return true;
            }
        }
    }
    return false;
}


bool solve(struct square** field, int sizeX, int sizeY)
{
    for(int column = 0; column < sizeX; column++)
    {
        for(int row = 0; row < sizeY; row++)
        {
            if(field[column][row].value == 0)
            {
                for (int n = 1; n <= MAXVALUE; n++)
                {
                    field[column][row].value = n;
                    if (fieldIsValid(field, sizeX, sizeY))
                    {
                        if (fieldContainsEmptySpaces(field, sizeX, sizeY))
                        {
                            if (solve(field, sizeX, sizeY))
                            {
                                return true;
                            }
                        }
                        else
                        {
                            return true;
                        }
                    }
                }
                field[column][row].value = 0;
                return false;
            }
        }
    }
    return false;
}