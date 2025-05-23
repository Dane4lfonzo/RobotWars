#include "Class.h"

int main()
{
    srand(time(0));
/*************** Variables for Yuven's readfile function later **************************/
    int row = 5;
    int col = 10;
    int numofsteps = 1000;
    int numberOfRobots = 6;
    string StringOfRoboName = "ABCDEF";

/****************************************************************************************/

    bool SetSignia = true;

    SeeingRobot RoboMove(row-1, col-1);  //Original MovingRobot class instance
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
                RoboMoveCopies[i].SetSignia(StringOfRoboName[i]);
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

                for (int j=0; j<RoboMoveCopies.size(); j++)
                {
                    if (!(*RoboMoveCopies[i].current_col == *RoboMoveCopies[j].current_col && *RoboMoveCopies[i].current_row == *RoboMoveCopies[j].current_row))
                    {
                        RoboMoveCopies[i].Look(*RoboMoveCopies[j].current_row, *RoboMoveCopies[j].current_col);
                    }
                }

                for (int i = 0; i < RoboMoveCopies.size(); i++)
                {
                    cout << "Robot " << i << " row: " << *RoboMoveCopies[i].current_row;
                    cout <<" col: " << *RoboMoveCopies[i].current_col << endl;
                }
                

                RoboMoveCopies[0].delay(100);
            }
        }

    }

    return 0;
}