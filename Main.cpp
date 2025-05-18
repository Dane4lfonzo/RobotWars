#include "Class.h"

int main()
{
    srand(time(0));

    int row = 30;
    int col = 80;

    //Battlefield Grid(rows, cols);

    
    MovingRobot RoboMove(row, col);
    MovingRobot RoboMove2 = RoboMove;
    /*
    Robo.WheretoMove();
    Robo.MovetoSquare();
    Robo.printGrid(); 
    */
    RoboMove.GridMaker();

    while (true)
    {
        //cout << "Works" << endl;
        system("CLS");

        //RoboMove.GridMaker();

        RoboMove.WheretoMove();
        RoboMove.MovetoSquare();

        //RoboMove2.WheretoMove();
        //RoboMove2.MovetoSquare();
        

        RoboMove.printGrid();

        RoboMove.delay(500);


        //Robo.GridReset();
    }

}