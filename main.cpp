/*
 Name: Kaitlynn_Pham 
 Description: The program will take user input for a level and
 read the matching file. The userwill have 5 guesses to guess
 the letters in a crossword game. The game will end when all
 correct guesses are displayed or user is out of guesses. It
 will ask the userif they would like to play again.
 Input: level number, letters for guesses, yes or no if player would like
 to play again
 Output: game board after each guess and remaining number of guesses
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

// function prototypes
void printBoard(vector<vector<char>>, vector<char>);
bool correctGuess(vector<char>, char);
bool guessedLetters(vector<char>, char);
bool incorrectGuess(vector<vector<char>>, char);
bool wonGame(vector<vector<char>>, vector<vector<char>>);
vector<vector<char>> update(vector<vector<char>>, vector<char>);

int main()

{

    // welcome message
    cout << endl
         << "     Welcome to\n\n"
         << "         W \n"
         << "     C R O S S\n"
         << "         R\n"
         << "         D\n\n";

    // ifstream variable
    ifstream iFile;
    // variable for level
    int level = 0;

    // two 2d vectors for game board
    // vector that will be changed later
    vector<vector<char>> board;
    // vector for answers
    vector<vector<char>> answers;
    // string to play again
    string play = " ";
    do
    {
        do
        { // ask user for level
            cout << "Enter level to play:\n";
            cin >> level;
            // file name with level
            string filename = "level" + to_string(level) + ".txt";

            // open file
            iFile.open(filename.c_str());
            // validate input
            if (cin.fail() || level < 1)
            {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid Entry!\n";
            }
            // check if file exists
            else if (!iFile.is_open())
            {
                cout << "Level files could not be found!\n";
            }
        } while (cin.fail() || level < 1 || !iFile.is_open());

        // string to read file
        string line;

        // read file into 2d vectors
        while (getline(iFile, line))
        {
            vector<char> temp;
            stringstream ss(line);
            char character = ' ';
            while (ss >> character)
            {
                temp.push_back(character);
            }
            board.push_back(temp);
            answers.push_back(temp);
        }

        // close file
        iFile.close();

        // vector to keep guesses
        vector<char> guesses;
        // number of guesses
        int guessCount = 5;

 
        // vector for updating board after guesses
        vector<vector<char>> updateboard;

        do
        {

            // print current game board
            cout << endl;
            printBoard(board, guesses);

            // prompt user for letter and clear input after 1st character
            char letter = ' ';
            cout << "\nEnter a letter:\n";
            cin >> letter;
            cin.clear();
            cin.ignore(100, '\n');
            // change lowercase letters to uppercase
            letter = toupper(letter);
            // check if letter was already guessed
            if (guessedLetters(guesses, letter) == true)
            {
                cout << "The letter is already guessed, try again!\n";
            }

            // check if guess was incorrect and subtract # of guesses
            else if (incorrectGuess(board, letter) == true)
            {
                cout << "The letter is not on the board\n";
                guessCount -= 1;
            }
            // keep guesses in a vector
            guesses.push_back(letter);

            // display current guesses
            cout << "Remaining incorrect guesses: "
                 << guessCount << endl;

            // update vector for current game board
            vector<vector<char>> updateboard = update(board, guesses);

            // if current game board matches answer board, exit loop
            if (wonGame(updateboard, answers))
            {
                break;
            }

        } while (guessCount > 0 && guessCount <= 5);
        // display final board
        cout << endl;
        printBoard(board, guesses);

        //reset board
        board.clear(); 

        // display message for user if won or lost
        if (guessCount == 0)
        {
            cout << "\nBetter luck next time!\n";
        }
        else
        {
            cout << "\nCongratulations! you solved the level!\n";
        }

        // loop if user wants to play again

        do
        {   //check for valid input 
            cout << "Play again? (y/n)\n";
            cin >> play;
            if (play.length() > 1 || (play != "Y" && play != "y" &&
                play != "N" && play != "n"))
            {
                cout << "Invalid Entry!\n";
                cin.clear();
                cin.ignore(100, '\n');
            }
          //close if user says no 
            else if (play == "N" || play == "n")
            {
                cout << "Thank you for playing Crossword!\n";
                return 0;
            }
        } while (play.length() >1 || (play != "Y" && play != "y" && 
        play != "N" && play != "n"));

    } while (play == "Y" || play == "y");

    return 0;
}

// function defintions
// check if guess is correct

/*
correctGuess: The function will check if the guesses match the game board
parameters: vector<char> guesses, char board
return value:true or false
*/
bool correctGuess(vector<char> guesses, char board)
{
    for (unsigned int guess = 0; guess < guesses.size(); guess++)
    {
        if (guesses[guess] == board)
        {
            return true;
        }
    }
    return false;
}
/*
guessedLetters: The function will check if the guess was already made
using the vector of guesses
parameters: vector<char> guesses, char letter
return value:true or false
*/

bool guessedLetters(vector<char> guesses, char letter)
{
    for (unsigned int i = 0; i < guesses.size(); i++)
    {
        if (letter == guesses[i])
        {
            return true;
        }
    }
    return false;
}

/*
update: The function update the original board after guesses
parameters: vector<vector<char>> board, vector<char> guesses
return value:  vector<vector<char>> board
*/
vector<vector<char>> update(vector<vector<char>> board,
                            vector<char> guesses)
{

    for (unsigned int i = 0; i < board.size(); i++)
    {
        for (unsigned int j = 0; j < board[i].size(); j++)
        {

            bool correct = correctGuess(guesses, board[i][j]);
           
            if (correct == false)
            {
                if (board[i][j] != '#')
                {
                    (board[i][j]) = '_';
                }
            }
        }
    }
    return board;
}
/*
printBoard: The function will print the updated board after guesses
parameters: vector<vector<char>> aboard, vector<char> guesses
return value: no return
*/
void printBoard(vector<vector<char>> aboard, vector<char> guesses)

{

    for (unsigned int i = 0; i < aboard.size(); i++)
    {
        for (unsigned int j = 0; j < aboard[i].size(); j++)
        {
            if (aboard[i][j] == '#')
            {
                cout << "# ";
                continue;
            }

            bool correct = correctGuess(guesses, aboard[i][j]);
            if (correct == true)
            {
                cout << aboard[i][j] << " ";
            }
            if (correct == false)
            {
                aboard[i][j] = '_';
                cout << aboard[i][j] << " ";
            }
        }
        cout << endl;
    }
}
/*
incorrectGuess: The function will check if the guess matches the board
parameters: vector<vector<char>> board, char guessedL
return value: true or false
*/
bool incorrectGuess(vector<vector<char>> board, char guessedL)
{

    for (unsigned int i = 0; i < board.size(); i++)
    {
        for (unsigned int j = 0; j < board[i].size(); j++)
        {
            if (guessedL == board[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

/*
wonGame: The function will check if the updated board with guesses
 matches the original board with answers.
parameters: vector<vector<char>> updated ,
            vector<vector<char>> answerboard
return value: true or false
*/
bool wonGame(vector<vector<char>> updated,
             vector<vector<char>> answerboard)
{
    if (updated == answerboard)
    {
        return true;
    }
    return false;
}
