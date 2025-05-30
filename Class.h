#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>
#include <queue>
#include <set>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Battlefield class to create the grid
class Battlefield
{
    protected:
        int* MaxRow = new int(0);
        int* MaxCol = new int(0);
        

    public:
        int CountNumSteps = 0;
        vector<vector<string>> Grid;
        Battlefield(){};
        Battlefield(int row, int col);
        Battlefield(const Battlefield& obj);
        ~Battlefield();
        void SetStep(int numofsteps);
        bool StepCount();
        void CountDownStep();
        void GridMaker();
        void GridReset();
        void delay(int miliseconds);
        void printGrid(); //gonna use this in a looped iteration to update display
};


// Base abstract class that is inheritted
class Robot
{
    protected:
        int arraychoice[2][8] = {
            {-1, 0, 1, 1, 1, 0, -1, -1},
            {-1, -1, -1, 0, 1, 1, 1, 0}
        };
        int *shells;
        bool *explosion;
        int *lives;
        bool *inQueue;


        int upgraded_arraychoice[2][24] = {
            {-1, 0, 1, 1, 1, 0, -1, -1, -1, 0, 1, 2, 2, 2, 1, 0, -1, -2, -2, -2, 0, 3, 0, -3},
            {-1, -1, -1, 0, 1, 1, 1, 0, -2, -2, -2, -1, 0, 1, 2, 2, 2, 1, 0, -1, -3, 0, 3, 0}
        };
        
    
    public:
        Robot(){}
        virtual void stats() = 0;
        virtual ~Robot() {}

};

// Class to upgrade robots
class UpgradeRobot
{
    protected:

        bool *movingUpgradeUse_Jump;
        bool *movingUpgradeUse_Hide;

        bool *shootingUpgradeUse_LongShot;
        bool *shootingUpgradeUse_SemiAuto;
        bool *shootingUpgradeUse_ThirtyShot;

        bool *seeingUpgradeUse_Scout;
        bool *seeingUpgradeUse_Track;

        string *movingUpgradeChosen;
        string *shootingUpgradeChosen;
        string *seeingUpgradeChosen;

        int *hideUsage;

        int *jumpUsage;

        int *scoutUsage;

        int *trackUsage;
        

    public:
        bool *printtrackList;
        bool *RobotUpgraded;// For shooting: when it upgrades, it cant upgrade anymore until respawn
        string *trackList;
        bool *addtrackList;
        UpgradeRobot();
        UpgradeRobot(const UpgradeRobot& obj);
        ~UpgradeRobot();
        bool HideBot();
        bool JumpBot();
        bool LongShotBot();
        bool SemiAutoBot();
        bool ThirtyShotBot();
        bool ScoutBot();
        bool TrackBot();
        void ResetBot();


};

// Class for all robot's movement and spawn places
class MovingRobot : public Robot, public Battlefield, public UpgradeRobot
{
    protected:
        int *movingchoice = new int(0);
        int *move_row = new int(0);
        int *move_col = new int(0);
        string* signia = new string();


    public:
        int *current_row;
        int *current_col;
        void stats() override
        {
            shells = new int;
            lives = new int(3);
            explosion = new bool(false);
            inQueue = new bool(false);

        }
        MovingRobot(){}
        MovingRobot(int row, int col);
        MovingRobot(const MovingRobot& obj);
        ~MovingRobot();
        string GetSignia();
        void GetShells(int bullets);
        void SetCurrentPos(vector<string> check_spawn_condition, int& iterationval);
        void WheretoMove();
        void PlaceRobot(vector<vector<string>>& sharedGrid);
        void SetSignia(char character);
        void MovetoSquare(vector<vector<string>>& sharedGrid);
        void NewSpawn(vector<vector<string>>& sharedGrid);
};

// Class for Robot to detect other robots
class SeeingRobot: public MovingRobot
{
    protected:
        int *checkrow;
        int *checkcol;
        bool *detection = new bool;

    public:
        SeeingRobot(){}
        SeeingRobot(int row, int col);
        SeeingRobot(const SeeingRobot& obj);
        ~SeeingRobot();
        void Look(int row, int col);
        bool RobotDetect();
    
};

class ThinkingRobot: public SeeingRobot
{ 
    protected:
        bool *movingUpgrade;
        bool *shootingUpgrade;
        bool *seeingUpgrade;

        bool *movingUpgradeDone;
        bool *shootingUpgradeDone;
        bool *seeingUpgradeDone;


    public:
        bool *shootFlag = new bool(false);
        ThinkingRobot(){};
        ThinkingRobot(int row, int col); 
        ThinkingRobot(const ThinkingRobot& obj); 
        void ShootheRobot();
        void UpdateUsage();
        ~ThinkingRobot();
        void Think();
        void Upgrade();
        bool CheckExplosion();
        bool CheckQueue();
        bool SetQueue();
        bool NullifyQueue();
        int CheckLives();
        int DeductLives();
};

// Class for robot to shoot and kill other robots
class ShootingRobot : public ThinkingRobot
{
    protected:
        int *shootChances;
        bool *shooting;


    public:
        ShootingRobot(){}
        ShootingRobot(int row, int col);
        ShootingRobot(const ShootingRobot& obj);
        ~ShootingRobot();
        void CheckShot(string Robotname, int numberofRobots);
        bool GetShooting();
        int Checkshells();
        
};

// Function to read file
void filereading(ifstream&, ofstream&, int&, int&, int&, int&, string&, vector<string>&);
