#include <iostream>
#include <vector>

using namespace std;

class Battlefield
{
    private:
        vector<vector<string>> Grid;
        int MaxRow;
        int MaxCol;


    public:
        Battlefield(int row, int col);
        Battlefield(){};
        void printGrid();
};


 class Robot : public Battlefield
{
    private:
        int posx;
        int posy;
        string signia;

    public:
        Robot(int x, int y);
        Robot(){};
        //void movement(int posx, int posy);
};

class thinkingRobot : public Robot
{
    private:

    public:
        thinkingRobot(){};

};


