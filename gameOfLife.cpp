/* 
	Author: Katherine Sandoval
	Date: 10/25/2013
	Contact: kate_sandoval27@hotmail.com
    Description: This program simulates Conway's Game of Life.
*/

#include "consolecolours.h"
#include <sstream>  
#include <iomanip>        // setw()
#include <windows.h>      // setConsoleTitle(), Sleep()
#include <stdio.h>        // standard input/output 
#include <cstdlib>        // rand(), seed()
#include <iostream>       // cout
using namespace std;

// OUR DATA and CONSTANTS
const char LIFE  = '8';
const char BLANK = '.';

const int N = 15;
const int M = 15;
const int nLife = M>N ? M/2 : N/2;
char world[N*M];     // will simulate 2-dimenisonal array.


// OUR FUNCTIONS (ie, TOOLS) that work on our DATA
void fillWorldwith(char w[], const int N, const int M, const char stuff){
 for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
     w[i*M+j*sizeof(char)]=stuff;
}

void fillWorldwithLife(char w[], const int N, const int M, const int Life){
    for(int k=0; k<Life; k++)
    {
        int i = rand()%N;
        int j = rand()%M;
        w[i*M+j*sizeof(char)]=LIFE;
    }
}

void displayWorld(char *w, const int N, const int M){
 for(int i=0; i<N; i++)
 {
   for(int j=0; j<M; j++)
     cout << setw(2) << w[i*M+j*sizeof(char)];
   cout << endl;
 }
}

// Used in applyRules as a buffer to update world.
void copyWorld(char dest[], char src[], const int N, const int M){
  for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
      dest[i*M+j*sizeof(char)]= src[i*M+j*sizeof(char)];
}

// Rules
/* 1. Any live cell with fewer than two live neighbours dies, as if caused by under-population.
   2. Any live cell with two or three live neighbours lives on to the next generation.
   3. Any live cell with more than three live neighbours dies, as if by overcrowding.
   4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.  */
void applyRules(char  w[], const int N, const int M)
{
    char *t = new char[N*M];    // create a temporary world

    copyWorld(t, w, N, M);      // copy world w to temporary world t
    for(int i=0; i<N; i++)
     for(int j=0; j<M; j++)
     {
       int liveNeighCnt = 0;
            // All possible neighbors
            if (w[(i-1)*M+j] == LIFE)
            {
                liveNeighCnt++;
            }
            if (w[(i-1)*M+(j-1)] == LIFE)
            {
                liveNeighCnt++;
            }
           
            if (w[(i-1)*M+(j+1)] == LIFE)
            {
                liveNeighCnt++;
            }
            if(w[(i+1)*M+j] == 1)
            {
                liveNeighCnt++;
            }
            if (w[i*M+(j-1)] == LIFE)
            {
                liveNeighCnt++;
            }
           
            if (w[i*M+(j+1)] == LIFE)
            {
                liveNeighCnt++;
            }
            if (w[(i+1)*M+(j-1)] == LIFE)
            {
                liveNeighCnt++;
            }
            if (w[(i+1)*M+(j+1)] == LIFE)
            {
                liveNeighCnt++;
            }
          
            
           
            if (w[i*M+j] == LIFE && liveNeighCnt < 2)                               // rule 1
            {
               t[i*M+j] = BLANK;
            }
            else if (w[i*M+j] == LIFE && (liveNeighCnt == 2 || liveNeighCnt == 3))  // rule 2
            {
               t[i*M+j] = LIFE;
            }
            else if (w[i*M+j] == LIFE && liveNeighCnt > 3)                           // rule 3
            {
               t[i*M+j] = BLANK;
            }
            else if (w[i*M+j] == BLANK && liveNeighCnt == 3)                         // rule 4
            {
               t[i*M+j] = LIFE;
            } 
    }

    copyWorld(w, t, N, M);  // copy temp world to w world: w <- temp
}


int main()
{
    SMALL_RECT windowSize = {0, 0, 200, 200};           // windows
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // windows

    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);  // windows
    SetConsoleTitle("Game of Life");                    // windows

    system("cls");                                      // clear the console
    stringstream ss;                                    // trick to combine string and numbers
    ss << "color " << Black << Yellow;

    // objects are fun to use.
    system( ss.str().c_str() );                         // change console colour

    fillWorldwith(world, N, M, BLANK);                  // fill whole world with BLANKS
    displayWorld(world, N, M);
   
    fillWorldwithLife(world, N, M, 60);                 // new random life
   
    for(int time=0; time<50; time++)                    // each loop, considered time.
    {                    
     system("cls");
     applyRules(world, N, M);
     displayWorld(world, N, M);                         // display world
     Sleep(1000);                                       // delay so we can see world
    }

    system("pause");
    return 0;
}


/*
This is a command line parameter for the MS-DOS console.
I placed all this data in a header file for use with C++

Sets the default console foreground and background colors.
COLOR [attr]

  attr        Specifies color attribute of console output

Color attributes are specified by TWO hex digits -- the first
corresponds to the background; the second the foreground.  Each digit
can be any of the following values:

    0 = Black       8 = Gray
    1 = Blue        9 = Light Blue
    2 = Green       A = Light Green
    3 = Aqua        B = Light Aqua
    4 = Red         C = Light Red
    5 = Purple      D = Light Purple
    6 = Yellow      E = Light Yellow
    7 = White       F = Bright White

If no argument is given, this command restores the color to what it was
when CMD.EXE started
*/