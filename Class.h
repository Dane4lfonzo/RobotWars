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
        
    
    public:
        Robot(){}
        virtual void show() = 0;
        virtual ~Robot() {}

};


class MovingRobot : public Robot, public Battlefield
{
    protected:
        
        int *movingchoice = new int(0);
        int *move_row = new int(0);
        int *move_col = new int(0);
            
        string* signia = new string();

    public:
        int *current_row;
        int *current_col;
        void show() override{}
        MovingRobot(){}
        MovingRobot(int row, int col);
        MovingRobot(const MovingRobot& obj);
        ~MovingRobot();
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
    bool *shootFlag;
    bool *movingUpgrade;
    bool *shootingUpgrade;
    bool *seeingUpgrade;


    public:
    ThinkingRobot(){};
    ThinkingRobot(int row, int col); // ni robot first
    ThinkingRobot(const ThinkingRobot& obj); // ni robot copied
    ~ThinkingRobot();

    void Think();
    void Upgrade();
};

class HideRobot : public ThinkingRobot
{
    protected:
    bool *hidden = new bool(false);
    int *hideUsage = new int(3);

    public:
    HideRobot(){};
    HideRobot(int row, int col);
    HideRobot(const HideRobot& obj);


};
