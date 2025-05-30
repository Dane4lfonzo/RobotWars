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
    queue<ShootingRobot*> RobotQueue;


    // Check whether the 
    if (numberOfRobots > RoboNames.size())
    {
        cout << "Number of robots entered exceed the amount given. Quitting Simulation..." << endl;
        outfile << "Number of robots entered exceed the amount given. Quitting Simulation..." << endl;
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
            outfile << "Robot Position " << RoboMoveCopies[i]->GetSignia() << " is out of bounds. Quitting Simulation..." << endl; 
            return 1;
        }

        if ((*RoboMoveCopies[i]->current_col < 0) || (*RoboMoveCopies[i]->current_col >= col))
        {
            cout << "Robot Position " << RoboMoveCopies[i]->GetSignia() << " is out of bounds. Quitting Simulation..." << endl;
            outfile << "Robot Position " << RoboMoveCopies[i]->GetSignia() << " is out of bounds. Quitting Simulation..." << endl;
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
            
            Round += 1;
            cout << endl << "ROUND " << Round << endl;
            cout << endl << "Robot " << RoboMoveCopies[i]->GetSignia() << "'s Turn" << endl;

            unordered_set<int> Trashbin;
            
            if (!Spawning)
            {
                // Robot Actions (Looking & Shooting)
                for (int j=0; j<RoboMoveCopies.size(); j++)
                {
                    if (RoboMoveCopies[i] == nullptr || RoboMoveCopies[j] == nullptr || i == j)
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

                    if (!RoboMoveCopies[j]->HideBot())
                    {
                        RoboMoveCopies[i]->Look(*RoboMoveCopies[j]->current_row, *RoboMoveCopies[j]->current_col);
                    }

                    if (RoboMoveCopies[i]->RobotDetect() && !RoboMoveCopies[j]->CheckQueue() && !RoboMoveCopies[j]->HideBot())
                    {
                        cout << "Robot "<< RoboMoveCopies[i]->GetSignia() << " detects Robot " << RoboMoveCopies[j]->GetSignia() << endl;
                        RoboMoveCopies[i]->ShootheRobot();
                        RoboMoveCopies[i]->CheckShot(RoboMoveCopies[j]->GetSignia(), numberOfRobots);
                        cout << RoboMoveCopies[i]->GetSignia() << "'s Shells left: " << RoboMoveCopies[i]->Checkshells() << endl;

                        if (RoboMoveCopies[i]->GetShooting() && !RoboMoveCopies[j]->CheckQueue())
                        {
                            RoboMoveCopies[j]->DeductLives();
                            RoboMoveCopies[j]->SetQueue();
                            if (RoboMoveCopies[j]->CheckLives() != 0)
                            {
                                cout << "Robot " << RoboMoveCopies[j]->GetSignia() << " was shot and is in queue.\n";
                            }
                            Trashbin.insert(j); // Puts shot robot into an array

                            if (!*RoboMoveCopies[i]->RobotUpgraded) ///////////////////////Going to make the upgrades stackable later
                            {
                                RoboMoveCopies[i]->Upgrade();
                                *RoboMoveCopies[i]->UpgradeLimit += 1;
                                if (*RoboMoveCopies[i]->UpgradeLimit >= 3)
                                {
                                    *RoboMoveCopies[i]->RobotUpgraded = true;
                                } 
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
                Trashbin.insert(i);
            }

            // Cleans up the shot Robot
            for (int x : Trashbin)
            {
                if (RoboMoveCopies[x] != nullptr)
                {
                    // Clear grid symbol before deleting
                    if (RoboMoveCopies[x]->current_row != nullptr && RoboMoveCopies[x]->current_col != nullptr)
                    {

                        // Clear grid symbol before deleting
                        if (RoboMoveCopies[x]->current_row && RoboMoveCopies[x]->current_col)
                        {
                            battlefield.Grid[*RoboMoveCopies[x]->current_row][*RoboMoveCopies[x]->current_col] = ".";
                        }
                        cout << "Robot " << RoboMoveCopies[x]->GetSignia() << " was shot and removed.\n";

                        ofstream outfile;
                        outfile.open("Robotoutput.txt", ios::app);
                        outfile << "Robot " << RoboMoveCopies[x]->GetSignia() << " was shot and removed.\n";
                        battlefield.Grid[*RoboMoveCopies[x]->current_row][*RoboMoveCopies[x]->current_col] = ".";
                    }

                    if (RoboMoveCopies[x]->CheckLives() <= 0)
                    {
                        cout << "Robot " << RoboMoveCopies[x]->GetSignia() << " has lost all lives and is removed.\n";

                        delete RoboMoveCopies[x]; // Deletes the object of the shot robot
                        RoboMoveCopies[x] = nullptr;
                        Endgame += 1;
                    }
                    else if (RoboMoveCopies[x]->CheckLives() > 0)
                    {
                        RobotQueue.push(RoboMoveCopies[x]);
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

                    ofstream outfile;
                    outfile.open("Robotoutput.txt", ios::app);
                    outfile << "Robot " << RoboMoveCopies[k]->GetSignia() << " row: " << *RoboMoveCopies[k]->current_row
                        << " col: " << *RoboMoveCopies[k]->current_col
                        << " Shots: " << *RoboMoveCopies[k]->shootFlag << endl;

                    if (*RoboMoveCopies[k]->printtrackList)  //Ensures that the robots being tracked are still printed after the uses run out
                    {
                        cout << "TrackList: " << *RoboMoveCopies[k]->trackList << endl;
                        outfile << "TrackList: " << *RoboMoveCopies[k]->trackList << endl;
                    }

                    if (RoboMoveCopies[k]->ScoutBot())
                    {
                        if (RoboMoveCopies[k] == nullptr)
                        {
                            continue;
                        }
                        
                        cout << "Robot " << RoboMoveCopies[k]->GetSignia() << " sees:";
                        ofstream outfile;
                        outfile.open("Robotoutput.txt", ios::app);
                        outfile << "Robot " << RoboMoveCopies[k]->GetSignia() << " sees:";

                        for (int x = 0; x < RoboMoveCopies.size(); x++)
                        {
                            if (RoboMoveCopies[x] == nullptr || RoboMoveCopies[x]->current_row == nullptr 
                                || RoboMoveCopies[x]->current_col == nullptr || x == k) continue;
                                                                                                                               
                            cout << " Robot " << RoboMoveCopies[x]->GetSignia() << " at (" << *RoboMoveCopies[x]->current_row << ", " << *RoboMoveCopies[x]->current_col << ")";
                            cout << ",";
                            ofstream outfile;
                            outfile.open("Robotoutput.txt", ios::app);
                            outfile << " Robot " << RoboMoveCopies[x]->GetSignia() << " at (" << *RoboMoveCopies[x]->current_row << ", " << *RoboMoveCopies[x]->current_col << ")";
                            outfile << ",";
                        }
                        cout << endl;
                        outfile << endl;
                    }

                }
                
                battlefield.delay(1000);
            }
            cout << endl;
            if (RoboMoveCopies[i] == nullptr)
            {
                continue;
            }
            RoboMoveCopies[i]->UpdateThirtyShot(numberOfRobots);

            // Print logs
            for (int k = 0; k < RoboMoveCopies.size(); k++)
            {
                if (RoboMoveCopies[k] == nullptr) continue;

                if (RoboMoveCopies[k]->current_row == nullptr || RoboMoveCopies[k]->current_col == nullptr || 
                    RoboMoveCopies[k]->CheckLives() <= 0 ) continue;

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
                    cout << "Robot " << RoboMoveCopies[k]->GetSignia() << " sees:";

                    for (int x = 0; x < RoboMoveCopies.size(); x++)
                    {
                        if (RoboMoveCopies[x] == nullptr) continue;
                        if (x == k) continue;
                        if (RoboMoveCopies[x]->current_row == nullptr || RoboMoveCopies[x]->current_col == nullptr) continue;
                                                                                                                            
                        cout << " Robot " << RoboMoveCopies[x]->GetSignia() << " at (" << *RoboMoveCopies[x]->current_row << ", " << *RoboMoveCopies[x]->current_col << ")";
                        cout << ",";
                    }
                    cout << endl;
                }
                cout << endl;

            }

            if (Endgame == (numberOfRobots + ExtraBot - 1))
            {
                Winner = RoboMoveCopies[i]->GetSignia();
                break;
            }
            if (Endgame == numberOfRobots + ExtraBot)
            {
                break;
            }
            cout << "Dead Robots: " << Endgame << endl;
            battlefield.delay(500);
        }
        
        int Gacha = rand() % 3;
        int oneSpawn = 0;
        //Get 3 new robots
        if (!Spawning)
        {
            if (Gacha == 0 && ExtraBot != 3 && oneSpawn == 0)
            {
                cout << "!!A new AI bot has randomly spawned!!" << endl;
                ShootingRobot* extraBot = new ShootingRobot(row, col);
                string sig = "$&@";
                extraBot->SetSignia(sig[ExtraBot]);
                extraBot->GetShells(numberOfRobots);
                extraBot->NewSpawn(battlefield.Grid);
                RoboMoveCopies.push_back(extraBot);
                ExtraBot += 1;
                oneSpawn += 1;
            }
        }
        

        int turn = 0;
        if (Spawnbot > 0)
        {
            if (!RobotQueue.empty() && turn == 0)
            {
                ShootingRobot* WaitingBot = RobotQueue.front();
                RobotQueue.pop();

                if (WaitingBot != nullptr && WaitingBot->CheckLives() > 0)
                {
                    cout << "Robot " << WaitingBot->GetSignia() << " is removed from queue.\n";
                    WaitingBot->NullifyQueue();
                    WaitingBot->ResetUpgrades(); // Resets the robot upgrade variables for a clean slate
                    WaitingBot->GetShells(numberOfRobots);
                    WaitingBot->NewSpawn(battlefield.Grid);
                    RoboMoveCopies.push_back(WaitingBot);
                    //battlefield.delay(1000);
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
        if (Endgame == (numberOfRobots + ExtraBot - 1))
        {
            break;
        }
        if (Endgame == numberOfRobots + ExtraBot)
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