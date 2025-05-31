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

/************************* Variables for main program ***********************************/
    int Round = 0;
    bool Spawning = true;
    int Spawnbot = 0;
    int Endgame = 0;
    int ExtraBot = 0;
    string Winner;

    ifstream infile;
    infile.open("Robotinput.txt");

    ofstream outfile;
    outfile.open("Robotoutput.txt"); // place ',ios::append' if u wish to not overwrite the file

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
    queue<ShootingRobot*> RobotQueue;


    // Check whether the 
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
            newBot->GetShells(numberOfRobots);
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
            if (RoboMoveCopies[i] == nullptr) continue; // Checking for if the pointer for that specific element is null or not
            if (RoboMoveCopies[i]->CheckLives() <= 0) continue;
            

            if (battlefield.CountNumSteps <= 0)
            {
                break;
            }

            //system("CLS");

            if (Spawning)
            {
                cout << "Spawning..." << endl;
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
            
            Round += 1;
            cout << endl << "ROUND " << Round << endl;
            cout << endl << "Robot " << RoboMoveCopies[i]->GetSignia() << "'s Turn" << endl;

            vector<int> Trashbin;
            
            if (!Spawning)
            {
                // Robot Actions (Looking & Shooting)
                for (int j=0; j<RoboMoveCopies.size(); j++)
                {
                    if (RoboMoveCopies[i] == nullptr || RoboMoveCopies[j] == nullptr || i == j )
                    {
                        continue;
                    }
                    
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

                    if (RoboMoveCopies[i]->RobotDetect() && !RoboMoveCopies[j]->CheckQueue() && !RoboMoveCopies[j]->HideBot())
                    {
                        cout << "Robot "<< RoboMoveCopies[i]->GetSignia() << " detects Robot " << RoboMoveCopies[j]->GetSignia() << endl;
                        RoboMoveCopies[i]->ShootheRobot();
                        RoboMoveCopies[i]->CheckShot(RoboMoveCopies[j]->GetSignia(), numberOfRobots);

                        if (RoboMoveCopies[i]->GetShooting() && !RoboMoveCopies[j]->CheckQueue())
                        {
                            RoboMoveCopies[j]->DeductLives();
                            RoboMoveCopies[j]->SetQueue();
                            Trashbin.push_back(j); // Puts shot robot into an array

                            if (!*RoboMoveCopies[i]->RobotUpgraded) ///////////////////////Going to make the upgrades stackable later
                            {
                                RoboMoveCopies[i]->Upgrade();
                                *RoboMoveCopies[i]->RobotUpgraded = true;
                            }
                            
                            if (RoboMoveCopies[i]->CheckExplosion())
                            {
                                break;
                            }
                        }
                    }
                }
            }

            if (RoboMoveCopies[i]->CheckExplosion())
            {
                cout << "Robot " << RoboMoveCopies[i]->GetSignia() << " is out of shells and is now initiating self-destruct." << endl;
                RoboMoveCopies[i]->DeductLives();
                RoboMoveCopies[i]->SetQueue();
                Trashbin.push_back(i);
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

                    if (RoboMoveCopies[x]->CheckLives() <= 0)
                    {
                        cout << "Robot " << RoboMoveCopies[x]->GetSignia() << " has lost all lives and is removed.\n";
                        delete RoboMoveCopies[x]; // Deletes the object of the shot robot
                        RoboMoveCopies[x] = nullptr;
                        Endgame += 1;
                    }
                    else
                    {
                        if (RoboMoveCopies[x]->Checkshells() != 0)
                        {
                            cout << "Robot " << RoboMoveCopies[x]->GetSignia() << " was shot and is in queue.\n";
                        }
                        RobotQueue.push(RoboMoveCopies[x]);
                        RoboMoveCopies[x] = nullptr; // Cleans up the pointer of the removed robot
                    }
                }
            }

            cout << endl;
            // Print logs
            for (int k = 0; k < RoboMoveCopies.size(); k++)
            {
                if (!RoboMoveCopies[k]) continue;
                if (!RoboMoveCopies[k]->current_row || !RoboMoveCopies[k]->current_col || !RoboMoveCopies[k]->CheckLives()) continue;

                cout << "Robot " << RoboMoveCopies[k]->GetSignia() << " Coordinates: (" << *RoboMoveCopies[k]->current_row
                    << "," << *RoboMoveCopies[k]->current_col << ")"
                    << " Lives: " << RoboMoveCopies[k]->CheckLives() << " Shells left: "<< RoboMoveCopies[k]->Checkshells() << endl;

                RoboMoveCopies[k]->PrintUpgrades();

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
                cout << endl;

            }

            if (Endgame == (numberOfRobots - 1))
            {
                Winner = RoboMoveCopies[i]->GetSignia();
                break;
            }
            if (Endgame == numberOfRobots)
            {
                break;
            }
            
            battlefield.delay(1000);
        }

        if (!Spawning)
        {
            int Gacha = rand() % 7;
            //Get 3 new robots
            if (Gacha == 0 && ExtraBot != 3)
            {
                cout << "!!A new AI bot has randomly spawned!!" << endl;
                ShootingRobot* extraBot = new ShootingRobot(row, col);
                string signia = "$&@";
                extraBot->SetSignia(signia[ExtraBot]);
                extraBot->GetShells(numberOfRobots);
                extraBot->NewSpawn(battlefield.Grid);
                RoboMoveCopies.push_back(extraBot);
                ExtraBot += 1;
                battlefield.delay(1500);
            }
        }
        

        int turn = 0;
        if (Spawnbot > 0)
        {
            if (!RobotQueue.empty() && turn == 0 )
            {
                ShootingRobot* WaitingBot = RobotQueue.front();
                RobotQueue.pop();

                if (WaitingBot != nullptr && WaitingBot->CheckLives() > 0)
                {
                    cout << "Robot " << WaitingBot->GetSignia() << " is removed from queue.\n";
                    WaitingBot->NullifyQueue();
                    WaitingBot->GetShells(numberOfRobots);
                    WaitingBot->NewSpawn(battlefield.Grid);
                    RoboMoveCopies.push_back(WaitingBot);
                    battlefield.delay(1500);
                }
                turn += 1;
            }
            Spawnbot = 0;
        }
        else
        {
            Spawnbot += 1;
        }

        // Get winner of the program
        if (Endgame == (numberOfRobots - 1))
        {
            break;
        }
        if (Endgame == numberOfRobots)
        {
            break;
        }
        
        Spawning = false;
    }

    if (!Winner.empty())
    {
        cout << endl << "!!ROBOT " << Winner << " IS THE WINNER!!" << endl; 
    }
    else
    {
        cout << endl << "Match ends with no winner" << endl; 
    }

    return 0;
}