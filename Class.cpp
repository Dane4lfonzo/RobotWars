#include "Class.h"

/*************************Battlefield***************************************/
Battlefield::Battlefield(int row, int col)
{
    *MaxRow = row;
    *MaxCol = col;
}

Battlefield::Battlefield(const Battlefield& obj)
{
    MaxRow = new int(*obj.MaxRow);
    MaxCol = new int(*obj.MaxCol);
    Grid = obj.Grid; // deep copy via vector copy
    //utk robot tu tau which vector //utk specify
}

Battlefield::~Battlefield()
{
    delete MaxRow;
    delete MaxCol;
}

void Battlefield::GridMaker()
{
    Grid.resize(*MaxRow);

    for (int i=0; i < *MaxRow; i++)
    {
        Grid[i].resize(*MaxCol, ".");
    }
}

void Battlefield::GridReset()//utk hilangkan after images
{
    for (int i=0; i < *MaxRow; i++)
    {
        for (int j=0; j < *MaxCol; j++)
        {
            Grid[i][j] = ".";
        }
    }
}

void Battlefield::printGrid()
{
    string Name = "Battlefield";
    cout << setw((*MaxCol / 2 + Name.size())-4) << Name << endl;

    for (int x=0; x < *MaxCol+4; x++)
    {
        cout << "#";
    }

    cout << endl;

    cout << "#" << setw(*MaxCol+3) << "#" << endl; 

    for (int i=0; i < *MaxRow; i++)
    {
        cout << "#";
        cout << " ";
        for (int j=0; j < *MaxCol; j++)
        {
            cout << Grid[i][j];
        }
        cout << " ";
        cout << "#";
        
        cout << endl;
    }

    cout << "#" << setw(*MaxCol+3) << "#" << endl;

    for (int x=0; x < *MaxCol+4; x++)
    {
        cout << "#";
    }
    cout << endl;    
}

void Battlefield::SetStep(int numofsteps)
{
    CountNumSteps = numofsteps;
}

bool Battlefield::StepCount()
{
    if (CountNumSteps > 0)
        return true;
    else
        return false;
}

void Battlefield::CountDownStep()
{
    CountNumSteps -= 1;
    cout << "Remaining Steps: " << CountNumSteps << "\n\n";
}

void Battlefield::delay(int milliseconds) 
{
    // Simple delay using a loop 
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds * CLOCKS_PER_SEC / 1000);
}

/********************************** UpgradeRobot **************************************/
UpgradeRobot::UpgradeRobot()
{
    RobotUpgraded = new bool(false);

    movingUpgradeUse_Jump = new bool(false);
    movingUpgradeUse_Hide = new bool(false);

    shootingUpgradeUse_LongShot = new bool(false);
    shootingUpgradeUse_SemiAuto = new bool(false);
    shootingUpgradeUse_ThirtyShot = new bool(false);

    seeingUpgradeUse_Scout = new bool(false);
    seeingUpgradeUse_Track = new bool(false); 

    movingUpgradeChosen = new string();
    shootingUpgradeChosen = new string();
    seeingUpgradeChosen = new string();

    hideUsage = new int(3);

    jumpUsage = new int(3);

    scoutUsage = new int(3);
    trackUsage = new int(3);

    trackList = new string();
    addtrackList = new bool(false);

}

UpgradeRobot::UpgradeRobot(const UpgradeRobot& obj)
{
    RobotUpgraded = new bool(*obj.RobotUpgraded);

    movingUpgradeUse_Jump = new bool(*obj.movingUpgradeUse_Jump);
    movingUpgradeUse_Hide = new bool(*obj.movingUpgradeUse_Hide);

    shootingUpgradeUse_LongShot = new bool(*obj.shootingUpgradeUse_LongShot);
    shootingUpgradeUse_SemiAuto = new bool(*obj.shootingUpgradeUse_SemiAuto);
    shootingUpgradeUse_ThirtyShot = new bool(*obj.shootingUpgradeUse_ThirtyShot);

    seeingUpgradeUse_Scout = new bool(*obj.seeingUpgradeUse_Scout);
    seeingUpgradeUse_Track = new bool(*obj.seeingUpgradeUse_Track);

    movingUpgradeChosen = new string(*obj.movingUpgradeChosen);
    shootingUpgradeChosen = new string(*obj.shootingUpgradeChosen);
    seeingUpgradeChosen = new string(*obj.seeingUpgradeChosen);

    trackList = new string(*obj.trackList);

    hideUsage = new int(*obj.hideUsage);

    jumpUsage = new int(*obj.jumpUsage);

    scoutUsage = new int(*obj.scoutUsage);

    trackUsage = new int(*obj.trackUsage);
    addtrackList = new bool(*obj.addtrackList);
}

