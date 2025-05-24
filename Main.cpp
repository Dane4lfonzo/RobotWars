#include "Class.h"

int main()
{
    srand(time(0));
/*************** Variables for Yuven's readfile function later **************************/
    int row = 5;
    int col = 10;
    int numofsteps = 100;
    int numberOfRobots = 4;
    string TestChars = "ABCD";
/****************************************************************************************/

    bool SetSignia = true;

    /*ShootingRobot RoboMove(row, col);  //Original MovingRobot class instance
    vector<ShootingRobot*> RoboMoveCopies;  //Copy Constructor class instance for MovingRobot but as an Array(Vector)

    for (int i = 0; i < numberOfRobots; i++) 
    {
        RoboMoveCopies.push_back(new ShootingRobot(row, col));   //Similar to MovingRobot RoboMove2 = RoboMove; / MovingRobot RoboMove2(RoboMove); but enables multi-copy in a for loop
    }

    RoboMoveCopies[0]->SetStep(numofsteps);

    RoboMoveCopies[0]->GridMaker(); */

    // Create standalone Battlefield object (not tied to any robot)
    Battlefield battlefield(row, col);
    battlefield.GridMaker();
    battlefield.SetStep(numofsteps);
    vector<ShootingRobot*> RoboMoveCopies;

    if (SetSignia)
    {
        for (int i = 0; i < numberOfRobots; i++)
        {
            ShootingRobot* newBot = new ShootingRobot(row, col);
            newBot->SetSignia(TestChars[i]);
            RoboMoveCopies.push_back(newBot);
        }
        
        SetSignia = false;
    }
      

    while (battlefield.StepCount())
    {
        for (int i = 0; i < RoboMoveCopies.size(); i++) 
        {
            if (RoboMoveCopies[i] == nullptr) continue; // Checking for if the pointer for that specific element is null or not
            
            system("CLS");
            
            
            // Robot movement
            RoboMoveCopies[i]->WheretoMove();
            RoboMoveCopies[i]->MovetoSquare(battlefield.Grid);

            // Counts one step for robot
            battlefield.CountDownStep();
            

            // Displays the Grid and Robots
            battlefield.printGrid();

            vector<int> Trashbin;
            // Robot Actions (Looking & Shooting)
            for (int j=0; j<RoboMoveCopies.size(); j++)
            {
                if (RoboMoveCopies[i] == nullptr || RoboMoveCopies[j] == nullptr || i == j) continue;
                if (!RoboMoveCopies[i]->current_row || !RoboMoveCopies[i]->current_col ||
                !RoboMoveCopies[j]->current_row || !RoboMoveCopies[j]->current_col) continue;

                // Check if robots are not in the same cell
                if (*RoboMoveCopies[i]->current_col == *RoboMoveCopies[j]->current_col &&
                    *RoboMoveCopies[i]->current_row == *RoboMoveCopies[j]->current_row)
                    continue;
                RoboMoveCopies[i]->Look(*RoboMoveCopies[j]->current_row, *RoboMoveCopies[j]->current_col);

                if (RoboMoveCopies[i]->RobotDetect())
                {
                    RoboMoveCopies[i]->ShootheRobot();
                    RoboMoveCopies[i]->CheckShot();

                    if (RoboMoveCopies[i]->GetShooting())
                    {
                        Trashbin.push_back(j);
                    }
                }
            }

            for (int x : Trashbin)
            {
                if (RoboMoveCopies[x] != nullptr)
            {
                // Clear grid symbol before deleting
                if (RoboMoveCopies[x]->current_row && RoboMoveCopies[x]->current_col)
                {
                    battlefield.Grid[*RoboMoveCopies[x]->current_row][*RoboMoveCopies[x]->current_col] = ".";
                }
                cout << "Robot " << x << " was shot and removed.\n";
                delete RoboMoveCopies[x];
                RoboMoveCopies[x] = nullptr;
            }
            }

            // print logs
            for (int k = 0; k < RoboMoveCopies.size(); k++)
            {
                if (RoboMoveCopies[k] == nullptr) continue;
                cout << "Robot " << k 
                        << " row: " << *RoboMoveCopies[k]->current_row
                        << " col: " << *RoboMoveCopies[k]->current_col
                        << " Shots: " << *RoboMoveCopies[k]->shootFlag << endl;
            }

        battlefield.delay(1000);
        
        }
    }

    return 0;
}