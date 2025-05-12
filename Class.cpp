#include "Class.h"

Battlefield::Battlefield(int row, int col)
{
    MaxRow = row;
    MaxCol = col;
    Grid.resize(MaxRow);

    for (int i=0; i < MaxRow; i++)
    {
        Grid[i].resize(MaxCol, "");
    }
}

void Battlefield::printGrid()
{
    for (int i=0; i < MaxRow; i++)
    {
        for (int j=0; j < MaxCol; j++)
        {
            cout << Grid[i][j];
        }
        cout << endl;
    }
}

Robot::Robot(int x, int y)
{
    posx = x;
    posy = y;
}

void Robot::movement(int posx, int posy)
{
    
}
