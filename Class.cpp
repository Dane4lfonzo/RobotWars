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
        move_posx = -1;
        move_posy = -1;
    }

    else if (movingchoice == 1)
    {
        move_posx = 0;
        move_posy = -1;
    }

    else if (movingchoice == 2)
    {
        move_posx = 1;
        move_posy = -1;
    }

    else if (movingchoice == 3)
    {
        move_posx = 1;
        move_posy = 0;
    }

    else if (movingchoice == 4)
    {
        move_posx = 1;
        move_posy = 1;
    }

    else if (movingchoice == 5)
    {
        move_posx = 0;
        move_posy = 1;
    }

    else if (movingchoice == 6)
    {
        move_posx = -1;
        move_posy = 1;
    }

    else if (movingchoice == 7)
    {
        move_posx = -1;
        move_posy = 0;
    }


}

Robot::Robot(int x, int y) //: Battlefield(x, y)
{   
    srand(time(0));

    current_posx = rand() % x;
    current_posy = rand() % y;
}

void Robot::MovetoSquare()
{
    Grid[current_posx][current_posy] = ".";

    int new_x = current_posx + move_posx;
    int new_y = current_posy + move_posy;

    if ((new_x) >= 0 && (new_x) < MaxRow)
    {
        current_posx = new_x;
    }
    
    if ((new_y) >= 0 && (new_y) < MaxCol)
    {
        current_posy = new_y;
    }

    Grid[current_posx][current_posy] = "R";

    
    cout << "\n\n\ncurrent_posx = " << current_posx << endl;
    cout << "\n\n\ncurrent_posy = " << current_posy << endl;
    /*
    cout << "\n\n\nmove_posx = " << move_posx << endl;
    cout << "\n\n\nmove_posy = " << move_posy << endl;
    */

}

