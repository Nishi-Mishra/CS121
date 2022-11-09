#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

// TODO Write this function -- done (according to unit tests of mimir) 
int energy(const Pixel *const*image, int col, int row, int width, int height)
{
    if (row >= height)
        throw std::invalid_argument("Invalid row");
    if (col >= width)
        throw std::invalid_argument("Invalid col");


    // Note: Pixel is given as (col, row) == (x, y)  
    int red_diffsq;
    int green_diffsq;
    int blue_diffsq; 

    // go and put the previous and the next array value into variables -- done!
    Pixel next_col; // x 
    Pixel prev_col; 

    Pixel next_row; // y
    Pixel prev_row; 

    // x  
    if (col == (width - 1)) 
        next_col = image[0][row]; // wrap-around to first element 
    else 
        next_col = image[col + 1][row]; 

    if (col == 0)
        prev_col = image[width-1][row];  
    else 
        prev_col = image[col - 1][row];
    
    // y 
    if (row == (height-1))
        next_row = image[col][0]; // same deal with rows instead 
    else
        next_row = image[col][row + 1]; 

    if (row == 0)
        prev_row = image[col][height-1];
    else
        prev_row = image[col][row - 1]; 
        
    
    // find gradient x 
    // next column - previous corresponding RGB values 
    // square and add the differences 
    red_diffsq = pow((next_col.r - prev_col.r), 2);
    green_diffsq = pow((next_col.g - prev_col.g), 2);
    blue_diffsq = pow((next_col.b - prev_col.b), 2);

    int grad_x = red_diffsq + green_diffsq + blue_diffsq;   

    // find gradient y 
    // next row - previous corresponding RGB values 
    // square and add the differences

    red_diffsq = pow((next_row.r - prev_row.r), 2);
    green_diffsq = pow((next_row.g - prev_row.g), 2);
    blue_diffsq = pow((next_row.b - prev_row.b), 2); 

    int grad_y = red_diffsq + green_diffsq + blue_diffsq;

    // add gradient x + gradient y and return value 

    return grad_x + grad_y;
}

// TODO Write this function
int getVerticalSeam(const Pixel *const*image, int start_col, int width, int height, int* seam)
{
    // begin at start col, row = 0 
    int i = 0; 
    int currCol = start_col; // never added this to the array 
    seam[0] = currCol; 
    i++; 
    int currRow = 0; // first row is taken care of 
    
    int forward; // row + 1
    int left;  // row + 1, col + 1 // it is backwards -- just go with it 
    int right; // row + 1, col - 1 
    

    int totEnergy = 0; 
    totEnergy += energy(image, currCol, currRow, width, height); // add the very first energy 

    const int int_max = 2147483647; // can't include climits so we make our own lol 

    // do currRow++ at the end 
    while ((currRow+1) < height) {

        left = int_max; right = int_max; // this line was from Dr. Taele so it could hit similarity 
        

        {// before comparing, assign the correct left, right, forward 
            // we store if it is an overflow square in the tiny bool array 
            if (currCol != (width - 1)) // currCol is on the far right --> 0
                left = energy(image, currCol + 1, currRow + 1, width, height); // image[currCol + 1][currRow + 1];

            if (currCol != 0) // far left 
                right = energy(image, currCol - 1, currRow + 1, width, height); // image[currCol - 1][currRow + 1];

            forward = energy(image, currCol, currRow + 1, width, height); // image[currCol][currRow + 1]; // no way of going over bc this is checked at the beginning 
        }

        // forward > left preference; right only happens if strictly less than  
        // energy(const Pixel *const*image, int col, int row, int width, int height) 
        // energy(image, col, row, width, height) 

        if (forward <= right && forward <= left) {
            totEnergy += forward;
        }
        else if (left <= forward && left <= right) {
            totEnergy += left; 
            currCol = currCol + 1; 
        }
        else if (right < forward && right < left) {
            totEnergy += right;  
            currCol = currCol - 1; 
        }
        else {
            cout << "Fell through all the if conditions in func getVertSeam()" << endl; 
        }
        // currRow + 1 = i  
        seam[i] = currCol;  
        i++; // iterator 
        currRow++;
         
        
    } // end of while 

    //cout << endl; 

    return totEnergy;
}

// TODO Write this function
void removeVerticalSeam(Pixel **image, int& width, int height, int *verticalSeam)
{
    // remove element at [col][row] --> col is from vertSeam 
    // move elemenents at col+1 to col so one down 

    for (int r = 0; r < height; r++) {
        for (int c = verticalSeam[r]; c < (width-1); c++) {
            image[c][r] = image[c + 1][r]; 
        }
    }

    width--; 
}

