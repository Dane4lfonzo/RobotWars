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
        vector<vector<string>> Grid;


    public:
        Battlefield(int row, int col);
        Battlefield(const Battlefield& obj);
        ~Battlefield();
        void GridMaker();
        void GridReset();
        void delay(int miliseconds);
        void printGrid(); //gonna use this in a looped iteration to update display
};


class Robot
{
    protected:
        
    
    public:

};

class MovingRobot : public Robot, public Battlefield
{
    protected:
        int current_row;
        int current_col;
        int *movingchoice = new int(0);
        int *move_row = new int(0);
        int *move_col = new int(0);

    public:
        MovingRobot(int row, int col);
        MovingRobot(const MovingRobot& obj);
        ~MovingRobot();
        void WheretoMove();
        void MovetoSquare();
};


