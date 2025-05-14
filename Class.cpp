#include "Class.h"

void Battlefield::GridMaker(int row, int col)
{
    MaxRow = row;
    MaxCol = col;
    Grid.resize(MaxRow);

    for (int i=0; i < MaxRow; i++)
    {
        Grid[i].resize(MaxCol, ".");
    }
}

void Battlefield::GridReset()
{
    for (int i=0; i < MaxRow; i++)
    {
        Grid[i].resize(MaxCol, ".");
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

void Battlefield::delay(int milliseconds) 
{
    // Simple delay using a loop 
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds * CLOCKS_PER_SEC / 1000);
}

void MovingRobot::WheretoMove()
{
    srand(time(0));
    movingchoice = rand() % 9;
    if (movingchoice == 0)
    {
        move_row = -1;
        move_col = -1;
    }

    else if (movingchoice == 1)
    {
        move_row = 0;
        move_col = -1;
    }

    else if (movingchoice == 2)
    {
        move_row = 1;
        move_col = -1;
    }

    else if (movingchoice == 3)
    {
        move_row = 1;
        move_col = 0;
    }

    else if (movingchoice == 4)
    {
        move_row = 1;
        move_col = 1;
    }

    else if (movingchoice == 5)
    {
        move_row = 0;
        move_col = 1;
    }

    else if (movingchoice == 6)
    {
        move_row = -1;
        move_col = 1;
    }

    else if (movingchoice == 7)
    {
        move_row = -1;
        move_col = 0;
    }


}

MovingRobot::MovingRobot(int row, int col) //: Battlefield(x, y)
{   
    srand(time(0));

    current_row = rand() % row;
    current_col = rand() % col;
}

void MovingRobot::MovetoSquare()
{
    Grid[current_row][current_col] = ".";

    int new_row = current_row + move_row;
    int new_col = current_col + move_col;

    
    if ((new_row) >= 0 && (new_row) < MaxRow)
    {
        current_row = new_row;
    }
    
    if ((new_col) >= 0 && (new_col) < MaxCol)
    {
        current_col = new_col;
    }

    Grid[current_row][current_col] = "R";

    
    cout << "\n\n\ncurrent_row = " << current_row << endl;
    cout << "\n\n\ncurrent_col = " << current_col << endl;
    /*
    cout << "\n\n\nmove_row = " << move_row << endl;
    cout << "\n\n\nmove_col = " << move_col << endl;
    */

}

