#include "minimax.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>

using namespace std; //For the std notation.
extern char board[8][8];

int Minimax::boardvalue ()
{
int boardvalue = 0;
int R, B, r, b;
R = 12;
B = -12;
r = 30;
b = -30;
for (int k = 0; k < 8; k++)
{
    for (int i = 0; i < 8; i++)
    {
        if (board[k][i] == 'R')
        {
            boardvalue += R;
        }
        else if (board[k][i] == 'B')
        {
            boardvalue += B;
        }
        else if (board[k][i] == 'r')
        {
           boardvalue += r;
        }
        else if (board[k][i] == 'b')
        {
            boardvalue += b;
        };
    }
}
cout << "Test system ----- The board value at this point is: " <<  boardvalue;
return boardvalue;
};
