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
        void delay(int miliseconds);
        void printGrid(); //gonna use this in a looped iteration to update display
};

class MovingRobot
{
    protected:
        int movingchoice;
        int move_posx;
        int move_posy;

    public:
        void WheretoMove();
        //void MovetoSquare(int move_posx, int move_posy);

};


class Robot : public MovingRobot, public Battlefield
{
    private:
        int current_posx;
        int current_posy;
        string signia;
        int life;

    public:
        Robot(int x, int y);
        void MovetoSquare();
};



