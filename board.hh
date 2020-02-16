/* Game15 (or puzzle 15) : Template code
 *
 * Class: Board
 *  Describes a two-dimensional grid for puzzle 15 with necessary functions.
 *
 * Program author ( Fill with your own info )
 * Name: Luu Tan Loc
 * Student number: 281693
 * UserID: luul ( Necessary due to gitlab folder naming. )
 * E-Mail: loc.luu@tuni.fi
 *
 * Notes:
 *
 * */

#ifndef BOARD_HH
#define BOARD_HH
#include <iostream>
#include <iomanip>
#include <random>
#include <string>
#include <vector>

using namespace std;
const int SIZE = 4;

class Board
{
public:
    Board();

    // Prints the game grid
    void print();

    // More methods
    void initBoard_RandomCase();
    //getData is used for input manually.
    void getData(vector <unsigned int>& inputVector);

    int getMove(string direction, unsigned int chosenMove);

    // Checking function
    bool isDone();
    bool isMissing(vector<unsigned int>& inputVector);
    bool isNotSovlable(vector<unsigned int>& inputVector);


private:

    // Shuffles the numbers vector by using seed as a seed value
    void my_shuffle(vector<unsigned int>& numbers, int seed);

    // Game grid for the 15 puzzle
    vector<vector<unsigned int>> grid_;

    // More attributes/methods


};

#endif // BOARD_HH
