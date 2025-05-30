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
        void ThirtyShotBot();
        bool ScoutBot();
        bool TrackBot();


};

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
        ThinkingRobot(int row, int col); // ni robot first
        void ShootheRobot();
        void UpdateUsage();
        ThinkingRobot(const ThinkingRobot& obj); // ni robot copied
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


void filereading(ifstream&, ofstream&, int&, int&, int&, int&, string&, vector<string>&);
