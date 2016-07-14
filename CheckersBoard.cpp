#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include "minimax.hpp"
using namespace std; //For the std notation.

//Sections//

//Main
//Check Move
//Display Board
//Input move
//Moving Pieces

//Gets stuck in an infinite loop if a single move is entered incorrectly, the input move function continues to go on forever without stop.
//Keeps on asking to leap if you want to leap -- might be an easy fix?

extern char Player_Turn;
extern bool leaping;
void do_the_leap();
void leap_again();
bool check_player ();
bool check_piece () ;
bool check_backwards();
bool check_taken ();
bool check_diagonal ();
bool check_only_column ();
bool check_leap ();
bool check_move ();
extern char board[8][8];
void display_board();
extern int row1, row2, column1, column2;
void input_move_sub1 ();
void input_move_sub2 ();
void input_move ();
bool game_running = false;
extern bool king;
void move_piece ();
void do_the_leap();
void placeKing();
void game_over();




//
//------------------------------------------------MAIN---------------------------------------------------------------

char Player_Turn = 'B'; // The program does not read in the Player's turn for some reason?
bool leaping = false;


Minimax minmax_object; //declares the usage of the minimax algorithm

//The game is played in the main function using all the functions declared below.

int main ()
{
    while (game_running == false)
    {
        leaping = false;
        display_board();
        minmax_object.boardvalue();
        input_move();
        //check_move();
        while (check_move () == false) //while this is true, loops until a correct move is entered.
        {
            input_move();
            //check_move();
        }
        move_piece();
        placeKing (); // Only places King if the opposite pieces are at either end.
        game_over();
    };

    if (Player_Turn == 'B')
    {
        cout << "Red wins!" << endl;
    }
    else if (Player_Turn == 'R')
    {
        cout << "Black wins!" << endl;
    };
    cout << "Game Over.";
    return 0;
};













//--------------------------------------------------------CHECKMOVE------------------------------------------------------------------------

//need a check for moving to the exact same spot
bool check_player ()
{
    if (Player_Turn == 'B')
    {
        if (board[row1][column1] == 'R' || board[row1][column1] == 'r')
        {
            cout << "You are moving the other player's piece!";
            return false;
        }
        else
        {
            return true;
        };
    };
    if (Player_Turn == 'R')
    {
        if (board[row1][column1] == 'B' || board[row1][column1] == 'b')
        {
            cout << "You are moving the other player's piece!";
            return false;
        }
        else
        {
            return true;
        };
    }
    else
    {
        return true;
    };
};


bool check_piece () {
    //Check if a black or red pawn piece or king piece is selected
    if ((board[row1][column1] != 'B' && board[row1][column1] != 'b') &&  Player_Turn == 'B')
    {
        cout << "You have not selected a piece" << endl;
        return false;
    }
    else if ((board[row1][column1] != 'R' && board[row1][column1] != 'r') &&  Player_Turn == 'R')
    {
        cout << "You have not selected a piece" << endl;
        return false;
    }
    else {
        return true;
    };
};

bool check_backwards()
{
    //Checks if either player is moving backwards
    if (Player_Turn == 'B' && board[row1][column1] == 'B' && row1 > row2 )
    {
        cout << "You are trying to move backwards" << endl;
        return false;
    }
    else if (Player_Turn == 'R' && board[row1][column1] == 'R' && row2 > row1)
    {
        cout << "You are trying to move backwards" << endl;
        return false;
    }
    else {
        return true;
    };
};

bool check_taken () // check to see if the space is already taken by another piece
{
    if (board[row2][column2] == ' ') {
        return true;
    }
    else {
        cout << "You are moving to a spot with another piece already in it" << endl;
        return false;
    };
};

bool check_diagonal () //check if the piece is not moving diagonally
{
    if (column1 == column2 || row1 == row2)
    {
        cout << "You aren't moving diagonally -- that's against the rules!" << endl;
        return false;
    }
    else {
        return true;
    };
};


bool check_only_column ()
{
    if ((column2 > column1 + 1 || column2 < column1 - 1) && (row2 == row1+1 || row2 == row1-1))
    {
        cout << "You are moving by more than two columns!" << endl;
        return false;
    }
    else {
        return true;
    };
};

