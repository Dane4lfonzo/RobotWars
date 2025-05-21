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

void Battlefield::GridReset()
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

    *current_row = rand() % row;
    *current_col = rand() % col;
}

MovingRobot::MovingRobot(const MovingRobot& obj) : Battlefield(obj)
{
    current_row = new int (*obj.current_row);
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
    sharedGrid[*current_row][*current_col] = ".";

    int new_row = *current_row + *move_row;
    int new_col = *current_col + *move_col;

    if (new_row >= 0 && new_row < *MaxRow)
    {
        *current_row = new_row;
    }

    if (new_col >= 0 && new_col < *MaxCol)
    {
        *current_col = new_col;
    }

    sharedGrid[*current_row][*current_col] = *signia;
    //cout << "\n\n\ncurrent_row = " << *current_row << endl;
    //cout << "\n\n\ncurrent_col = " << *current_col << endl;
}

/**********************************SeeingRobot**************************************/

SeeingRobot::SeeingRobot(int row, int col): MovingRobot(row, col)
{
    checkrow = new int;
    checkcol = new int;

    *detection = false;
    *robotLook = false;
}

SeeingRobot::SeeingRobot(const SeeingRobot& obj): MovingRobot(obj)
{
    checkrow = new int(*obj.checkrow);
    checkcol = new int(*obj.checkrow);

    detection = new bool(*obj.detection);
    robotLook = new bool(*obj.robotLook);
}

SeeingRobot::~SeeingRobot()
{
    
}

void SeeingRobot::Look(int row, int col)
{
    *checkrow = row;
    *checkcol = col;
    
    for (int i = 0; i < 8; i++)
    {
        if ((*checkrow == *current_row + arraychoice[0][i]) && (*checkcol == *current_col + arraychoice[1][i]))
        {
            cout << "Detection true" << endl;
        }
    }

}

bool SeeingRobot::RobotDetect()
{
    return *detection;
}