// TODO Write this function for extra credit
int getHorizontalSeam(const Pixel *const*image, int start_row, int width, int height, int* seam)
{
    // begin at col = 0, start row = 0 ---> WE GO SIDEWAYS NOT DOWN 
    int i = 0; // this deals with column 
    int currRow = start_row; 
    seam[0] = currRow;
    i++;
    int currCol = 0; 

    int forward; // col + 1
    int left;  // col + 1, row + 1 // it is backwards -- just go with it 
    int right; // col + 1, row - 1 
    

    int totEnergy = 0;
    totEnergy += energy(image, currCol, currRow, width, height); // add the very first energy 

    const int int_max = 2147483647; 

    // do currCol++ at the end 
    while ((currCol + 1) < width) {

        left = int_max; right = int_max; // this line was from Dr. Taele so it could hit similarity 


        {// before comparing, assign the correct left, right, forward 
            // we store if it is an overflow square in the tiny bool array 
            if (currRow != (height - 1)) // currCol is on the far right --> 0
                left = energy(image, currCol + 1, currRow + 1, width, height); 

            if (currRow != 0) // far left 
                right = energy(image, currCol + 1, currRow - 1, width, height); 

            forward = energy(image, currCol + 1, currRow, width, height); // no way of going over bc this is checked at the beginning 
        }

        // forward > left preference; right only happens if strictly less than  
        // energy(const Pixel *const*image, int col, int row, int width, int height) 
        // energy(image, col, row, width, height) 

        if (forward <= right && forward <= left) {
            totEnergy += forward;
        }
        else if (left <= forward && left <= right) {
            totEnergy += left;
            currRow = currRow + 1;
        }
        else if (right < forward && right < left) {
            totEnergy += right;
            currRow = currRow - 1; 
        }
        else {
            cout << "Fell through all the if conditions in func getHorizSeam()" << endl;
        }
  
        seam[i] = currRow;
        i++; // iterator 
        currCol++;


    } // end of while 

    return totEnergy;
}

// TODO Write this function for extra credit
void removeHorizontalSeam(Pixel **image, int width, int& height, int *horizontalSeam)
{
    for (int c = 0; c < width; c++) {
        for (int r = horizontalSeam[c]; r < (height - 1); r++) {
            image[c][r] = image[c][r+1];
        }
    }

    height--;
}

int *findMinVerticalSeam(const Pixel *const*image, int width, int height)
{
  // initialize minSeam and minDistance to seam starting at first col (index 0)
  int *minSeam = new int[height]{0};
  int minDist = getVerticalSeam(image, 0, width, height, minSeam);

  int *candidateSeam = new int[height]{0};
  int candidateDistance = -1; // invalid distance

  // start at second col (index 1) since we initialized with first col (index 0)
  for (int col = 1; col < width; ++col)
  {
    candidateDistance = getVerticalSeam(image, col, width, height, candidateSeam);

    if (candidateDistance < minDist)
    { // new min
      //  swap min & candidate
      minDist = candidateDistance;
      int* temp = candidateSeam;
      candidateSeam = minSeam;
      minSeam = temp;
    }
  }

  // clean up 
  delete [] candidateSeam;

  return minSeam;
}

int *findMinHorizontalSeam(const Pixel *const*image, int width, int height)
{
  // initialize minSeam and minDistance to seam starting at first row (index 0)
  int *minSeam = new int[width]{0};
  int minDistance = getHorizontalSeam(image, 0, width, height, minSeam);

  int *candidateSeam = new int[width]{0};
  int candidateDistance = -1; // invalid distance

  // start at second row (index 1) since we initialized with first row (index 0)
  for (int row = 1; row < height; ++row)
  {
    candidateDistance = getHorizontalSeam(image, row, width, height, candidateSeam);

    if (candidateDistance < minDistance)
    { // new minimum
      //  swap min and candidate seams
      minDistance = candidateDistance;
      int* temp = candidateSeam;
      candidateSeam = minSeam;
      minSeam = temp;
    }
  }

    // clean up 
  delete [] candidateSeam;

  return minSeam;
}

