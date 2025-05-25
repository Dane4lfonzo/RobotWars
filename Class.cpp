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
    for (int i=0; i < *MaxRow; i++)
    {
        for (int j=0; j < *MaxCol; j++)
        {
            cout << Grid[i][j];
        }
        cout << endl;
    }
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

/**********************************MovingRobot**************************************/

MovingRobot::MovingRobot(int row, int col) : Battlefield(row, col)
{   
    current_row = new int;
    current_col = new int;

    *current_row = rand() % row; //spawn point furst object (robot first)
    *current_col = rand() % col;
}

MovingRobot::MovingRobot(const MovingRobot& obj) : Battlefield(obj)//ni utk robot lain
{
    current_row = new int (*obj.current_row); // to create new memory for next loc
    current_col = new int (*obj.current_col);

    movingchoice = new int (*obj.movingchoice);
    move_row = new int (*obj.move_row);
    move_col = new int (*obj.move_col);

    *current_row = rand() % *MaxRow; 
    *current_col = rand() % *MaxCol;

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

void MovingRobot::WheretoMove()
{
    
    *movingchoice = rand() % 8;

    
    int array_rowchoice[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
    int array_colchoice[8] = {-1, -1, -1, 0, 1, 1, 1, 0};

    *move_row = array_rowchoice[*movingchoice];
    *move_col = array_colchoice[*movingchoice];

}

void MovingRobot::MovetoSquare(vector<vector<string>>& sharedGrid) 
{
    sharedGrid[*current_row][*current_col] = "."; //utk replace afterimage // to replace the previous position to '.'

    int new_row = *current_row + *move_row;
    int new_col = *current_col + *move_col;

    //Yaro's code
    /*if (new_row >= 0 && new_row < *MaxRow && new_col >= 0 && new_col < *MaxCol) 
    {
        // Check if the target cell is empty
        if (sharedGrid[new_row][new_col] == ".") {
            *current_row = new_row;
            *current_col = new_col;
        }
    }

    sharedGrid[*current_row][*current_col] = *signia;*/

    bool validpos = false;

    while (!validpos)
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
    checkcol = new int(*obj.checkrow);
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

bool SeeingRobot::RobotDetect()
{
    return *detection;
}
 

/**********************************ThinkingRobot**************************************/
ThinkingRobot::ThinkingRobot(int row, int col) : SeeingRobot(row,col)
{
    *shootFlag = false;
    *movingUpgrade = false;
    *shootingUpgrade = false;
    *seeingUpgrade = false;

}

ThinkingRobot::ThinkingRobot(const ThinkingRobot& obj) : SeeingRobot(obj)
{
    shootFlag = new bool(*obj.shootFlag); // copy content of shootFlag into address of shootFlag
    movingUpgrade = new bool(*obj.movingUpgrade);
    shootingUpgrade = new bool(*obj.shootingUpgrade);
    seeingUpgrade = new bool(*obj.seeingUpgrade);
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

}

void ThinkingRobot::Think()
{
    cout << "Robot "<< *signia <<" is thinking" << endl;
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
    vector<string> movingUpgradeChoice = {"HideBot", "JumpBot"};
    vector<string> shootingUpgradeChoice = {"LongShotBot", "SemiAutoBot", "ThirtyShotBot"};
    vector<string> seeingUpgradeChoice = {"ScoutBot", "TrackBot"};

    vector<int> areasAvailable{};

    // if tkde movingUpgrade, letak dlm vector supaya bole pilih japgi
    if(*movingUpgrade == false)
    {
        areasAvailable.push_back(0);
    }

    if(*shootingUpgrade == false)
    {
        areasAvailable.push_back(1);
    }

    if(*seeingUpgrade == false)
    {
        areasAvailable.push_back(2);
    }
    // if robot tu tkde any upgrades vector tu camni
    // areasAvailable{0,1,2}

    int choice = areasAvailable[rand() % areasAvailable.size()]; // utk randomly choose

    switch(choice)
    {
        case 0:
            *movingUpgrade = true;
            cout << "Robot " << *signia << " has upgraded in Moving Upgrade: " << movingUpgradeChoice[rand() % movingUpgradeChoice.size()] << endl;
            areasAvailable.clear(); // utk clear for next upgrade so this upgrade tkde dlm vector areasAvailable
            break;
        case 1:
            *shootingUpgrade = true;
            cout << "Robot " << *signia << " has upgraded in Shooting Upgrade: " << shootingUpgradeChoice[rand() % shootingUpgradeChoice.size()] << endl;
            areasAvailable.clear();
            break;
        case 2:
            *seeingUpgrade = true;
            cout << "Robot " << *signia << " has upgraded in Seeing Upgrade: " << seeingUpgradeChoice[rand() % seeingUpgradeChoice.size()] << endl;
            areasAvailable.clear();
            break;

    }

}
/**********************************HideRobot**************************************/

HideRobot::HideRobot(int row, int col) : ThinkingRobot(row, col)
{

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

void ShootingRobot::CheckShot()
{
    *shooting = false;

    if (*shootFlag)
    {
        *shootChances = (rand() % 10) + 1;

        if (*shootChances <= 7)
        {
            *shooting = true;
            cout << "Shots fired successfully" << endl;
            
        }
        else
        {
            cout << "Shots missed" << endl;
        }
    *detection = false;
    *shootFlag = false;
    }
}

bool ShootingRobot::GetShooting()
{return *shooting;}
   