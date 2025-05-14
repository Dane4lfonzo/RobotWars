#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>

using namespace std;

class Battlefield
{
    protected:
        int MaxRow;
        int MaxCol;
        vector<vector<string>> Grid;


    public:
        void GridMaker(int row, int col);
        void GridReset();
        void delay(int miliseconds);
        void printGrid(); //gonna use this in a looped iteration to update display
};


class Robot : public Battlefield
{
    protected:
        string signia;
        int life;
};


class MovingRobot : public Robot
{
    protected:
        int current_row;
        int current_col;
        int movingchoice;
        int move_row;
        int move_col;

    public:
        MovingRobot(int x, int y);
        void WheretoMove();
        void MovetoSquare();
        //void MovetoSquare(int move_posx, int move_posy);

};




