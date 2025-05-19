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
        
    
    public:
        Robot(){}
        virtual void show() = 0;
        virtual ~Robot() {}

};

class MovingRobot : public Robot, public Battlefield
{
    protected:
        int *current_row;
        int *current_col;
        int *movingchoice = new int(0);
        int *move_row = new int(0);
        int *move_col = new int(0);    

        string* signia = new string();

    public:
        MovingRobot(int row, int col);
        MovingRobot(const MovingRobot& obj);
        ~MovingRobot();
        void show() override{}
        void WheretoMove();
        void SetSignia(char character);
        void MovetoSquare(vector<vector<string>>& sharedGrid);
};

