#include <iostream>
#include "character.h"
#include "point.h"
#include "bmplib.h"
#include <cstdlib>
#include <cmath>

using namespace std;

// default constructor
Character::Character(){
   ul_r = 0; ul_c = 0;
   height = 0; width = 0;
   q0 = 0; q1 = 0; q2 = 0; qd = 0; q3 = 0; q4 = 0;
   area = 0; perimeter = 0; euler = 0;
   vCen = 0; hCen = 0; sym = 0; ratio = 0;
   image = NULL;
}
/************************************************************************/
// (*myarray)[256] is a pointer to a 256 x 256 2D array
//    each character can access any pixel data from 2D image
Character::Character(unsigned char (*myimage)[256], int ulr, int ulc,
int h, int w){
   ul_r = ulr; ul_c = ulc;
   height = h; width = w;
   image = myimage;
}
Character::~Character(){
}
/************************************************************************/
// performs bit quads iteration
void Character::calc_bit_quads(){
   // initialized values
   int Q0 = 0, Q1 = 0, Q2 = 0, Q3 = 0, Qd = 0, Q4 = 0;
   int sr = ul_r; int sc = ul_c;
   for(int i = sr - 1; i <= sr + height; i++){
      for(int j = sc - 1; j <= sc + width; j++){
         // finds which bit quads have all four black cells     
         if(image[i][j] == 0 && image[i+1][j] == 0 &&
         image[i][j+1] == 0 && image[i+1][j+1] == 0){
            Q4++;   
         }
         // find which bit quads contain one black cell
         else if(image[i][j] == 0 && image[i+1][j] == 255 &&
         image[i][j+1] == 255 && image[i+1][j+1] == 255){
            Q1++;
         }
         else if(image[i][j] == 255 && image[i+1][j] == 0 &&
         image[i][j+1] == 255 && image[i+1][j+1] == 255){
            Q1++;
         }
         else if(image[i][j] == 255 && image[i+1][j] == 255 &&
         image[i][j+1] == 0 && image[i+1][j+1] == 255){
            Q1++;
         }
         else if(image[i][j] == 255 && image[i+1][j] == 255 &&
         image[i][j+1] == 255 && image[i+1][j+1] == 0){
            Q1++;
         }
         // finding which bit quads contain two non-diagonal black cells
         else if(image[i][j] == 0 && image[i][j+1] == 0 &&
         image[i+1][j] == 255 && image[i+1][j+1] == 255){
            Q2++;
         }
         else if(image[i][j] == 255 && image[i][j+1] == 0 &&
         image[i+1][j] == 255 && image[i+1][j+1] == 0){
            Q2++;
         }
         else if(image[i][j] == 255 && image[i][j+1] == 255 &&
         image[i+1][j] == 0 && image[i+1][j+1] == 0){
            Q2++;
         }
         else if(image[i][j] == 0 && image[i][j+1] == 255 &&
         image[i+1][j] == 0 && image[i+1][j+1] == 255){
            Q2++;
         }
         // finding which bit quads contain two diagonal black cells
         else if(image[i][j] == 0 && image[i][j+1] == 255 &&
         image[i+1][j] == 255 && image[i+1][j+1] == 0){
            Qd++;
         }
         else if(image[i][j] == 255 && image[i][j+1] == 0 &&
         image[i+1][j] == 0 && image[i+1][j+1] == 255){
            Qd++;
         }
         // finding which bit quads contain three black cells
         else if(image[i][j] == 255 && image[i+1][j] == 0 &&
         image[i][j+1] == 0 && image[i+1][j+1] == 0){
            Q3++;
         }
         else if(image[i][j] == 0 && image[i+1][j] == 255 &&
         image[i][j+1] == 0 && image[i+1][j+1] == 0){
            Q3++;
         }
         else if(image[i][j] == 0 && image[i+1][j] == 0 &&
         image[i][j+1] == 255 && image[i+1][j+1] == 0){
            Q3++;
         }
         else if(image[i][j] == 0 && image[i+1][j] == 0 &&
         image[i][j+1] == 0 && image[i+1][j+1] == 255){
            Q3++;
         }
         else{
            Q0++;
         }
      }
   }
   q0 = Q0; q1 = Q1; q2 = Q2; qd = Qd; q3 = Q3; q4 = Q4;
}
/************************************************************************/
// calculates the area of the character
int Character::calc_area(){
   return (q1 + (2*q2) + (2*qd) + (3*q3) + (4*q4)) / 4;
}
// calculates the perimeter of the character
int Character::calc_perimeter(){
   return q1 + q2 + (2*qd) + q3;
}
// calculates the Euler number
int Character::calc_euler_number(){
   return (q1 - q3 - (2*qd)) / 4;
}
/************************************************************************/
// calculates vertical centroid
int Character::calc_vert_centroid(){
   int vert_center = 0; int total_black = 0;
   for(int i = ul_r; i < ul_r + height; i++){
      for(int j = ul_c; j < ul_c + width; j++){
         if(image[i][j] == 0){
            vert_center += i;
            total_black++;
         }
      }
   }
   return vert_center / total_black;
}
/************************************************************************/
// calcs horizontal centroid
int Character::calc_horz_centroid(){
   int horz_center = 0; int total_black = 0;
   for(int i = ul_r; i < ul_r + height; i++){
      for(int j = ul_c; j < ul_c + width; j++){
         if(image[i][j] == 0){
            horz_center += j;
            total_black++;
         }
      }
   }
   return horz_center / total_black;
}
/************************************************************************/
// calculates vertical and horizontal symmetry
int Character::calc_sym(){
   // scans the image to see if there is horizontal or vertical symmetry
   for(int i = ul_r; i < ul_r + height; i++){
      for(int j = ul_c; j < ul_c + width; j++){
         if(image[i][j] != image[ul_r+height-1][j] &&
         image[i][j] != image[i][ul_c+width-1]){
            return 0;
         }
      }
   }
   return 1;
}
/************************************************************************/
int Character::calc_aspect_ratio(){
   return height / (width+1);
}
// calls any private member functions to perform classification tests
// stores results in appropriate data members.
void Character::perform_tests(){
   calc_bit_quads();
   area = calc_area(); perimeter = calc_perimeter();
   euler = calc_euler_number();
   vCen = calc_vert_centroid(); hCen = calc_horz_centroid();
   sym = calc_sym(); ratio = calc_aspect_ratio();
}
/************************************************************************/
// uses results from the tests to classify the character and then stores
// the data as a private member variable.
void Character::classify(){
   if(euler == -1){
      recognized_char = '8';
   }
   else if(euler == 0){
      if(sym == 1){
         recognized_char = '0';
      }
      else{
         if(vCen > ul_r+(height/2) && hCen < ul_c+(width/2)){
            recognized_char = '6';
         }
         else{
            if(abs(hCen-(ul_c+(width/2))) > abs(vCen-(ul_r+(height/2)))){
               recognized_char = '4';
            }
            else{
               if(hCen > ul_c + (width/2)){
                  recognized_char = '9';
               }
               else{
                  recognized_char = '0';
               }
            }
         }
      }
   }
   else if(euler == 1){
      if(image[vCen][hCen] == 0){
         if(vCen > ul_r+(height/2) && hCen < ul_c+(width/2)){
            recognized_char = '1';
         }
         else if(hCen > ul_c+(width/2)){
            recognized_char = '3';
         }
         else{
            recognized_char = '5';
         }
      }
      else{         
         if(abs(vCen-(ul_r+(height/2))) > 2*abs(hCen-(ul_c+(width/2)))){
            recognized_char = '7';
         }
         else if(vCen > ul_r+(height/2)){
            recognized_char = '2';
         }
         else{
            recognized_char = '5';
         }
      }   
   }
}
/************************************************************************/
// returns character the character object represents
char Character::get_classification(){
   return recognized_char;
}
// returns upper left corner and bottom right corner
// look at aliases!!!
void Character::get_bounding_box(int &ulr, int &ulc, int &lrr, int &lrc){
   ulr = ul_r;
   ulc = ul_c;
   lrr = ul_r + height;
   lrc = ul_c + width;
}
// prints test results to the screen for debugging purposes.
void Character::print_calculations(){
   cout << "BQ0=" << q0 << " BQ1=" << q1 << " BQ2=" << q2;
   cout << " BQ3=" << q3 << " BQ4=" << q4 << " BQD=" << qd << endl;
   cout << "===================================================" << endl;
   cout << "Area=" << area << endl;
   cout << "Perimeter=" << perimeter << endl;
   cout << "Euler Number=" << euler << endl;
   cout << "VCentroid=" << vCen << " HCentroid=" << hCen << endl;
   cout << "Symmetrical: " << sym << endl;
   cout << "Aspect Ratio=" << ratio << endl;
   cout << "Character classified as: " << recognized_char << endl;
}
