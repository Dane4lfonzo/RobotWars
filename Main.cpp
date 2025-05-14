#include "Class.h"

int main()
{
    int rows = 30;
    int cols = 80;

    //Battlefield Grid(rows, cols);

    
    Robot Robo(rows - 1, cols - 1);
    /*
    Robo.WheretoMove();
    Robo.MovetoSquare();
    Robo.printGrid(); 
    */

    while (true)
    {
        system("CLS");

        Robo.GridMaker(rows, cols);

        Robo.WheretoMove();
        Robo.MovetoSquare();

        Robo.printGrid();

        Robo.delay(500);

        //Robo.GridReset();
    }

}