UpgradeRobot::~UpgradeRobot()
{
    delete RobotUpgraded;

    delete hideUsage;
    delete jumpUsage;

    delete scoutUsage;
    delete trackUsage;

    delete movingUpgradeUse_Jump;
    delete movingUpgradeUse_Hide;

    delete shootingUpgradeUse_LongShot;
    delete shootingUpgradeUse_SemiAuto;
    delete shootingUpgradeUse_ThirtyShot;

    delete seeingUpgradeUse_Scout;
    delete seeingUpgradeUse_Track;

    delete movingUpgradeChosen;
    delete shootingUpgradeChosen;
    delete seeingUpgradeChosen;

    delete trackList;
    delete addtrackList;
}

bool UpgradeRobot::HideBot()
{
    return *movingUpgradeUse_Hide;
}

bool UpgradeRobot::JumpBot()
{
    return *movingUpgradeUse_Jump;
}

bool UpgradeRobot::LongShotBot()
{
    return *shootingUpgradeUse_LongShot;
}

bool UpgradeRobot::SemiAutoBot()
{
    return *shootingUpgradeUse_SemiAuto;
}

bool UpgradeRobot::ScoutBot()
{
    return *seeingUpgradeUse_Scout;
}

bool UpgradeRobot::TrackBot()
{
    return *seeingUpgradeUse_Track;
    //return true;
}

/**********************************MovingRobot**************************************/
MovingRobot::MovingRobot(int row, int col) : Battlefield(row, col), UpgradeRobot()
{   
    current_row = new int(0);
    current_col = new int(0);

    //*current_row = rand() % row;
    //*current_col = rand() % col;

}

void MovingRobot::SetCurrentPos(vector<string> check_spawn_condition, int& iterationval)
{
    if (check_spawn_condition[iterationval] != "random")
    {
        *current_row = stoi(check_spawn_condition[iterationval]);
    }

    else if (check_spawn_condition[iterationval] == "random")
    {
        *current_row = rand() % *MaxRow;
    }

    iterationval += 1;

    if (check_spawn_condition[iterationval] != "random")
    {
        *current_col = stoi(check_spawn_condition[iterationval]);
    }

    else if (check_spawn_condition[iterationval] == "random")
    {
        *current_col = rand() % *MaxCol;
    }

    iterationval += 1;

}

MovingRobot::MovingRobot(const MovingRobot& obj) : Battlefield(obj), UpgradeRobot(obj) //ni utk robot lain
{
    current_row = new int (*obj.current_row); // to create new memory for next loc
    current_col = new int (*obj.current_col);

    movingchoice = new int (*obj.movingchoice);
    move_row = new int (*obj.move_row);
    move_col = new int (*obj.move_col);

}


MovingRobot::~MovingRobot()
{
    delete movingchoice;
    delete move_row;
    delete move_col;
    delete current_row;
    delete current_col;
    delete signia;
}

void MovingRobot::SetSignia(char character)
{
    *signia = character;
}

string MovingRobot::GetSignia()
{
    return (*signia);
}

