#include "Class.h"

int main()
{
    int rows = 30;
    int cols = 80;

    //Battlefield Grid(rows, cols);

    
    MovingRobot RoboMove(rows - 1, cols - 1);
    /*
    Robo.WheretoMove();
    Robo.MovetoSquare();
    Robo.printGrid(); 
    */

    while (true)
    {
        system("CLS");

        RoboMove.GridMaker(rows, cols);

        RoboMove.WheretoMove();
        RoboMove.MovetoSquare();

        RoboMove.printGrid();

        RoboMove.delay(500);

        //Robo.GridReset();
    }

}