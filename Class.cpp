#include "Class.h"

/*************************Battlefield***************************************/
Battlefield::Battlefield(int row, int col)
{
    *MaxRow = row;
    *MaxCol = col;
}

Battlefield::Battlefield(const Battlefield& obj)
{
    MaxRow = new int(*obj.MaxRow);
    MaxCol = new int(*obj.MaxCol);
    Grid = obj.Grid; // deep copy via vector copy
}

Battlefield::~Battlefield()
{
    delete MaxRow;
    delete MaxCol;
}

void Battlefield::GridMaker()
{
    Grid.resize(*MaxRow);

    for (int i=0; i < *MaxRow; i++)
    {
        Grid[i].resize(*MaxCol, ".");
    }
}

void Battlefield::GridReset()
{
    for (int i=0; i < *MaxRow; i++)
    {
        for (int j=0; j < *MaxCol; j++)
        {
            Grid[i][j] = ".";
        }
    }
}

void Battlefield::printGrid()
{
    for (int i=0; i < *MaxRow; i++)
    {
        for (int j=0; j < *MaxCol; j++)
        {
            cout << Grid[i][j];
        }
        cout << endl;
    }
}

void Battlefield::delay(int milliseconds) 
{
    // Simple delay using a loop 
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds * CLOCKS_PER_SEC / 1000);
}

/**********************************MovingRobot**************************************/

MovingRobot::MovingRobot(int row, int col) : Battlefield(row, col)
{   
    current_row = new int;
    current_col = new int;

    *current_row = rand() % row;
    *current_col = rand() % col;
}

MovingRobot::MovingRobot(const MovingRobot& obj) : Battlefield(obj)
{
    current_row = new int (*obj.current_row);
    current_col = new int (*obj.current_col);

    movingchoice = new int (*obj.movingchoice);
    move_row = new int (*obj.move_row);
    move_col = new int (*obj.move_col);

    *current_row = rand() % *MaxRow;
    *current_col = rand() % *MaxCol;

}


MovingRobot::~MovingRobot()
{
    delete movingchoice;
    delete move_row;
    delete move_col;
    delete current_row;
    delete current_col;
}

void MovingRobot::WheretoMove()
{
    
    *movingchoice = rand() % 8;

    if (*movingchoice == 0)
    {
        *move_row = -1;
        *move_col = -1;
    }

    else if (*movingchoice == 1)
    {
        *move_row = 0;
        *move_col = -1;
    }

    else if (*movingchoice == 2)
    {
        *move_row = 1;
        *move_col = -1;
    }

    else if (*movingchoice == 3)
    {
        *move_row = 1;
        *move_col = 0;
    }

    else if (*movingchoice == 4)
    {
        *move_row = 1;
        *move_col = 1;
    }

    else if (*movingchoice == 5)
    {
        *move_row = 0;
        *move_col = 1;
    }

    else if (*movingchoice == 6)
    {
        *move_row = -1;
        *move_col = 1;
    }

    else if (*movingchoice == 7)
    {
        *move_row = -1;
        *move_col = 0;
    }

    //cout << "moving choice: "<< *movingchoice << endl;


}

/*
void MovingRobot::MovetoSquare()
{
    Grid[*current_row][*current_col] = ".";

    int new_row = *current_row + *move_row;
    int new_col = *current_col + *move_col;

    
    if (((new_row) >= 0) && ((new_row) < *MaxRow))
    {
        *current_row = new_row;
    }
    
    if (((new_col) >= 0) && ((new_col) < *MaxCol))
    {
        *current_col = new_col;
    }

    Grid[*current_row][*current_col] = "R";

    
    cout << "\n\n\ncurrent_row = " << *current_row << endl;
    cout << "\n\n\ncurrent_col = " << *current_col << endl;
    /*
    cout << "\n\n\n*move_row = " << *move_row << endl;
    cout << "\n\n\n*move_col = " << *move_col << endl;
    */

void MovingRobot::MovetoSquare(vector<vector<string>>& sharedGrid) 
{
    sharedGrid[*current_row][*current_col] = ".";

    int new_row = *current_row + *move_row;
    int new_col = *current_col + *move_col;

    if (new_row >= 0 && new_row < *MaxRow)
    {
        *current_row = new_row;
    }

    if (new_col >= 0 && new_col < *MaxCol)
    {
        *current_col = new_col;
    }

    sharedGrid[*current_row][*current_col] = "R";
    cout << "\n\n\ncurrent_row = " << *current_row << endl;
    cout << "\n\n\ncurrent_col = " << *current_col << endl;
}