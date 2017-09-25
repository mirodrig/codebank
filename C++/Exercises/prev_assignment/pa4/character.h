#ifndef CHARACTER_H
#define CHARACTER_H

class Character {
 public:
  Character();
  // the first parameter should just be passed in and saved to 
  //  the 'image' data member as in ( image = myimage; )
  Character(unsigned char(*myimage)[256], int ulr, int ulc, int h, int w);
  ~Character();

  void perform_tests();
  void classify();
  char get_classification();
  
  // returns upper-left point and lower-right point of bounding box
  //  DOES NOT compute bounding box...it's already in your data members
  //  just returns the bounding box if a user wants the bounds
  void get_bounding_box(int &ulr, int &ulc, int &lrr, int &lrc);
  void print_calculations();

 private:
  //==============
  // Helper Functions
  //==============
  void calc_bit_quads(); // does the bit quads operation
  int calc_area(); // calculates the area of the character
  int calc_perimeter(); // calculates the perimeter of the character
  int calc_euler_number(); // calculates the euler number of the char..
  int calc_vert_centroid(); // calcs vertical centroids
  int calc_horz_centroid(); // calculates horizontal centroid
  int calc_sym(); // calcs horizontal and vertical symmetry
  int calc_aspect_ratio(); // height divided by width of character

  //==============
  // Data Members
  //==============
 private: 
  int ul_r, ul_c; // upper left row and column
  int height, width; // height and width of character
  
  // feel free to add functions here.
  
  // number of each type of bit quad
  int q0, q1, q2, qd, q3, q4;
  // stores test results
  int area, perimeter, euler;
  int vCen, hCen, sym, ratio;
  
  char recognized_char; // resulting output from performing tests
  unsigned char (*image)[256]; // pointer to 2D array
};
#endif
