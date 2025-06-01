/**********|**********|**********|
 Program: Main.cpp / Class.cpp / Class.h 
Course: Data Structures and Algorithms
 Trimester: 2410

 Name: DANIEL ARIF BIN ABD ZAINEE
 ID: 242UC244JU
 Lecture Section: TC3L
 Tutorial Section: T11L
 Email: DANIEL.ARIF.ABD@student.mmu.edu.my
 Phone: 0137469125

 Name: NUR YASMIN BINTI MOHD SABRI
 ID: 242UC244TX
 Lecture Section: TC3L
 Tutorial Section: T11L
 Email: NUR.YASMIN.MOHD@student.mmu.edu.my
 Phone: 0197828428

 Name: MUHAMMAD NUR AIZAD BIN MURTADHA
 ID: 242UC244T5
 Lecture Section: TC3L
 Tutorial Section: T11L
 Email: MUHAMMAD.NUR.AIZAD@student.mmu.edu.my
 Phone: 0195659972

 Name: YUVENDAR A/L MARAN
 ID: 242UC244DJ
 Lecture Section: TC3L
 Tutorial Section: T11L
 Email: YUVENDAR.MARAN@student.mmu.edu.my
 Phone: 0127420244
 **********|**********|**********/
#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>
#include <queue>
#include <set>
#include <fstream>
#include <string>
#include <iomanip>
#include <unordered_set>

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
        // Constructor, copy constructor and destructor-----
        Battlefield(){};
        Battlefield(int row, int col);
        Battlefield(const Battlefield& obj);
        ~Battlefield();
        // --------------------------------------------------
        void SetStep(int numofsteps); // get number of steps
        bool StepCount(); // return boolean
        void CountDownStep(); // remove one step after each round
        void GridMaker(); // to create battlefield grid
        void GridReset(); // reset the grid and remove the afterimages
        void delay(int miliseconds); // to print out the created grid
        void printGrid(); // gonna use this in a looped iteration to update display
};


// Base abstract class that is inherited
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
        // Constructor, copy constructor and destructor-----
        UpgradeRobot();
        UpgradeRobot(const UpgradeRobot& obj);
        ~UpgradeRobot();
        // -------------------------------------------------
        bool *printtrackList;
        bool *RobotUpgraded;// For shooting: when it upgrades, it cant upgrade anymore until respawn
        int *UpgradeLimit;
        string *trackList;
        bool *addtrackList;
        bool HideBot();
        bool JumpBot();
        bool LongShotBot();
        bool SemiAutoBot();
        bool ThirtyShotBot();
        bool ScoutBot();
        bool TrackBot();

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
        // Constructor, copy constructor and destructor-----
        MovingRobot(){}
        MovingRobot(int row, int col);
        MovingRobot(const MovingRobot& obj);
        ~MovingRobot();
        // ------------------------------------------------
        string GetSignia() const;
        void GetShells(int bullets); // return shells
        void SetCurrentPos(vector<string> check_spawn_condition, int& iterationval); // to check "random coordinates" from input file
        void WheretoMove(); // Get random number to determine movement
        void PlaceRobot(vector<vector<string>>& sharedGrid); // for spawning
        void SetSignia(char character); // set robot's signia
        void MovetoSquare(vector<vector<string>>& sharedGrid); // Function for robot to choose its next movement
        void NewSpawn(vector<vector<string>>& sharedGrid); // Get new coordinates for the robot after queue

};

// Class for Robot to detect other robots
class SeeingRobot: public MovingRobot
{
    protected:
        int *checkrow;
        int *checkcol;
        bool *detection = new bool;

    public:
        // Constructor, copy constructor and destructor-----
        SeeingRobot(){}
        SeeingRobot(int row, int col);
        SeeingRobot(const SeeingRobot& obj);
        ~SeeingRobot();
        // -------------------------------------------------
        void Look(int row, int col, string roboname); // Check each coordinates of the robot and compare to the bounds of the current robot
        bool RobotDetect(); // return detection

};

// Class to think and return stats
class ThinkingRobot: public SeeingRobot
{ 
    protected:
        bool *shootFlag = new bool(false);
        bool *movingUpgrade;
        bool *shootingUpgrade;
        bool *seeingUpgrade;

        bool *movingUpgradeDone;
        bool *shootingUpgradeDone;
        bool *seeingUpgradeDone;


    public:
        // Constructor, copy constructor and destructor-----
        ThinkingRobot(){};
        ThinkingRobot(int row, int col); 
        ThinkingRobot(const ThinkingRobot& obj); 
        ~ThinkingRobot();
        // -------------------------------------------------
        void ShootheRobot(); // return shootflag
        void UpdateUsage(); // increase the amount of upgrades used
        void UpdateThirtyShot(); // upgrades for thirtyshotbot
        void PrintUpgrades(); // printing upgrades
        void ResetUpgrades(); // resetting upgrades
        void Upgrade(); // Getting upgrades
        bool CheckExplosion(); // check if robot explode
        bool CheckQueue(); // check if robot in queue
        bool SetQueue(); // return queue true 
        bool NullifyQueue(); // return queue false
        int CheckLives() const; // check robot's lives
        int DeductLives(); // remove 1 life from robot
};

// Class for robot to shoot and kill other robots
class ShootingRobot : public ThinkingRobot
{
    protected:
        int *shootChances;
        bool *shooting;


    public:
        // Constructor, copy constructor and destructor-----
        ShootingRobot(){}
        ShootingRobot(int row, int col);
        ShootingRobot(const ShootingRobot& obj);
        ~ShootingRobot();
        // ------------------------------------------------
        void CheckShot(string Robotname, int numberofRobots); // Robot shooting action
        int Checkshells() const; // check how many shells left
        bool GetShooting(); // return shooting
        friend ostream& operator<<(ostream& os, const ShootingRobot& robot); // overloading operator for printing

};

// Function to read file
void filereading(ifstream&, ofstream&, int&, int&, int&, int&, string&, vector<string>&);