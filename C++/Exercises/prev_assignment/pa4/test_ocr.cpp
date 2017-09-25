#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <cstdlib>
#include "character.h"
#include "point.h"
#include "bmplib.h"

using namespace std;

#define THRESH 127
// Location struct containing row and column
struct Location{
   int row; int col;
};

unsigned char image[SIZE][SIZE];
unsigned char visit[SIZE][SIZE];

int main(int argc, char *argv[])
{
   /*********************************************************************/
   // ensures that the user enters two command line arguments
   if(argc != 3){
      cout << "Enter the name of the function and debug option" << endl;
      return 1;
   }
   readGSBMP(argv[1], image); // reads from image file
   // ensures the second command line argument is 1 or 0
   if(atoi(argv[2]) != 0 && atoi(argv[2]) != 1){
      cout << "second argument should be 1 or 0 for debug info" << endl;
      return 1;
   }
   /*********************************************************************/
   /* displays the image as black and white as well as initializes all
   of the pixels to have not been previously visited. */
   for(int i = 0; i < SIZE; i++){
      for(int j = 0; j < SIZE; j++){
         visit[i][j] = 0;
         if(image[i][j] > 128){
            image[i][j] = 255;
         }
         else{
            image[i][j] = 0;
         }
      }
   }   
   /*********************************************************************/
   // counter for n Characters or n bounding boxes
   int n = 0;
   // integer vectors for corners of the bounding box
   vector<int> topRow; topRow.push_back(0);
   vector<int> botRow; botRow.push_back(0);
   vector<int> leftCol; leftCol.push_back(0);
   vector<int> rightCol; rightCol.push_back(0);

   Character nullChar;
   // vector for Characters
   // create a "NULL" default character for newly allocated elements
   vector<Character> myChar; myChar.push_back(nullChar);
   
   // start and current location for the BFS
   Location start, c;
   
   // deque that keeps track of Locations previously visited
   deque<Location> pixLoc;
   /********************************************************************/
   /* scans the 2D image for a black pixel. Once it finds a black pixel,
   it begins a breath first search to identify other black pixels that
   have not been previously explored. */
   for(int i = 0; i < SIZE; i++){
      for(int j = 0; j < SIZE; j++){     
         if(image[i][j] == 0 && visit[i][j] == 0){
            // each time a black unvisited pixel found, create new Char.
            visit[i][j] = 1;
            start.row = i; start.col = j;
            pixLoc.push_back(start);
            // initialize values for bounding box corners
            topRow[n] = start.row; leftCol[n] = start.col;
            botRow[n] = start.row; rightCol[n] = start.col;
            
            /* Locations of black unexplored pixels will be stored in a
            deque. Each Location will be analyzed using BFS for other
            neighbors. We will continue finding pixels while the Location
            deque is not empty. */
            while(!pixLoc.empty()){
               // read and remove front location of deque
               c = pixLoc.front();
               pixLoc.pop_front();
               Location temp = c;
               
               // set direction variables
               int north = c.row - 1, south = c.row + 1;
               int west = c.col - 1, east = c.col + 1;
               
               // check north location
               if(image[north][c.col] == 0 && visit[north][c.col] == 0){
                  visit[north][c.col] = 1;
                  /* if north exceeds dimensions of bounding box, then
                  top row will update. */
                  if(north < topRow[n]){
                     topRow[n] = north;
                  }
                  temp.row = north;
                  pixLoc.push_back(temp);
                  temp = c;  
               }
               // check south location
               if(image[south][c.col] == 0 && visit[south][c.col] == 0){
                  visit[south][c.col] = 1;
                  /* if south exceeds dimensions of bounding box, then
                  bottom row will update. */
                  if(south > botRow[n]){
                     botRow[n] = south;
                  }
                  temp.row = south;
                  pixLoc.push_back(temp);
                  temp = c;
               }
               // check east location
               if(image[c.row][east] == 0 && visit[c.row][east] == 0){
                  visit[c.row][east] = 1;
                  /* if east exceeds dimensions of bounding box, then
                  right column will update. */
                  if(east > rightCol[n]){
                     rightCol[n] = east;
                  }
                  temp.col = east;
                  pixLoc.push_back(temp);
                  temp = c;
               }
               // check west location
               if(image[c.row][west] == 0 && visit[c.row][west] == 0){
                  visit[c.row][west] = 1;
                  /* if west exceeds dimensions of bounding box, then
                  left column will update. */
                  if(west < leftCol[n]){
                     leftCol[n] = west;
                  }
                  temp.col = west;
                  pixLoc.push_back(temp);
                  temp = c;
               }
               // check northwest
               if(image[north][west] == 0 && visit[north][west] == 0){
                  visit[north][west] = 1;
                  // compares north and west with current box dimensions
                  if(north < topRow[n]){
                     topRow[n] = north;
                  }
                  if(west < leftCol[n]){
                     leftCol[n] = west;
                  }
                  temp.row = north; temp.col = west;
                  pixLoc.push_back(temp);
                  temp = c;
               }
               // check southwest
               if(image[south][west] == 0 && visit[south][west] == 0){
                  visit[south][west] = 1;
                  // compares south and west with current dimensions
                  if(south > botRow[n]){
                     botRow[n] = south;
                  }
                  if(west < leftCol[n]){
                     leftCol[n] = west;
                  }
                  temp.row = south; temp.col = west;
                  pixLoc.push_back(temp);
                  temp = c;
               }
               // check southeast
               if(image[south][east] == 0 && visit[south][east] == 0){
                  visit[south][east] = 1;
                  // compares south and east with current dimensions
                  if(south > botRow[n]){
                     botRow[n] = south;
                  }
                  if(east > rightCol[n]){
                     rightCol[n] = east;
                  }
                  temp.row = south; temp.col = east;
                  pixLoc.push_back(temp);
                  temp = c;
               }
               // check northeast
               if(image[north][east] == 0 && visit[north][east] == 0){
                  visit[north][east] = 1;
                  // compares north and east with current dimensions
                  if(north < topRow[n]){
                     topRow[n] = north;
                  }
                  if(east > rightCol[n]){
                     rightCol[n] = east;
                  }
                  temp.row = north; temp.col = east;
                  pixLoc.push_back(temp);
                  temp = c;
               }
            }
            int h = botRow[n] - topRow[n];
            int w = rightCol[n] - leftCol[n];
            Character updateChar(image,topRow[n]-1,leftCol[n]-1,h+1,w+1);
            myChar[n] = updateChar;
            /* word on screen counter will increase. Also push back to
            corner and row vectors. */
            topRow.push_back(0); botRow.push_back(0);
            leftCol.push_back(0); rightCol.push_back(0);
            myChar.push_back(nullChar);
            n++;
         }
      }
   }
   /*********************************************************************/
   int m = 0;
   while(m < n){
      myChar[m].perform_tests();     
      myChar[m].classify();
      cout << myChar[m].get_classification() << " ";
      m++;
   }
   cout << endl;
   
   if(atoi(argv[2]) == 1){
      int k = 0;
      while(k < n){
         myChar[k].print_calculations();
         k++;
      }
   }
   // displays the resulting image (for testing)
   showGSBMP(image);
   return 0;
}
