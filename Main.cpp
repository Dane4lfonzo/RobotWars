#include "Class.h"

int main()
{
    srand(time(0));
/*************** Variables for Yuven's readfile function later **************************/
    int row = 10;
    int col = 20;
    int numofsteps = 100;
    int numberOfRobots = 4;
    string TestChars = "ABCD";
/****************************************************************************************/

    bool SetSignia = true;

    SeeingRobot RoboMove(row, col);  //Original MovingRobot class instance
    vector<SeeingRobot> RoboMoveCopies;  //Copy Constructor class instance for MovingRobot but as an Array(Vector)


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

                for (int j=0; j<RoboMoveCopies.size(); j++)
                {
                    if (!(*RoboMoveCopies[i].current_col == *RoboMoveCopies[j].current_col && 
                        *RoboMoveCopies[i].current_row == *RoboMoveCopies[j].current_row))
                    {
                        RoboMoveCopies[i].Look(*RoboMoveCopies[i].current_row, *RoboMoveCopies[i].current_col, 
                            *RoboMoveCopies[j].current_row, *RoboMoveCopies[j].current_col);
                    }
                }

                RoboMoveCopies[0].CountDownStep();

                RoboMoveCopies[0].printGrid();

                for (int i = 0; i < RoboMoveCopies.size(); i++)
                {
                    cout << "Robot " << i << " row: " << *RoboMoveCopies[i].current_row;
                    cout <<" col: " << *RoboMoveCopies[i].current_col << endl;
                }
                

                RoboMoveCopies[0].delay(1000);
            }
        }

    }

    return 0;
}