#include "Class.h"

int main()
{
    srand(time(0));

    int row = 30;
    int col = 80;
    int numofsteps = 10;

    MovingRobot RoboMove(row, col);

    RoboMove.SetStep(numofsteps);
    
    int newrow =  rand() % row;
    int newcol = rand() % col;
    
    MovingRobot RoboMove2 = RoboMove;
    MovingRobot RoboMove3 = RoboMove;
    
    //*RoboMove2.current_row = newrow;
    //*RoboMove2.current_col = newcol;

    RoboMove.GridMaker();


    while (RoboMove.StepCount())
    {
        system("CLS");

        RoboMove.CountUpStep();

        RoboMove.GridReset();

        RoboMove.WheretoMove();
        RoboMove.MovetoSquare(RoboMove.Grid);

        RoboMove2.WheretoMove();
        RoboMove2.MovetoSquare(RoboMove.Grid);

        RoboMove3.WheretoMove();
        RoboMove3.MovetoSquare(RoboMove.Grid);
        

        RoboMove.printGrid();

        

        RoboMove.delay(1000);


        //Robo.GridReset();
    }

}