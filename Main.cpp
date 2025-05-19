#include "Class.h"

int main()
{
    srand(time(0));
/*************** Variables for Yuven's readfile function later **************************/
    int row = 30;
    int col = 80;
    int numofsteps = 10;
    int numberOfRobots = 4;
    string TestChars = "ABCD";
/****************************************************************************************/

    bool SetSignia = true;

    MovingRobot RoboMove(row, col);  //Original MovingRobot class instance
    vector<MovingRobot> RoboMoveCopies;  //Copy Constructor class instance for MovingRobot but as an Array(Vector)

    for (int i = 0; i < numberOfRobots; i++) 
    {
        RoboMoveCopies.push_back(RoboMove);   //Similar to MovingRobot RoboMove2 = RoboMove; / MovingRobot RoboMove2(RoboMove); but enables multi-copy in a for loop
    }

    RoboMoveCopies[0].SetStep(numofsteps);

    RoboMoveCopies[0].GridMaker();

    //MovingRobot RoboMove(row, col);
    //MovingRobot RoboMove2(RoboMove);

    while (RoboMoveCopies[0].StepCount())
    {

        if (SetSignia)
        {
            for (int i = 0; i < RoboMoveCopies.size(); i++)
            {
                RoboMoveCopies[i].SetSignia(TestChars[i]);
            }

            SetSignia = false;
        }
      
        for (int i = 0; i < RoboMoveCopies.size(); i++) 
        {
            if (RoboMoveCopies[0].StepCount())
            {
                system("CLS");
    
                RoboMoveCopies[i].WheretoMove();
                RoboMoveCopies[i].MovetoSquare(RoboMoveCopies[0].Grid);

                RoboMoveCopies[0].CountDownStep();

                RoboMoveCopies[0].printGrid();

                RoboMoveCopies[0].delay(1000);
            }
        }

    }

    return 0;
}