/**********|**********|**********|
 Program: Main.cpp / Class.cpp / Class.h 
Course: Data Structures and Algorithms
 Trimester: 2410

 Name: DANIEL ARIF BIN ABD ZAINEE
 ID: 242UC244JU
 Lecture Section: TC3L
 Tutorial Section: T11L
 Email: DANIEL.ARIF.ABD@student.mmu.edu.my
 Phone: 0137469125

 Name: NUR YASMIN BINTI MOHD SABRI
 ID: 242UC244TX
 Lecture Section: TC3L
 Tutorial Section: T11L
 Email: NUR.YASMIN.MOHD@student.mmu.edu.my
 Phone: 0197828428

 Name: MUHAMMAD NUR AIZAD BIN MURTADHA
 ID: 242UC244T5
 Lecture Section: TC3L
 Tutorial Section: T11L
 Email: MUHAMMAD.NUR.AIZAD@student.mmu.edu.my
 Phone: 0195659972

 Name: YUVENDAR A/L MARAN
 ID: 242UC244DJ
 Lecture Section: TC3L
 Tutorial Section: T11L
 Email: YUVENDAR.MARAN@student.mmu.edu.my
 Phone: 0127420244
 **********|**********|**********/

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

    // Function to read the input file and write into the output file
    filereading(infile, outfile, row, col, numofsteps, numberOfRobots, RoboNames, check_spawn_condition);
