#include "Class.h"

int main()
{
    srand(time(0));
/*************** Variables for Yuven's readfile function later **************************/
    int row = 10;
    int col = 5;
    int numofsteps = 100;
    int numberOfRobots = 4;
    string TestChars = "ABCD";
/****************************************************************************************/

    bool SetSignia = true;

    ShootingRobot RoboMove(row, col);  //Original MovingRobot class instance
    vector<ShootingRobot*> RoboMoveCopies;  //Copy Constructor class instance for MovingRobot but as an Array(Vector)


    for (int i = 0; i < numberOfRobots; i++) 
    {
        RoboMoveCopies.push_back(new ShootingRobot(row, col));   //Similar to MovingRobot RoboMove2 = RoboMove; / MovingRobot RoboMove2(RoboMove); but enables multi-copy in a for loop
    }

    RoboMoveCopies[0]->SetStep(numofsteps);

    RoboMoveCopies[0]->GridMaker();

    //MovingRobot RoboMove(row, col);
    //MovingRobot RoboMove2(RoboMove);

    while (RoboMoveCopies[0]->StepCount())
    {

        if (SetSignia)
        {
            for (int i = 0; i < RoboMoveCopies.size(); i++)
            {
                if (RoboMoveCopies[i] == nullptr) continue; // Checking for if the pointer for that specific element is null or not

                RoboMoveCopies[i]->SetSignia(TestChars[i]);
            }

            SetSignia = false;
        }
      
        for (int i = 0; i < RoboMoveCopies.size(); i++) 
        {
            if (RoboMoveCopies[0]->StepCount())
            {
                system("CLS");
                if (RoboMoveCopies[i] == nullptr) continue;
                
                RoboMoveCopies[i]->WheretoMove();
                RoboMoveCopies[i]->MovetoSquare(RoboMoveCopies[0]->Grid);

                
                RoboMoveCopies[0]->CountDownStep();

                RoboMoveCopies[0]->printGrid();
                for (int j=0; j<RoboMoveCopies.size(); j++)
                {
                    if (RoboMoveCopies[j] == nullptr || RoboMoveCopies[i] == nullptr) continue;

                    if (!(*RoboMoveCopies[i]->current_col == *RoboMoveCopies[j]->current_col && 
                        *RoboMoveCopies[i]->current_row == *RoboMoveCopies[j]->current_row))
                    {
                        RoboMoveCopies[i]->Look(*RoboMoveCopies[j]->current_row, *RoboMoveCopies[j]->current_col);
                        RoboMoveCopies[i]->CheckShot();

                        if (i != j && RoboMoveCopies[i]->GetShooting())
                        {
                            delete RoboMoveCopies[j];
                            RoboMoveCopies[j] = nullptr;
                        }

                    }
                }

                if (RoboMoveCopies[i] != nullptr && RoboMoveCopies[i]->current_row != nullptr && 
                    RoboMoveCopies[i]->current_col != nullptr)
                {
                    for (int i = 0; i < RoboMoveCopies.size(); i++)
                    {
                        if (RoboMoveCopies[i] == nullptr) continue;
                        cout << "Robot " << i << " row: " << *RoboMoveCopies[i]->current_row;
                        cout <<" col: " << *RoboMoveCopies[i]->current_col << endl;
                    }
                }

                RoboMoveCopies[0]->delay(1000);
            }
        }

    }

    return 0;
}