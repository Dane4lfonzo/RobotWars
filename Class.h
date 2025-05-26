#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>

using namespace std;

class Battlefield
{
    protected:
        int* MaxRow = new int(0);
        int* MaxCol = new int(0);
        int CountNumSteps = 0;

    public:
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
        int ammo = 30;
        
    
    public:
        Robot(){}
        virtual void show() = 0;
        virtual ~Robot() {}

};


class MovingRobot : public Robot, public Battlefield, public UpgradeRobot
{
    protected:
        
        int *movingchoice = new int(0);
        int *move_row = new int(0);
        int *move_col = new int(0);
            
        string* signia = new string();;

    public:
        int *current_row;
        int *current_col;
        void show() override{}
        MovingRobot(){}
        MovingRobot(int row, int col);
        MovingRobot(const MovingRobot& obj);
        ~MovingRobot();
        string GetSignia();
        void WheretoMove();
        void SetSignia(char character);
        void MovetoSquare(vector<vector<string>>& sharedGrid);
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


    public:
        bool *shootFlag = new bool(false);
        ThinkingRobot(){};
        ThinkingRobot(int row, int col); // ni robot first
        void ShootheRobot();
        ThinkingRobot(const ThinkingRobot& obj); // ni robot copied
        ~ThinkingRobot();
        void Think();
        void Upgrade();


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
        void CheckShot();
        bool GetShooting();
        
};

class UpgradeRobot
{
    protected:
    bool *RobotHidden = new bool(false);
    int *hideUsage = new int(3);
    bool *RobotJump = new bool(false);
    int *jumpUsage = new int(3);

    public:
    UpgradeRobot(){};
    UpgradeRobot(const UpgradeRobot& obj){};
    bool HideBot();
    bool JumpBot();
    void LongShotBot();
    void SemiAutoBot();
    void ThirtyShotBot();
    void ScoutBot();


};
