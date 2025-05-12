#include "Class.h"

Battlefield::Battlefield(int row, int col) // ni constructor
{
    MaxRow = row;
    MaxCol = col;
    Grid.resize(MaxRow); //resize tu vector

    for (int i=0; i < MaxRow; i++)
    {
        Grid[i].resize(MaxCol, "*"); //grid is vector // utk print the battlefield
        //.resize(numItShouldContain,WhatItShouldBeFilled)
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

/* void Robot::movement(int posx, int posy)
{
    
}  */