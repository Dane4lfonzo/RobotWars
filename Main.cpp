#include "Class.h"

int main()
{
    srand(time(0));
/*************** Variables for Yuven's readfile function later **************************/
    int row = 5;
    int col = 10;
    int numofsteps = 100;
    int numberOfRobots = 4;
    bool Spawning = true;
    string TestChars = "ABCD";
    bool SetSignia = true;
/****************************************************************************************/

    // Create standalone Battlefield object (not tied to any robot)
    Battlefield battlefield(row, col); // Original class instance
    battlefield.GridMaker();
    battlefield.SetStep(numofsteps);
    vector<ShootingRobot*> RoboMoveCopies; // Copy Constructor class instance for the robot classes but as an Array(Vector)
    queue<ShootingRobot*> RobotQueue;


    if (SetSignia)
    {
        for (int i = 0; i < numberOfRobots; i++)
        {
            ShootingRobot* newBot = new ShootingRobot(row, col); // Creates new object during the runtime (
                                                                //  dynamically) and store a new pointer
            newBot->SetSignia(TestChars[i]);
            RoboMoveCopies.push_back(newBot); // Each object is created anew and pushed into the vector
        }
        SetSignia = false;
    }
      
    while (battlefield.StepCount())
    {
        for (int i = 0; i < RoboMoveCopies.size(); i++) 
        {
            if (RoboMoveCopies[i] == nullptr) continue; // Checking for if the pointer for that specific element is null or not
            if (RoboMoveCopies[i]->CheckLives() <= 0) continue;
            
            system("CLS");

            if (Spawning)
            {
                cout << "Spawning..." << endl;
            }
            
            // Robot movement
            RoboMoveCopies[i]->WheretoMove();
            RoboMoveCopies[i]->MovetoSquare(battlefield.Grid);

            // Counts one step for robot
            battlefield.CountDownStep();
            
            // Displays the Grid and Robots
            battlefield.printGrid();

            vector<int> Trashbin;
            
            if (Spawning == false)
            {
                // Robot Actions (Looking & Shooting)
                for (int j=0; j<RoboMoveCopies.size(); j++)
                {
                    if (RoboMoveCopies[i] == nullptr || RoboMoveCopies[j] == nullptr || i == j) continue;

                    /*if (!(*RoboMoveCopies[i]->current_col == *RoboMoveCopies[j]->current_col && 
                        *RoboMoveCopies[i]->current_row == *RoboMoveCopies[j]->current_row)) continue; // prevents from "looking " at itself */
                    

                    if (!RoboMoveCopies[i]->current_row || !RoboMoveCopies[i]->current_col ||
                    !RoboMoveCopies[j]->current_row || !RoboMoveCopies[j]->current_col)  continue; 

                    if (RoboMoveCopies[i]->current_row == nullptr || RoboMoveCopies[i]->current_col == nullptr ||
                    RoboMoveCopies[j]->current_row == nullptr || RoboMoveCopies[j]->current_col == nullptr) continue;
                    

                    // Check if robots are not in the same cell
                    if (*RoboMoveCopies[i]->current_col == *RoboMoveCopies[j]->current_col &&
                        *RoboMoveCopies[i]->current_row == *RoboMoveCopies[j]->current_row) continue;
                        
                    RoboMoveCopies[i]->Look(*RoboMoveCopies[j]->current_row, *RoboMoveCopies[j]->current_col);

                    if (RoboMoveCopies[i]->RobotDetect())
                    {
                        RoboMoveCopies[i]->ShootheRobot();
                        RoboMoveCopies[i]->CheckShot();

                        if (RoboMoveCopies[i]->GetShooting() && !RoboMoveCopies[j]->CheckQueue())
                        {
                            RoboMoveCopies[j]->DeductLives();
                            RoboMoveCopies[j]->SetQueue();
                            Trashbin.push_back(j); // Puts shot robot into an array
                        }
                    }
                }
            }

            // Cleans up the shot Robot
            for (int x : Trashbin)
            {
                if (RoboMoveCopies[x] != nullptr)
                {
                    // Clear grid symbol before deleting
                    if (RoboMoveCopies[x]->current_row && RoboMoveCopies[x]->current_col)
                    {
                        battlefield.Grid[*RoboMoveCopies[x]->current_row][*RoboMoveCopies[x]->current_col] = ".";
                    }
                    cout << "Robot " << RoboMoveCopies[x]->GetSignia() << " was shot and removed.\n";

                    if (RoboMoveCopies[x]->CheckLives() == 0)
                    {
                        delete RoboMoveCopies[x]; // Deletes the object of the shot robot
                        RoboMoveCopies[x] = nullptr;
                    }
                    else
                    {
                        RobotQueue.push(RoboMoveCopies[x]);
                        RoboMoveCopies[x] = nullptr; // Cleans up the pointer of the removed robot
                    }
                }
            }

            // Print logs
            for (int k = 0; k < RoboMoveCopies.size(); k++)
            {
                if (!RoboMoveCopies[k]) continue;
                if (!RoboMoveCopies[k]->current_row || !RoboMoveCopies[k]->current_col || !RoboMoveCopies[k]->CheckLives()) continue;

                cout << "Robot " << RoboMoveCopies[k]->GetSignia() << " Coordinates: (" << *RoboMoveCopies[k]->current_row
                    << "," << *RoboMoveCopies[k]->current_col << ")"
                    << " Lives: " << RoboMoveCopies[k]->CheckLives() << endl;
                    
            }
            
            battlefield.delay(600);
        }
        if (!RobotQueue.empty())
        {
            ShootingRobot* WaitingBot = RobotQueue.front();
            RobotQueue.pop();

            if (WaitingBot != nullptr && WaitingBot->CheckLives() > 0)
            {
                WaitingBot->NullifyQueue();
                RoboMoveCopies.push_back(WaitingBot);
            }
        }
        Spawning = false;
    }

    return 0;
}