bool check_leap ()
{
    if ((row2 > row1+1 || row2 < row1 - 1))
    {
        if(row2 > row1 + 2 && row2 < row1 - 2)
        {
            cout << "This leap is too far" << endl;
            leaping = false;
            return false;
        }
        else if (column2 != column1 + 2 && column2 != column1 - 2)
        {
            cout << "You have leaped too far to the side!" << endl;
            leaping = false;
            return false;
        }
        else if ( row2 > row1 && column2 > column1)
        {
            if (board[row2-1][column2-1] == ' ')
            {
                cout << "You have leaped over nothing!" << endl;
                leaping = false;
                return false;
            };
        }

        else if (row2 > row1 && column2 < column1)
        {
            if(board[row2-1][column2+1] == ' ')
            {
                cout << "You have leaped over nothing!" << endl;
                leaping = false;
                return false;
            };
        }
        else if (row2 < row1 && column2 > column1)
        {
            if(board[row2+1][column2-1] == ' ')
            {
                cout << "You have leaped over nothing!" << endl;
                leaping = false;
                return false;
            };
        }
        else if (row2 < row1 && column2 < column1)
        {
            if(board[row2+1][column2+1] == ' ')
            {
                cout << "You have leaped over nothing!" << endl;
                leaping = false;
                return false;
            };
        }
    leaping = true;
    return true;
    }
else {return true;}

};



bool check_move ()
{
    /*check_piece ();
    check_backwards ();
    check_taken ();
    check_diagonal ();
    check_only_column ();
    check_player ();
    check_leap (); */
    if (check_piece () == false || check_backwards () == false || check_taken () == false || check_diagonal() == false || check_only_column () == false ||  check_player () == false || check_leap () == false )
    {
        return false;
    }
    else
    {
       return true;
    }
};












//----------------------------------------------------------DISPLAYBOARD-----------------------------------------------------


char board[8][8] =
{
    {' ', 'B', ' ', 'B', ' ', 'B', ' ', 'B'},
    {'B', ' ', 'B', ' ', 'B', ' ', 'B', ' '},
    {' ', 'B', ' ', 'B', ' ', 'B', ' ', 'B'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'R', ' ', 'R', ' ', 'R', ' ', 'R', ' '},
    {' ', 'R', ' ', 'R', ' ', 'R', ' ', 'R'},
    {'R', ' ', 'R', ' ', 'R', ' ', 'R', ' '},
};

void display_board()
{
cout << 0 <<  1 <<  2 <<  3 <<  4 <<  5 <<  6 <<  7  <<  endl << endl;
cout << board[0][0] << board[0][1] << board[0][2] << board[0][3] << board[0][4] << board[0][5] << board[0][6] << board[0][7] << " " << 0 << endl;
cout << board[1][0] << board[1][1] << board[1][2] << board[1][3] << board[1][4] << board[1][5] << board[1][6] << board[1][7] << " " << 1 << endl;
cout << board[2][0] << board[2][1] << board[2][2] << board[2][3] << board[2][4] << board[2][5] << board[2][6] << board[2][7] << " " << 2 << endl;
cout << board[3][0] << board[3][1] << board[3][2] << board[3][3] << board[3][4] << board[3][5] << board[3][6] << board[3][7] << " " << 3 << endl;
cout << board[4][0] << board[4][1] << board[4][2] << board[4][3] << board[4][4] << board[4][5] << board[4][6] << board[4][7] << " " << 4 << endl;
cout << board[5][0] << board[5][1] << board[5][2] << board[5][3] << board[5][4] << board[5][5] << board[5][6] << board[5][7] << " " << 5 << endl;
cout << board[6][0] << board[6][1] << board[6][2] << board[6][3] << board[6][4] << board[6][5] << board[6][6] << board[6][7] << " " << 6 << endl;
cout << board[7][0] << board[7][1] << board[7][2] << board[7][3] << board[7][4] << board[7][5] << board[7][6] << board[7][7] << " " << 7 << endl;

};










//---------------------------------------------------------------INPUTMOVE----------------------------------------------------------

int row1, row2, column1, column2;

void input_move_sub1 () {
cout << endl << endl << "Pick a piece on the board to move ---- " << endl;
cout << "Row: ";
cin >> row1;
cout << "Column: ";
cin >> column1;
}

void input_move_sub2 () {
cout << "Pick a box to move the piece to -----" << endl;
cout << "Row: ";
cin >> row2;
cout << "Column: ";
cin >> column2;
}

void input_move ()
{
input_move_sub1 ();

while ( ((row1 < 0) || (row1 > 7)) || ((column1 < 0) || (column1 > 7)) )
{
    cout << "Enter a number for the row and column between 0 and 7";
    input_move_sub1 ();
};

input_move_sub2 ();

while ( ((row2 < 0) || (row2 > 7)) || ((column2 < 0) || (column2 > 7)) )
{
    cout << "Enter a number for the row and column between 0 and 7" << endl << endl;
    input_move_sub2 ();
};
};
















//------------------------------------------------------------------MOVINGPIECES-------------------------------------------------------

//All the possible moves for the pieces and performs them.