void MovingRobot::WheretoMove()
{
    *movingchoice = rand() % 8;

    
    int array_rowchoice[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
    int array_colchoice[8] = {-1, -1, -1, 0, 1, 1, 1, 0};

    *move_row = array_rowchoice[*movingchoice];
    *move_col = array_colchoice[*movingchoice];

}

void MovingRobot::PlaceRobot(vector<vector<string>>& sharedGrid)
{
    sharedGrid[*current_row][*current_col] = *signia;
}

void MovingRobot::MovetoSquare(vector<vector<string>>& sharedGrid) 
{
    sharedGrid[*current_row][*current_col] = "."; //utk replace afterimage // to replace the previous position to '.'

    int new_row = *current_row + *move_row;
    int new_col = *current_col + *move_col;

    int rand_row = rand() % *MaxRow;
    int rand_col = rand() % *MaxCol;

    bool validpos = false;

    while (!validpos)
    {
        if (!JumpBot()) //!JumpBot()
        {
            if ((new_row >= 0 && new_row < *MaxRow) && (new_col >= 0 && new_col < *MaxCol) && sharedGrid[new_row][new_col] == ".")
            {
                *current_row = new_row;
                *current_col = new_col;

                sharedGrid[*current_row][*current_col] = *signia;
                validpos = true;
            }

            else 
            {
                WheretoMove();
                new_row = *current_row + *move_row;
                new_col = *current_col + *move_col;        
                validpos = false;
            }
        }

        if(JumpBot())
        {
            if (sharedGrid[rand_row][rand_col] == ".")
            {
                *current_row = rand_row;
                *current_col = rand_col;

                sharedGrid[*current_row][*current_col] = *signia;
                validpos = true;
            }

            else 
            {
                rand_row = rand() % *MaxRow;
                rand_col = rand() % *MaxCol;      
                validpos = false;
            } 
        }
    }


}

/**********************************SeeingRobot**************************************/

SeeingRobot::SeeingRobot(int row, int col): MovingRobot(row, col)
{
    checkrow = new int;
    checkcol = new int;

    *detection = false;
}

SeeingRobot::SeeingRobot(const SeeingRobot& obj): MovingRobot(obj)
{
    checkrow = new int(*obj.checkrow); //checkrow tkde asterisk sbb kita nk pass address of obj.checkrow
    // letak content of obj.checkrow into the memory allocation(address) of checkrow
    checkcol = new int(*obj.checkcol);
    detection = new bool(*obj.detection);
}

SeeingRobot::~SeeingRobot()
{
    delete checkrow;
    delete checkcol;
    delete detection;
    
}

void SeeingRobot::Look(int Robo_current_row, int Robo_current_col)
{
    *detection = false;
    *checkrow = Robo_current_row;
    *checkcol = Robo_current_col;

    if (!LongShotBot())
    {
        for (int i = 0; i < 8; i++)
        {
            if ((*checkrow == *current_row + arraychoice[0][i]) && (*checkcol == *current_col + arraychoice[1][i]))
            {
                cout << "Detection true at (" << *checkrow << "," << *checkcol << ")" << endl;
                *detection = true;
                break;
            }
        }
    }

    if (LongShotBot())
    {
        for (int j = 0; j < 24; j++)
        {
            if ((*checkrow == *current_row + upgraded_arraychoice[0][j]) && (*checkcol == *current_col + upgraded_arraychoice[1][j]))
            {
                cout << "Detection true at (" << *checkrow << "," << *checkcol << ")" << endl;
                *detection = true;
                break;
            }
        }
    }

}

bool SeeingRobot::RobotDetect()
{
    return *detection;
}
 

/**********************************ThinkingRobot**************************************/
ThinkingRobot::ThinkingRobot(int row, int col) : SeeingRobot(row,col)
{
    shootFlag = new bool(false);

    movingUpgrade = new bool(false);
    shootingUpgrade = new bool(false);
    seeingUpgrade = new bool(false);

    movingUpgradeDone = new bool(false);
    shootingUpgradeDone = new bool(false);
    seeingUpgradeDone = new bool(false);

}

ThinkingRobot::ThinkingRobot(const ThinkingRobot& obj) : SeeingRobot(obj)
{
    shootFlag = new bool(*obj.shootFlag); // copy content of shootFlag into address of shootFlag

    movingUpgrade = new bool(*obj.movingUpgrade);
    shootingUpgrade = new bool(*obj.shootingUpgrade);
    seeingUpgrade = new bool(*obj.seeingUpgrade);

    movingUpgradeDone = new bool(*obj.movingUpgradeDone);
    shootingUpgradeDone = new bool(*obj.shootingUpgradeDone);
    seeingUpgradeDone = new bool(*obj.seeingUpgradeDone);
}

void ThinkingRobot::ShootheRobot()
{
    if(*detection == true)
    {
        *shootFlag = true;
    }

}

ThinkingRobot::~ThinkingRobot()
{
    delete shootFlag;
    delete movingUpgrade;
    delete shootingUpgrade;
    delete seeingUpgrade;
    delete movingUpgradeDone;
    delete shootingUpgradeDone;
    delete seeingUpgradeDone;

}

void ThinkingRobot::Think()
{
    cout << "Robot "<< signia <<" is thinking" << endl;

    if(*detection == true)
    {
        *shootFlag = true;
    }
    else
    {
        *shootFlag = false;
    }

}

void ThinkingRobot::Upgrade()
{
    
    string movingUpgradeChoice[2] = {"HideBot", "JumpBot"};
    string shootingUpgradeChoice[3] = {"LongShotBot", "SemiAutoBot", "ThirtyShotBot"}; //////////////////////////////////////////////////
    string seeingUpgradeChoice[2] = {"ScoutBot", "TrackBot"};



    vector<int> areasAvailable{};

    // if tkde movingUpgrade, letak dlm vector supaya bole pilih japgi
    // if(*movingUpgrade == false)
    // {
    //     areasAvailable.push_back(0);
    // }
    
    // if(*shootingUpgrade == false)
    // {
    //     areasAvailable.push_back(1);
    // }

    if(*seeingUpgrade == false)
    {
        areasAvailable.push_back(2);
    }

    // if robot tu tkde any upgrades vector tu camni
    // areasAvailable{0,1,2}

    int choice = areasAvailable[rand() % areasAvailable.size()]; // utk randomly choose

    int rand_move = rand() % 2;
    int rand_shoot = rand() % 3;
    int rand_see = rand() % 2;

    *movingUpgradeChosen = movingUpgradeChoice[rand_move];
    //*shootingUpgradeChosen = shootingUpgradeChoice[rand_shoot];
    //*shootingUpgradeChosen = "SemiAutoBot";
    //*seeingUpgradeChosen = seeingUpgradeChoice[rand_see];
    //*seeingUpgradeChosen = "ScoutBot";
    *seeingUpgradeChosen = "TrackBot";
    
    

    switch(choice)
    {
        case 0:
            *movingUpgrade = true;
            cout << "Robot " << *signia << " has upgraded in Moving Upgrade: " << *movingUpgradeChosen << endl;
            areasAvailable.clear(); // utk clear for next upgrade so this upgrade tkde dlm vector areasAvailable
            break;
        case 1:
            *shootingUpgrade = true;
            cout << "Robot " << *signia << " has upgraded in Shooting Upgrade: " << *shootingUpgradeChosen << endl;
            areasAvailable.clear();
            break;
        case 2:
            *seeingUpgrade = true;
            cout << "Robot " << *signia << " has upgraded in Seeing Upgrade: " << *seeingUpgradeChosen << endl;
            areasAvailable.clear();
            break;
    }

    if (movingUpgradeChoice[rand_move] == "HideBot" && !*movingUpgradeDone && *movingUpgrade)
    {
        *movingUpgradeUse_Hide = true;
        *movingUpgradeDone = true;

    }

    if (movingUpgradeChoice[rand_move] == "JumpBot" && !*movingUpgradeDone && *movingUpgrade)
    {
        *movingUpgradeUse_Jump = true;
        *movingUpgradeDone = true;
    }

    if (*shootingUpgradeChosen == "LongShotBot" && !*shootingUpgradeDone && *shootingUpgrade)
    {
        *shootingUpgradeUse_LongShot = true;
        *shootingUpgradeDone = true;
    }

    if(*shootingUpgradeChosen == "SemiAutoBot" && !*shootingUpgradeDone && *shootingUpgrade)
    {
        *shootingUpgradeUse_SemiAuto = true;
        *shootingUpgradeDone = true;
    }

    if (*seeingUpgradeChosen == "ScoutBot" && !*seeingUpgradeDone && *seeingUpgrade)
    {
        *seeingUpgradeUse_Scout = true;
        *seeingUpgradeDone = true;
    }

    if (*seeingUpgradeChosen == "TrackBot" && !*seeingUpgradeDone && *seeingUpgrade)
    {
        *seeingUpgradeUse_Track = true;
        *seeingUpgradeDone = true;
    }


}

void ThinkingRobot::UpdateUsage()
{
    if (HideBot())
    {
        *hideUsage -= 1;
        //cout << "\n\n\nHideCount: " << *hideUsage << endl;
        if (*hideUsage <= 0)
        {
            *movingUpgradeUse_Hide = false;
            
        }
    } 

    if (JumpBot())
    {
        *jumpUsage -= 1;
        //cout << "\n\n\nJumpCount: " << *jumpUsage << endl;
        if (*jumpUsage <= 0)
        {
            *movingUpgradeUse_Jump = false;
            
        }
    }

    if (ScoutBot())
    {
        *scoutUsage -= 1;
        
        if (*scoutUsage <= 0)
        {
            *seeingUpgradeUse_Scout = false;
        }
    }

    if (TrackBot())
    {
        if (*trackUsage <= 0)
        {
            *seeingUpgradeUse_Track = false;
        }
    }

}
/**********************************ShootingRobot**************************************/

ShootingRobot::ShootingRobot(int row, int col): ThinkingRobot(row, col)
{
    shootChances = new int;
    shooting = new bool(false);
}

ShootingRobot::ShootingRobot(const ShootingRobot& obj) : ThinkingRobot(obj)
{
    shootChances = new int(*obj.shootChances);
    shooting = new bool(*obj.shooting);
}

ShootingRobot::~ShootingRobot()
{
    delete shootChances;
    delete shooting;
}

void ShootingRobot::CheckShot(string Robotname, int numberofRobots)
{
    *shooting = false;

    if (*shootFlag && !SemiAutoBot())
    {
        *shootChances = (rand() % 10) + 1;

        if (*shootChances <= 0)//7
        {
            *shooting = true;
            cout << "Shots fired successfully" << endl;
            
        }
        else
        {
            cout << "Shots missed" << endl;
            *addtrackList = true;
            // if (TrackBot())
            // {
            //     *addtrackList = true;
            // }
            
        }
    *detection = false;
    *shootFlag = false;
    }

    if (*shootFlag && SemiAutoBot())
    {
        for (int i = 0; i < 3; i++)
        {
            *shootChances = (rand() % 10) + 1;

            if (*shootChances <= 7)
            {
                *shooting = true;
                cout << "Shots fired successfully" << endl;
                break;
            }
            else
            {
                cout << "Shots missed" << endl;
                *addtrackList = true;
            }
        }
        *detection = false;
        *shootFlag = false;
    }
    
    if (TrackBot() && *addtrackList)
    {
        // if ((*trackList).length() == 0)
        // {
        //     *trackList += Robotname;
        // }
        // else
        //{
            for (int x = 0; x < (*trackList).length(); x++)
            {
                if ((*trackList)[x] == Robotname[0])
                {
                    *addtrackList = false;
                    break;
                }
            }     
        //}

        if (*addtrackList)
        {
            *trackList += Robotname;
            cout << "Work Track" << endl;
            *trackUsage -= 1;
            *addtrackList = false;
        }

         
        // *trackList += Robotname;
        // cout << "\n\n\n\n\nWork Track" << endl;

        
    }
}

bool ShootingRobot::GetShooting()
{return *shooting;}


void filereading(ifstream& infile, ofstream& outfile, int& numrows, int& numcols, int& numofsteps, int& numberofRobots, string& RoboNames, vector<string>& check_spawn_condition)
{
    string line;
    int iterationval = 0;
    
    // int numrows, numcols, numofsteps, numberofRobots;
    // string RoboNames;

    while (getline(infile,line))
    {

    // to find numrows by numcols

      if(line.find("numrows by numcols") != string::npos && line.find(":") != string::npos) // check if the line contains "numrows by numcols" and ":"
        {
            //outfile << ">numrows by numcols fileOutput.txt;" << endl;
            //cout << ">numrows by numcols fileOutput.txt;" << endl;

            int start = line.find(":"); // find the position of the colon - remove everything till ":"
            string numrowsCol = line.substr(start + 2); // takes " row by col" // "5 by 10"
        
            int spacePos = numrowsCol.find(" "); // finding position of the space

            string rowStr = numrowsCol.substr(0, spacePos); // ambil the row part
            string colStr = numrowsCol.substr(spacePos + 1); // ambil the col part

            if (rowStr != "random")
            {
                numrows = stoi(rowStr); // change string to integer
            }
            
            if (colStr != "random")
            {
                numcols = stoi(colStr); // change string to integer
            }
            
            if (rowStr == "random")
            {

            }
            outfile << "Row: " << numrows << endl;
            outfile << "Col: " << numcols << endl;

            //cout << "Row: " << numrows << endl;
            //cout << "Col: " << numcols << endl;

        }

        // to find numofsteps

        if (line.find("numofsteps") != string::npos && line.find(":") != string::npos) // check if the line contains "numofsteps" and ":"
        {
            //outfile << ">numofsteps fileOutput.txt;" << endl;
            //cout << ">numofsteps fileOutput.txt;" << endl;

            int start = line.find(":"); // find the position of the colon - remove everything till ":"
            string numofStepsStr = line.substr(start + 2); // takes "1000" steps 

            numofsteps = stoi(numofStepsStr); // changes string to integer

            outfile << "Number of Steps: " << numofsteps << endl;
            //cout << "Number of Steps: " << numofsteps << endl;
        }

        // to find number of robots

        if (line.find("numberofRobots") != string::npos && line.find(":")!= string::npos) // check if the line contains "numberofRobots" and ":"
        {
            //outfile << ">numofRobots fileOutput.txt;" << endl;
            //cout << ">numofRobots fileOutput.txt;" << endl;

            int start = line.find(":"); // find the position of the colon - remove everything till ":"
            string numofRobotsStr = line.substr(start + 2); // takes "6" / total robots stated

            numberofRobots = stoi(numofRobotsStr); // changes string to integer

            outfile << "Number of Robots:" << numberofRobots << endl;
            //cout << "Number of Robots: " << numberofRobots << endl;
        }

        // to find robots and positions

        if (line.find("GenericRobot") != string::npos) // check if the line contains "GenericRobot"
        {
            //outfile << ">GenericRobot fileOutput.txt;" << endl;
            //cout << ">GenericRobot fileOutput.txt;" << endl;

            int spaceone = line.find(" "); // find the position of the first space
            int spacetwo = line.find(" ", spaceone + 1); // find the position of the second space // after the first space
            int spacethree = line.find(" ", spacetwo + 1); // find the position of the third space // after the second space
            
            string robotName = line.substr(spaceone + 1, spacetwo - spaceone - 1); // remove robot name
            string rowStr = line.substr(spacetwo + 1, spacethree - spacetwo - 1); // remove row number
            string colStr = line.substr(spacethree + 1); // remove column number

            outfile << "Robot Name: " << robotName;
            //cout << "Robot Name: " << robotName;

            check_spawn_condition.push_back(rowStr);
    
            check_spawn_condition.push_back(colStr);

            outfile << " Row: " << check_spawn_condition[iterationval*2];
            outfile << " Col: " << check_spawn_condition[iterationval*2 +1] << endl;
            // cout << " Row: " << check_spawn_condition[iterationval*2];
            // cout << " Col: " << check_spawn_condition[iterationval*2 +1] << endl;
            
            RoboNames += robotName;
            iterationval += 1;
                       
        }
    }


infile.close();
outfile.close();
}