Pixel **createImage(int width, int height)
{
  cout << "Start createImage... " << endl;

  // Create a one dimensional array on the heap of pointers to Pixels
  //    that has width elements (i.e. the number of columns)
  Pixel **image = new Pixel *[width] {}; // initializes to nullptr

  for (int col = 0; col < width; ++col)
  { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    try
    {
      image[col] = new Pixel[height];
    }
    catch (std::bad_alloc &e)
    {
      // clean up already allocated arrays
      for (int i = 0; i < col; ++i)
      {
        delete[] image[i];
      }
      delete[] image;
      // rethrow
      throw e;
    }
  }

  // initialize cells
  // cout << "Initializing cells..." << endl;
  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      // cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = {0, 0, 0};
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel **image, int width)
{
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i = 0; i < width; ++i)
  {
    delete[] image[i];
  }
  delete[] image;
  image = nullptr;
  cout << "End deleteImage..." << endl;
}

bool isValidColor(int colorVal)
{
  if (colorVal < 0 || colorVal > 255)
  {
    return false;
  }
  return true;
}

Pixel ** loadImage(string filename, int &width, int &height)
{
  cout << "Start loadImage..." << endl;
  // remove
  ifstream ifs(filename);
  if (!ifs.is_open())
  {
    throw std::invalid_argument("Failed to open input file (" + filename + ")");
  }

  string type;
  ifs >> type; // should be P3
  if (toupper(type.at(0)) != 'P' || type.at(1) != '3')
  {
    throw std::domain_error("Not PPM type P3 (" + type + ")");
  }
  ifs >> width;
  // cout << "w and h: " << w << " " << h << endl;
  if (ifs.fail())
  {
    throw std::domain_error("Read non-integer value for width");
  }
  if (width <= 0)
  {
    ostringstream oss;
    oss << "Width in file must be greater than 0 (" << width << ")";
    throw std::domain_error(oss.str());
  }

  ifs >> height;
  if (ifs.fail())
  {
    cout << "Read non-integer value for height" << endl;
  }
  if (height <= 0)
  {
    ostringstream oss;
    oss << "Height in file must be greater than 0 (" << height << ")";
    throw std::domain_error(oss.str());
  }

  int colorMax = 0;
  ifs >> colorMax;
  if (ifs.fail())
  {
    throw std::domain_error("Read non-integer value for max color value");
  }
  if (colorMax != 255)
  {
    ostringstream oss;
    oss << "Max color value must be 255 (" << colorMax << ")";
    throw std::domain_error(oss.str());
  }

  // load image throws exceptions but we will let them pass through
  Pixel **image = createImage(width, height);

  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      // cout << "Pixel(" << col << ", " << row << ")" << endl;
      ifs >> image[col][row].r;
      if (ifs.fail() && !ifs.eof())
      { // bad input that is not caused by being at the end of the file
        throw std::domain_error("Read non-integer value for red");
      }
      if (!isValidColor(image[col][row].r))
      {
        ostringstream oss;
        oss << "Invalid color value for red (" << image[col][row].r << ")";
        throw std::domain_error(oss.str());
      }

      ifs >> image[col][row].g;
      if (ifs.fail() && !ifs.eof())
      { // bad input that is not caused by being at the end of the file
        throw std::domain_error("Read non-integer value for green");
      }
      if (!isValidColor(image[col][row].r))
      {
        ostringstream oss;
        oss << "Invalid color value for green (" << image[col][row].r + ")";
        throw std::domain_error(oss.str());
      }

      ifs >> image[col][row].b;
      if (ifs.fail() && !ifs.eof())
      { // bad input that is not caused by being at the end of the file
        throw std::domain_error("Read non-integer value for blue");
      }
      if (!isValidColor(image[col][row].r))
      {
        ostringstream oss;
        oss << "Invalid color value for blue (" << image[col][row].r + ")";
        throw std::domain_error(oss.str());
      }
    }
  }
  cout << "End loadImage..." << endl;
  return image;
}

void outputImage(string filename, const Pixel *const *image, int width, int height)
{
  cout << "Start outputImage..." << endl;
  // remove code
  // declare/define and open output file stream with filename
  ofstream ofs(filename);
  // ensure file is open
  if (!ofs.is_open())
  {
    throw std::invalid_argument("Error: failed to open output file - " + filename);
  }
  ofs << "P3" << endl;
  ofs << width << " " << height << endl;
  ofs << 255 << endl;
  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      ofs << image[col][row].r << " ";
      ofs << image[col][row].g << " ";
      ofs << image[col][row].b << " ";
    }
    ofs << endl;
  }
  cout << "End outputImage..." << endl;
}