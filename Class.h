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
        void movement(int posx, int posy);
};