/****************************************************************************************/

    // Create standalone Battlefield object (not tied to any robot)
    Battlefield battlefield(row, col); // Original class instance
    battlefield.GridMaker();
    battlefield.SetStep(numofsteps);
    vector<ShootingRobot*> RoboMoveCopies; // Copy Constructor class instance for the robot classes but as an Array(Vector)
    queue<ShootingRobot*> RobotQueue;

    // output file variables
    ofstream outlogfile;
    outlogfile.open("Robotoutput.txt", ios::app);

    // Check whether the Robot amount exceeds the bounds
    if (numberOfRobots > RoboNames.size())
    {
        cout << "Number of robots entered exceed the amount given. Quitting Simulation..." << endl;
        outlogfile << "Number of robots entered exceed the amount given. Quitting Simulation..." << endl;
        return 1;
    }

    // Set the Signia for Robots
    if (SetSignia)
    {
        for (int i = 0; i < numberOfRobots; i++)
        {
            ShootingRobot* newBot = new ShootingRobot(row, col); // Creates new object during the runtime (
                                                                //  dynamically) and store a new pointer
            newBot->SetSignia(RoboNames[i]);
            newBot->GetShells(10); 
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
            outlogfile << "Robot Position " << RoboMoveCopies[i]->GetSignia() << " is out of bounds. Quitting Simulation..." << endl; 
            return 1;
        }

        if ((*RoboMoveCopies[i]->current_col < 0) || (*RoboMoveCopies[i]->current_col >= col))
        {
            cout << "Robot Position " << RoboMoveCopies[i]->GetSignia() << " is out of bounds. Quitting Simulation..." << endl;
            outlogfile << "Robot Position " << RoboMoveCopies[i]->GetSignia() << " is out of bounds. Quitting Simulation..." << endl;
            return 1;            
        }

        if (numberOfRobots >= (row*col))
        {
           cout << "Number of robots maximizes Battlefield space, no room for simulation. Quitting Simulation..." << endl;
           return 1; 
        }
    }
      

    // Check while the amount of steps is not 0
    while (battlefield.StepCount())
    {
        
        // Cycles through the robots in the array
        for (int i = 0; i < RoboMoveCopies.size(); i++) 
        {
            if (RoboMoveCopies[i] == nullptr) continue; // Checking for if the pointer for that specific element is null or not
            if (RoboMoveCopies[i]->CheckLives() <= 0) continue;
            
            // If the amount of step has reached 0, the program automatically ends
            if (battlefield.CountNumSteps <= 0)
            {
                break;
            }

            // For cleaner printing
            system("CLS");

            // Check if all the robots initiated in the beginning has spawned
            if (Spawning)
            {
                cout << "Spawning..." << endl;
                outlogfile << "Spawning..." << endl;

                RoboMoveCopies[i]->PlaceRobot(battlefield.Grid);
            }
            
            // Get Robot choice for movement
            RoboMoveCopies[i]->WheretoMove();

            // Condition to avoid robot from moving before all robots are initiated into the battlefield
            if (Spawning == false)
            {
                // Robot Movements
                RoboMoveCopies[i]->MovetoSquare(battlefield.Grid);
            }

            //Updates the number of uses of each upgrades if the robot has one
            RoboMoveCopies[i]->UpdateUsage();

            // Counts one step for robot
            battlefield.CountDownStep();
            
            // Displays the Grid and Robots
            battlefield.printGrid();
            
            // Printings
            Round += 1;
            cout << endl << "ROUND " << Round << endl;
            cout << endl << "Robot " << RoboMoveCopies[i]->GetSignia() << "'s Turn" << endl;

            outlogfile << endl << "ROUND " << Round << endl << endl << "Robot " << RoboMoveCopies[i]->GetSignia() << "'s Turn" << endl;

            // Set array
            unordered_set<int> Trashbin;
            
            if (!Spawning)
            {
                // Robot Actions (Looking & Shooting)
                for (int j=0; j<RoboMoveCopies.size(); j++)
                {
                    // Check if the current robot is not null and is not the same as the compared robot---------------------------
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
                    //-----------------------------------------------------------------------------------------------------------

                    // Check if robots are not in the same cell
                    if (*RoboMoveCopies[i]->current_col == *RoboMoveCopies[j]->current_col &&
                        *RoboMoveCopies[i]->current_row == *RoboMoveCopies[j]->current_row) 
                    {
                        continue;
                    }

                    // Check so that the compared robot does not have the HideBot immunity
                    if (!RoboMoveCopies[j]->HideBot())
                    {
                        RoboMoveCopies[i]->Look(*RoboMoveCopies[j]->current_row, *RoboMoveCopies[j]->current_col);
                    }

                    // Check for detection
                    if (RoboMoveCopies[i]->RobotDetect() && !RoboMoveCopies[j]->CheckQueue() && !RoboMoveCopies[j]->HideBot())
                    {
                        cout << "Robot "<< RoboMoveCopies[i]->GetSignia() << " detects Robot " << RoboMoveCopies[j]->GetSignia() << endl;
                        outlogfile << "Robot "<< RoboMoveCopies[i]->GetSignia() << " detects Robot " << RoboMoveCopies[j]->GetSignia() << endl;

                        // Check if Robot was able to shoot the detected robot
                        RoboMoveCopies[i]->ShootheRobot();
                        RoboMoveCopies[i]->CheckShot(RoboMoveCopies[j]->GetSignia(), numberOfRobots);
                        cout << RoboMoveCopies[i]->GetSignia() << "'s Shells left: " << RoboMoveCopies[i]->Checkshells() << endl;
                        outlogfile << RoboMoveCopies[i]->GetSignia() << "'s Shells left: " << RoboMoveCopies[i]->Checkshells() << endl;

                        if (RoboMoveCopies[i]->GetShooting() && !RoboMoveCopies[j]->CheckQueue())
                        {
                            RoboMoveCopies[j]->DeductLives(); // Deduct shot robot's life
                            RoboMoveCopies[j]->SetQueue(); // Set shot robot into queue

                            if (RoboMoveCopies[j]->CheckLives() != 0)
                            {
                                cout << "Robot " << RoboMoveCopies[j]->GetSignia() << " was shot and is in queue.\n";
                                outlogfile << "Robot " << RoboMoveCopies[j]->GetSignia() << " was shot and is in queue.\n";
                            }
                            Trashbin.insert(j); // Puts shot robot into an array set

                            // Check if the current robot has fully upgraded from a successful shot or not
                            if (!*RoboMoveCopies[i]->RobotUpgraded) 
                            {
                                RoboMoveCopies[i]->Upgrade(); // Choosing upgrades
                                *RoboMoveCopies[i]->UpgradeLimit += 1;
                                if (*RoboMoveCopies[i]->UpgradeLimit >= 3) // Condition to check if all stack upgrades are in
                                {
                                    *RoboMoveCopies[i]->RobotUpgraded = true;
                                } 
                            }
                            
                            // Check if current robot has run out of ammo or not
                            if (RoboMoveCopies[i]->CheckExplosion())
                            {
                                break;
                            }
                        }
                    }
                }
            }

            // Initiate self-destruct for robot that has run out of shells
            if (RoboMoveCopies[i]->CheckExplosion())
            {
                cout << "Robot " << RoboMoveCopies[i]->GetSignia() << " is out of shells and is now initiating self-destruct." << endl;
                outlogfile << "Robot " << RoboMoveCopies[i]->GetSignia() << " is out of shells and is now initiating self-destruct." << endl;

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
                    }

                    // Check if robot has no lives left
                    if (RoboMoveCopies[x]->CheckLives() <= 0)
                    {
                        cout << "Robot " << RoboMoveCopies[x]->GetSignia() << " has lost all lives and is removed.\n";
                        outlogfile << "Robot " << RoboMoveCopies[x]->GetSignia() << " has lost all lives and is removed.\n";
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
            }

            cout << endl;
            outlogfile << endl;

            if (RoboMoveCopies[i] != nullptr)
            {
                RoboMoveCopies[i]->UpdateThirtyShot();
            }

            // Print logs
            for (int k = 0; k < RoboMoveCopies.size(); k++)
            {
                if (RoboMoveCopies[k] == nullptr) continue;

                if (RoboMoveCopies[k]->current_row == nullptr || RoboMoveCopies[k]->current_col == nullptr || 
                    RoboMoveCopies[k]->CheckLives() <= 0 ) continue;

                cout << *RoboMoveCopies[k] << endl; // <<operator overloading

                outlogfile << *RoboMoveCopies[k] << endl; // <<operator overloading

                RoboMoveCopies[k]->PrintUpgrades();

                if (*RoboMoveCopies[k]->printtrackList)  //Ensures that the robots being tracked are still printed after the uses run out
                {
                    if (!(*RoboMoveCopies[k]->trackList).empty())
                    {
                        cout << "TrackList: " << *RoboMoveCopies[k]->trackList << endl;
                        outlogfile << "TrackList: " << *RoboMoveCopies[k]->trackList << endl;
                    }
                    else
                    {
                        cout << "TrackList: None" << endl;
                        outlogfile << "TrackList: None" << endl;
                    }
                }

                if (RoboMoveCopies[k]->ScoutBot())
                {
                    cout << "Robot " << RoboMoveCopies[k]->GetSignia() << " sees:";
                    outlogfile << "Robot " << RoboMoveCopies[k]->GetSignia() << " sees:";

                    for (int x = 0; x < RoboMoveCopies.size(); x++)
                    {
                        if (RoboMoveCopies[x] == nullptr) continue;
                        if (x == k) continue;
                        if (RoboMoveCopies[x]->current_row == nullptr || RoboMoveCopies[x]->current_col == nullptr) continue;
                                                                                                                            
                        cout << " Robot " << RoboMoveCopies[x]->GetSignia() << " at (" << *RoboMoveCopies[x]->current_row << ", " << *RoboMoveCopies[x]->current_col << ")";
                        cout << ",";
                        outlogfile << " Robot " << RoboMoveCopies[x]->GetSignia() << " at (" << *RoboMoveCopies[x]->current_row << ", " 
                        << *RoboMoveCopies[x]->current_col << ")" << ",";
                    }
                    cout << endl;
                    outlogfile << endl;
                }
                cout << endl;
                outlogfile << endl;

            }

            // Check if only one robot is left in the battlefield
            if (Endgame == (numberOfRobots + ExtraBot - 1))
            {
                if (RoboMoveCopies[i] != nullptr)
                {
                    Winner = RoboMoveCopies[i]->GetSignia();
                    break;
                }
            }
            // Check if the last two robots in the battlefield dies at the same time
            if (Endgame == numberOfRobots + ExtraBot)
            {
                break;
            }

            cout << "Dead Robots: " << Endgame << endl;
            outlogfile << "Dead Robots: " << Endgame << endl;

            battlefield.delay(500); // Program runtime
        }
        
        //Get 3 new alien robots ---------------------------------------------------------------
        int Gacha = rand() % 3;
        int oneSpawn = 0;
        if (!Spawning)
        {
            if (Gacha == 0 && ExtraBot != 3 && oneSpawn == 0)
            {
                cout << "!!A new AI bot has randomly spawned!!" << endl;
                outlogfile << "!!A new AI bot has randomly spawned!!" << endl;
                ShootingRobot* extraBot = new ShootingRobot(row, col);
                string sig = "$&@";
                extraBot->SetSignia(sig[ExtraBot]);
                extraBot->GetShells(10);
                extraBot->NewSpawn(battlefield.Grid);
                RoboMoveCopies.push_back(extraBot);
                ExtraBot += 1;
                oneSpawn += 1;
            }
        }
        // ---------------------------------------------------------------------------------------

        // Removing robots from queue and into the battlefield again ------------------------------------
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
                    outlogfile << "Robot " << WaitingBot->GetSignia() << " is removed from queue.\n";
                    WaitingBot->NullifyQueue();
                    WaitingBot->ResetUpgrades(); // Resets the robot upgrade variables for a clean slate
                    WaitingBot->GetShells(10);
                    WaitingBot->NewSpawn(battlefield.Grid);
                    RoboMoveCopies.push_back(WaitingBot);
                    battlefield.delay(1000);
                }
                turn += 1;
            }
            Spawnbot = 0;
        }
        else
        {
            Spawnbot += 1;
        }
        // ----------------------------------------------------------------------------------------------


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

    // Printing for the winner of the program
    if (!Winner.empty())
    {
        cout << endl << "!!ROBOT " << Winner << " IS THE WINNER!!" << endl; 
        outlogfile << endl << "!!ROBOT " << Winner << " IS THE WINNER!!" << endl; 
    }
    else
    {
        cout << endl << "Match ends with no winner" << endl; 
        outlogfile << endl << "Match ends with no winner" << endl; 
    }

    return 0;
    
}