#include "Class.h"

int main()
{
    int row = 30;
    int col = 80;

    //Battlefield Grid(rows, cols);

    
    MovingRobot RoboMove(row - 1, col - 1);
    MovingRobot Robomove2 = RoboMove;
    /*
    Robo.WheretoMove();
    Robo.MovetoSquare();
    Robo.printGrid(); 
    */

    while (true)
    {
        system("CLS");

        RoboMove.GridMaker(row, col);

        RoboMove.WheretoMove();
        RoboMove.MovetoSquare();

        RoboMove.printGrid();

        RoboMove.delay(500);


        //Robo.GridReset();
    }

}