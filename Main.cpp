#include "Class.h"

int main()
{
    srand(time(0));

    int row = 30;
    int col = 80;

    //Battlefield Grid(rows, cols);

    MovingRobot RoboMove(row, col);
    int newrow =  rand() % row;
    int newcol = rand() % col;
    MovingRobot RoboMove2 = RoboMove;
    *RoboMove2.current_row = newrow;
    *RoboMove2.current_col = newcol;
    /*
    Robo.WheretoMove();
    Robo.MovetoSquare();
    Robo.printGrid(); 
    */
    RoboMove.GridMaker();
    //RoboMove2.GridMaker();

    while (true)
    {
        //cout << "Works" << endl;
        system("CLS");

        RoboMove.GridReset();

        RoboMove.WheretoMove();
        RoboMove.MovetoSquare(RoboMove.Grid);

        RoboMove2.WheretoMove();
        RoboMove2.MovetoSquare(RoboMove.Grid);
        

        RoboMove.printGrid();

        RoboMove.delay(1000);


        //Robo.GridReset();
    }

}