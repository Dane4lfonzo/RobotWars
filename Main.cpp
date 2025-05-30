#include "Class.h"

int main()
{
    srand(time(0));
/*************** Variables for Yuven's readfile function later **************************/
    int row;
    int col;
    int numofsteps;
    int numberOfRobots;
    vector<string> check_spawn_condition;
    string RoboNames;

    int TestVal = 0;
    bool SetSignia = true;
    bool Spawning = true;

    ifstream infile;
    infile.open("Robotinput.txt");

    ofstream outfile;
    outfile.open("Robotoutput.txt", ios::app); // place ',ios::append' if u wish to not overwrite the file

    //shows error if both files fail to open
    if (!infile || !outfile)
    {
        cout << "Error: Could not open the input and output files." << endl;
        return 1;
    }

    filereading(infile, outfile, row, col, numofsteps, numberOfRobots, RoboNames, check_spawn_condition);
/****************************************************************************************/

    // Create standalone Battlefield object (not tied to any robot)
    Battlefield battlefield(row, col); // Original class instance
    battlefield.GridMaker();
    battlefield.SetStep(numofsteps);
    vector<ShootingRobot*> RoboMoveCopies; // Copy Constructor class instance for the robot classes but as an Array(Vector)

    if (numberOfRobots > RoboNames.size())
    {
        cout << "Number of robots entered exceed the amount given. Quitting Simulation..." << endl;
        return 1;
    }

    if (SetSignia)
    {
        for (int i = 0; i < numberOfRobots; i++)
        {
            ShootingRobot* newBot = new ShootingRobot(row, col); // Creates new object during the runtime (
                                                                //  dynamically) and store a new pointer
            newBot->SetSignia(RoboNames[i]);
            RoboMoveCopies.push_back(newBot); // Each object is created anew and pushed into the vector         
        }
    
        SetSignia = false;
    }

    //This for loop is to assign the positions of all robots according to the input txt file given
    for (int i=0; i < numberOfRobots; i++)
    {
        RoboMoveCopies[i]->SetCurrentPos(check_spawn_condition, TestVal);
    }

    //This for loop is to ensure that the robot positions given are confined within the Grid
    for (int i=0; i < numberOfRobots; i++)
    {
        if ((*RoboMoveCopies[i]->current_row < 0) || (*RoboMoveCopies[i]->current_row >= row))
        {
            cout << "Robot Position " << RoboMoveCopies[i]->GetSignia() << " is out of bounds. Quitting Simulation..." << endl;
            return 1;
        }

        if ((*RoboMoveCopies[i]->current_col < 0) || (*RoboMoveCopies[i]->current_col >= col))
        {
            cout << "Robot Position " << RoboMoveCopies[i]->GetSignia() << " is out of bounds. Quitting Simulation..." << endl;
            return 1;            
        }
    }
      

    while (battlefield.StepCount())
    {
        for (int i = 0; i < RoboMoveCopies.size(); i++) 
        {
            if (RoboMoveCopies[i] == nullptr) 
            {
                continue; // Checking for if the pointer for that specific element is null or not
            }

            if (battlefield.CountNumSteps <= 0)
            {
                break;
            }

            //system("CLS");

            if (Spawning)
            {
                cout << "Spawning..." << endl;
                
                ofstream outfile;
                outfile.open("Robotoutput.txt", ios::app);
                outfile << "Spawning..." << endl;

                RoboMoveCopies[i]->PlaceRobot(battlefield.Grid);
            }
            
            // Robot movement
            RoboMoveCopies[i]->WheretoMove();

            if (Spawning == false)
            {
                RoboMoveCopies[i]->MovetoSquare(battlefield.Grid);
            }

            //Updates the number of uses of each upgrades if the robot has one
            RoboMoveCopies[i]->UpdateUsage();

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
                    if (RoboMoveCopies[i] == nullptr || RoboMoveCopies[j] == nullptr || i == j || RoboMoveCopies[j]->HideBot()) //|| RoboMoveCopies[j]->HideBot()
                    {
                        continue;
                    }
                    /*if (!(*RoboMoveCopies[i]->current_col == *RoboMoveCopies[j]->current_col && 
                        *RoboMoveCopies[i]->current_row == *RoboMoveCopies[j]->current_row)) continue; // prevents from "looking " at itself */
                    

                    if (!RoboMoveCopies[i]->current_row || !RoboMoveCopies[i]->current_col ||
                    !RoboMoveCopies[j]->current_row || !RoboMoveCopies[j]->current_col)  
                    {
                        continue; 
                    }

                    if (RoboMoveCopies[i]->current_row == nullptr || RoboMoveCopies[i]->current_col == nullptr ||
                    RoboMoveCopies[j]->current_row == nullptr || RoboMoveCopies[j]->current_col == nullptr) 
                    {
                        continue;
                    }

                    // Check if robots are not in the same cell
                    if (*RoboMoveCopies[i]->current_col == *RoboMoveCopies[j]->current_col &&
                        *RoboMoveCopies[i]->current_row == *RoboMoveCopies[j]->current_row) 
                    {
                        continue;
                    }

                    RoboMoveCopies[i]->Look(*RoboMoveCopies[j]->current_row, *RoboMoveCopies[j]->current_col);

                    if (RoboMoveCopies[i]->RobotDetect())
                    {
                        RoboMoveCopies[i]->ShootheRobot();
                        RoboMoveCopies[i]->CheckShot(RoboMoveCopies[j]->GetSignia(), numberOfRobots);

                        if (RoboMoveCopies[i]->GetShooting())
                        {
                            Trashbin.push_back(j); // Puts shot robot into an array
                            if (!*RoboMoveCopies[i]->RobotUpgraded) ///////////////////////Going to make the upgrades stackable later
                            {
                                RoboMoveCopies[i]->Upgrade();
                                *RoboMoveCopies[i]->RobotUpgraded = true;
                            }
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
                        delete RoboMoveCopies[x]; // Deletes the object of the shot robot
                        RoboMoveCopies[x] = nullptr; // Cleans up the pointer of the removed robot
                    }
                }

                // Print logs
                for (int k = 0; k < RoboMoveCopies.size(); k++)
                {
                    //if (RoboMoveCopies[k] == nullptr) continue;
                    if (RoboMoveCopies[k] == nullptr || RoboMoveCopies[k]->current_row == nullptr 
                        || RoboMoveCopies[k]->current_col == nullptr || RoboMoveCopies[k]->shootFlag == nullptr)
                        {
                            continue;
                        } 

                    cout << "Robot " << RoboMoveCopies[k]->GetSignia() << " row: " << *RoboMoveCopies[k]->current_row
                        << " col: " << *RoboMoveCopies[k]->current_col
                        << " Shots: " << *RoboMoveCopies[k]->shootFlag << endl;

                    if (*RoboMoveCopies[k]->printtrackList)  //Ensures that the robots being tracked are still printed after the uses run out
                    {
                        cout << "TrackList: " << *RoboMoveCopies[k]->trackList << endl;
                    }

                    if (RoboMoveCopies[k]->ScoutBot())
                    {
                        if (RoboMoveCopies[k] == nullptr)
                        {
                            continue;
                        }
                        cout << "Robot " << RoboMoveCopies[k]->GetSignia() << " sees:";

                        for (int x = 0; x < RoboMoveCopies.size(); x++)
                        {
                            if (RoboMoveCopies[x] == nullptr || RoboMoveCopies[x]->current_row == nullptr 
                                || RoboMoveCopies[x]->current_col == nullptr || x == k) continue;
                                                                                                                               
                            cout << " Robot " << RoboMoveCopies[x]->GetSignia() << " at (" << *RoboMoveCopies[x]->current_row << ", " << *RoboMoveCopies[x]->current_col << ")";
                            cout << ",";
                        }
                        cout << endl;
                    }

                }
                
                battlefield.delay(1000);
            }
         Spawning = false;
    }

    return 0;
}