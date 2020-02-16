/* Game15 (or puzzle 15) : Template code
 *
 * Class: Board
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

#include "board.hh"
#include <iostream>
#include <iomanip>
#include <random>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
const int EMPTY = 16;
const unsigned int PRINT_WIDTH = 5;
const vector<unsigned int> PATTERN = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};





Board::Board()
{

}

//Printing the Board
void Board::print()
{
    for(unsigned int x = 0; x < SIZE; ++x)
    {
        std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
        for(unsigned int y = 0; y < SIZE; ++y)
        {
            std::cout << "|" << std::setw(PRINT_WIDTH - 1);
            if(grid_.at(x).at(y) != EMPTY)
            {
                std::cout << grid_.at(x).at(y);
            }
            else
            {
                std::cout << ".";
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
}

//Check the initial vector which cannot be solved
bool Board::isNotSovlable(vector<unsigned int>& inputVec){
    int sumN = 0;
    int flagEmpty = 0;

    for(unsigned int i = 0; i < inputVec.size();i++){
        int n = 0;
        for(unsigned int j = i + 1; j < inputVec.size();j++){
            if(inputVec[i]>inputVec[j]){
                ++n;
            }
        }
        if(inputVec[i] == 16){
           flagEmpty = i;
        }
        sumN +=n;
    }

    //Check EMPTY on even row from the bottom
    if( (sumN % 2 == 0 && (flagEmpty - 8) <= (11 - flagEmpty)) ||
            (sumN % 2 == 0 && (flagEmpty - 0) <= (3 - flagEmpty)) ||
            //Check EMPTY on odd row from the bottom
            (sumN % 2 != 0 && (flagEmpty - 12) <= (15 - flagEmpty)) ||
            (sumN % 2 != 0 && (flagEmpty - 4) <= (7 - flagEmpty)) ||
            (sumN % 2 != 0 && inputVec[15]==16) ){
        cout << "Game is not solvable. What a pity." <<endl;
        return false;
    }
    return true;
}

/*Check manual input number for vector in range [1-16]
 * without duplicating number or missing any number in [1-16]
 * or being not enough 16 elemements
*/
bool Board::isMissing(vector<unsigned int>& inputVec){
    vector<unsigned int> temp = inputVec;
    //Sort elements in temp vector after copy from inputVec and compare to PATTERN
    sort(temp.begin(), temp.end());
    for(unsigned int i = 0; i < inputVec.size(); i++){
        if(temp[i] != PATTERN[i]){
            cout << "Number "<< PATTERN[i] <<" is missing" << endl;
            return false;
        }
    }
    return true;
}

//Reading and insert value to grid_ for Board manually
void Board::getData(vector <unsigned int>& inputVector){

    // Using insert shuffled value to grid_
    int k = 0;
    for( int y = 0; y < SIZE; ++y ) {
        vector<unsigned int> row = {};
        for( int x = 0; x < SIZE; ++x ) {
            row.push_back(inputVector.at(k++));
        }
        grid_.push_back(row);
    }
}

//Create the initial value for Board
void Board::initBoard_RandomCase(){
    cout <<"Enter a seed value (or an empty line): ";
    string seed_value = " ";
    vector<unsigned int> tempPATTERN;
    tempPATTERN = PATTERN; // Copy PATTERN to a temp vector.

    getline(cin, seed_value);
    if( seed_value == " " ) {
        my_shuffle(tempPATTERN,0);
    }
    else if (stoi(seed_value) == 1){
        cout << "Game is not solvable. What a pity.";
        //return EXIT_SUCCESS;
    }
    else{
        // If the user gave a seed value, use it.
        my_shuffle(tempPATTERN,stoi(seed_value));
    }
}

//Shuffling every single data on each grid_'s row
void Board::my_shuffle(vector<unsigned int> &numbers, int seed)
{
    default_random_engine randomEng(seed);
    uniform_int_distribution<int> distr(0, numbers.size() - 1);
    for(unsigned int i = 0; i < numbers.size(); ++i)
    {
        unsigned int random_index = distr(randomEng);
        unsigned int temp = numbers.at(i);
        numbers.at(i) = numbers.at(random_index);
        numbers.at(random_index) = temp;
    }

    // Using insert shuffled value to grid_
    int k = 0;
    for( int y = 0; y < SIZE; ++y ) {
        vector<unsigned int> row = {};
        for( int x = 0; x < SIZE; ++x ) {
            row.push_back(numbers.at(k++));
        }
        grid_.push_back(row);
    }
}

// Checking the result of Board
bool Board::isDone(){
    vector<unsigned int> flatten_grid_;
    // Transform 2 dimension vector to 1 dimension vector
    // and compare to PATTERN.
    for( int i = 0; i < SIZE; ++i ) {
        for( int j = 0; j < SIZE; ++j ) {
            flatten_grid_.push_back(grid_[i][j]);
        }
    }
    if(flatten_grid_ == PATTERN){
        return false;
    }
    return true;
}

//check Move function
int Board::getMove(string direction, unsigned int chosenMove){

    //Locating chosenMove.
    int x = 0;
    int y = 0;
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(grid_[i][j] == chosenMove){
                x = i;
                y = j;
                break;
            }
        }
    }

    if (chosenMove < 1 || chosenMove > 16){
        cout << "Invalid number: " << chosenMove << endl;
    }
    else if(direction == "d"){
        //Move Right
        if(grid_[x][y+1] != EMPTY || y+1 == SIZE){
            cout << "Impossible direction: " << direction << endl;
        }else
            swap( grid_[x][y], grid_[x][y+1]);
    }
    else if(direction == "a"){
        // Move Left
        if(grid_[x][y-1] != EMPTY || y-1 == SIZE){
            cout << "Impossible direction: " << direction << endl;
        }else
            swap( grid_[x][y], grid_[x][y-1]);
    }
    else if(direction == "w"){
        // Move Up
        if(grid_[x-1][y] != EMPTY || x-1 == SIZE){
            cout << "Impossible direction: " << direction << endl;
        }else
            swap( grid_[x][y], grid_[x-1][y]);
    }
    else if(direction == "s"){
        //Move down
        if(grid_[x+1][y] != EMPTY || x+1 == SIZE){
            cout << "Impossible direction: " << direction << endl;
        }else
            swap( grid_[x][y], grid_[x+1][y]);
    }
    else{
        cout << "Unknown command: " << direction << endl;
    }
    return 1;
}
