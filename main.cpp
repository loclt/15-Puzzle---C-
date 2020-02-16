/* Game15 (or puzzle 15) : Template code
 *
 * Desc:
 *  This program generates a 15 puzzle. The board is SIZE x SIZE,
 * (original was 4x4) and every round the player chooses a direction and
 * a number tile, making the given tile to be moved to the given direction.
 *  Game will end when the numbers 1-15 (1-16) are in the ascending order,
 * starting from top left and proceeding row by row.
 * Empty space is represented by the number 16 in the code (constant EMPTY)
 * and by dot when printing the game board.
 *
 * Program author ( Fill with your own info )
 * Name: Luu Tan Loc
 * Student number: 281694
 * UserID: luul ( Necessary due to gitlab folder naming. )
 * E-Mail: loc.luu@tuni.fi
 *
 * Notes about the program and it's implementation:
 *
 * */

#include "board.hh"
#include <iostream>
#include <string>

using namespace std;

//Split function which is reused from the exercise in this week.
vector<string> split(string input, char seperator, bool ignoreEmpty=false){
    vector<string> result;
    string::size_type start = 0;

    for (string::size_type i=0 ;i<=input.size();i++)
    {
        if(input[i] == seperator || i==input.size()){

            if(i-start == 0 && ignoreEmpty ){
                start = i+1;
                continue;
            }

            result.push_back(input.substr(start,i-start));
            start = i+1;
        }
    }

    return result;
}

int main()
{
    Board board;
    string cmd;
    while(true){
        cout <<"Random initialization (y/n): ";
        cin >> cmd;
        if(cmd == "y" || cmd == "n")
            break;
        else
            cout << "Unknown choice: " << cmd << endl;
    }
    cin.ignore();

    if (cmd == "y"){
        board.initBoard_RandomCase();
        cout << "Game is solvable: Go ahead!"<<endl;

        while(board.isDone() == true){
            board.print();

            string command = "";
            cout << "Dir (command, number): ";
            getline(cin,command);
            vector<string> parts  = split(command,' ');
            if (parts[0] == "q") return EXIT_SUCCESS;

            board.getMove(parts[0],stoi(parts[1]));
        }
        board.print();
        cout << "You won!" << endl;

    }else if (cmd == "n"){
        cout << "Enter the numbers 1-16 in a desired order (16 means empty):"<<endl;
        vector<unsigned int> inputNumbers = {};
        int element;

        // Insert every single number to temp vector before inserting them to grid_
        for(int i = 0; i < 16; ++i){
            std::cin >> element;
            inputNumbers.push_back(element);
        }
        cin.ignore();

        //Check missing case and being not sovlable case
        if(board.isMissing(inputNumbers) == false)
            return EXIT_FAILURE;
        if(board.isNotSovlable(inputNumbers) == false)
            return EXIT_SUCCESS;

        board.getData(inputNumbers);
        cout << "Game is solvable: Go ahead!"<<endl;

        while(board.isDone() == true){
            board.print();

            string command = "";
            cout << "Dir (command, number): ";
            getline(cin,command);
            vector<string> parts  = split(command,' ');
            if (parts[0] == "q") return EXIT_SUCCESS;

            board.getMove(parts[0],stoi(parts[1]));

        }
        board.print();
        cout << "You won!" << endl;;
    }
    return EXIT_SUCCESS;

}