void move_piece ()
{
    bool king = false;
    if (board[row1][column1] == 'b' || board[row1][column1] == 'r' )
        {
            king = true;
        };

    if (Player_Turn == 'B')
    {
        if (check_move () == true && king == false)
        {
            if (leaping == true)
                {

                    board[row2][column2] = 'B';
                    board[row1][column1] = ' ';
                    do_the_leap();
                }
            else
                {
                    board[row2][column2] = 'B';
                    board[row1][column1] = ' ';
                }
            Player_Turn = 'R';
            cout << endl << "Red's turn" << endl;

        }
        else if (check_move () == true && king == true)
        {
            if (leaping == true)
                {

                    board[row2][column2] = 'b';
                    board[row1][column1] = ' ';
                    do_the_leap();
                }
            else
                {
                    board[row2][column2] = 'b';
                    board[row1][column1] = ' ';
                }
            Player_Turn = 'R';
            cout  << endl << "Red's turn" << endl;

        }
    }
    else if (Player_Turn == 'R')
    {
        if (check_move () == true && king == false)
        {
            if (leaping == true)
                {

                    board[row2][column2] = 'R';
                    board[row1][column1] = ' ';
                    do_the_leap();
                }
            else
                {
                board[row2][column2] = 'R';
                board[row1][column1] = ' ';
                }
            Player_Turn = 'B';
            cout << endl << "Black's turn" << endl;

        }
        else if (check_move () == true && king == true)
        {
            if (leaping == true)
                {
                    board[row2][column2] = 'r';
                    board[row1][column1] = ' ';
                    do_the_leap();
                }
            else
                {
                board[row2][column2] = 'r';
                board[row1][column1] = ' ';
               }
            Player_Turn = 'B';
            cout << endl << "Black's turn" << endl;

        }
    };


};

//If leaping is true, then the function performs a leap of the pieces.


void do_the_leap()
{

    if (row2 == row1 + 2 && column2 == column1 + 2)
    {
        board[row2 - 1][column2 - 1] = ' ';
    }
    else if (row2 == row1 + 2 && column2 == column1 - 2)
    {
        board[row2 - 1][column2 + 1] = ' ';
    }
    else if (row2 == row1 - 2 && column2 == column1 +2)
    {
        board[row2+1][column2 - 1] = ' ';
    }
    else if (row2 == row1 - 2 && column2 == column1 - 2)
    {
        board[row2 +1][column2 +1] = ' ';
    }

leap_again();

};


void leap_again()
{
    char leap_again;

cout << endl << endl;
display_board();

//leaping once more if possible

cout << "IF POSSIBLE: do you want to leap again? Y or N." << endl;
cin >> leap_again;

if (leap_again == 'Y' || leap_again == 'y')
{
    row1 = row2;
    column1 = column2;
    cout << "Pick the place you want to leap again to.";
    cout << "Row 2: ";
    cin >> row2;
    cout << "Column 2: ";
    cin >> column2;

    while (row2 < 0 || row2 > 7 || column2 < 0 || column2 > 7)
    {
        cout << "Illegal move!" << endl;
        cout << "Pick the place you want to leap again to.";
        cout << "Row 2: ";
        cin >> row2;
        cout << "Column 2: ";
        cin >> column2;
    };

    check_move();

    if (leaping == false)
    {
        cout << "You cannot leap." << endl;
    }
    else if (leaping == true)
    {
        move_piece();
    };

    /*if (Player_Turn == 'B')
    {
        Player_Turn = 'R';
        //cout << "Red's turn" << endl;
    }
    else if (Player_Turn == 'R')
    {
        Player_Turn = 'B';
        //cout << "Black's turn" << endl;
    }; */
};
};

// Looks at the board spots at the end and checks whether or not they have the opposite pawn piece on them. And replaces
//with king if so.

void placeKing()
{
    for(int i = 0; i < 8; i++)
    {
        if (board[0][i] == 'R')
        {
            board[0][i] = 'r';
        }
        if (board[7][i] == 'B')
        {
            board[7][i] = 'b';
        }
    }
};


// testing whether or not the game is running, or if the game is over at all. Two checking counters check for black and
// red pieces on the board, and examine the entire board and assign values based on the amount of pieces on the board. If
// either equals 0 at any point, then the game is over because all the opposite pieces have been "captured".

void game_over()
{
    int checkingCounterB = 0;
    int checkingCounterR = 0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] == 'B')
            {
                checkingCounterB++;
            }
            else if (board[i][j] == 'b')
            {
                checkingCounterB++;
            }
            else if (board[i][j] == 'R')
            {
                checkingCounterR++;
            }
            else if (board[i][j] == 'r')
            {
                checkingCounterR++;
            }
        }
    }

if (checkingCounterB == 0 || checkingCounterR == 0)
    {
        game_running = true;
    }
else
    {
        game_running = false;
    }

};
