#include <bits/stdc++.h>
#include <stdexcept>
#include <climits>


int Largest(int a, int b, int c) {
  int max = a;
  if (max < b) 
    max = b; 
  if (max < c) 
    max = c; 
  
  return max;
}

bool SumIsEven(int a, int b) {
  if( (a+b) % 2 == 0){
    return true;
  } else {
    return false;
  }
}

int BoxesNeeded(int apples) {

  if (apples <= 0)
    return 0;
  else {
    if (apples % 20 == 0)
      return apples / 20; 
    else 
      return apples / 20 + 1; 
  }
}

bool SmarterSection(int A_correct, int A_total, int B_correct, int B_total) {
  double percentA = 1.0 * A_correct / A_total; 
  double percentB = 1.0 * B_correct / B_total;
  // A better than B = true 

  if (A_correct > A_total || B_correct > B_total || A_correct < 0 || B_correct < 0 || A_total < 0 || B_total < 0)
    throw std::invalid_argument(""); 

  if (percentA > percentB) {
    return true; 
  } else {
    return false; 
  }

}


bool GoodDinner(int pizzas, bool is_weekend) {
  if (is_weekend) {
    if (pizzas >= 10) 
      return true; 
    return false; 
  } else {
    if (pizzas >= 10 && pizzas <= 20)
      return true; 
    return false; 
  }
}

int SumBetween(int low, int high) {
  int value = 0;
  // int result; 
  if (low > high) {
    throw std::invalid_argument("");
  }

  if (low != INT32_MIN && (-1*low) == high) {
    // -100 to 100 
    return 0;
  }
  if (low == high) {
    return high; // 20 to 20 = 20 
  }

  if (low < 0 && high > 0 && (high + low) > 0) {
    // if it is -100 to 300 do 101 to 300 
    low = -1*low + 1; 
    //std::cout << "1" << std::endl; 
  } else if (low < 0 && high > 0 && (low + high) < 0) {
    // if -500 to 100 then do -500 to -101 
    high = -1*high - 1; 
    //std::cout << "2\n" << "  High is now equal to " << high << " Low is now " << low << std::endl; 
  } 
  
  //std::cout << "Is low equal to high? " << (low == high) << std::endl; 

  
  if (low == high) { 
    //std::cout << "Yes we are in the right place" << std::endl; 
    return high; 
  }
  if (low != INT32_MIN && (-1*low) == high) {
    // -100 to 100 
    //std::cout << "Wrong place" << std::endl;
    return 0;
  } 

  // std::cout << "Low: " << low << " High: " << high << std::endl; 

  for (int n = low; n <= high; n++) {

    // overflow doesn't actually error out so we have problems with unexpected behavior 
    
    // method 3 
    //result = value + n; // x+y > max == overflow // for both positive or n+value > max -->   n > max - value 
    // both negative also could over 
    // x + y < min == overflow   // x < min - y -->  n < min - value 
    
    // std::cout << " n: " << n << " value: " << value << std::endl; 

    if (n > 0 && value > 0 && n > INT32_MAX - value) {
      throw std::overflow_error("Int max block"); 
    } else if (n < 0 && value < 0 && n < INT32_MIN - value) { 
      throw std::overflow_error("Int min block"); 
    } else {
      value += n; 
    }


  // method 2 
    // result = value + n; // going with the approach of checking what should always be true 
    // if (((value + n) == result) && ((result - n) == value)) {
    //   value = result;
    // } else {
    //   throw std::overflow_error(""); 
    // }

  // method 1 
  /*
    if ( (value > 0) && (n > 0) && (value + n) < 0 ) {
      // if both positive then result isn't positive an overflow occured 
      throw std::overflow_error(""); 
    } else if ((value < 0) && (n < 0) && (value + n) > 0 ) {
      // if both are negative then result should be negative 
      throw std::overflow_error(""); 
    }  
    else if (  (value > n && (value + n) < 0) || (n > value && (value + n) < 0)  ) {
      // if one of the values are bigger than the other, it should be an overall positive  
      throw std::overflow_error(""); 
    } else {
      value += n;
    }
  */

    // if ((value + n) > INT32_MAX || (value + n) < INT32_MIN) {
    //   throw std::overflow_error(""); 
    // } else {
       
    // }
  }
  
  return value;
}

int Product(int a, int b) {

  int product = a * b; 
  if ( (a * b) == product && (product / a) == b) {
    return product;
  } else {
    throw std::overflow_error(""); 
  }

  /*
    // +a       +b        - res 
  if ( a > 0 && b > 0 && (a*b) < 0) {
    throw std::overflow_error("");
  }
  //        -a       -b       -res 
  else if ( a < 0 && b < 0 && (a*b) < 0 ) {
    throw std::overflow_error("");
  } 
  //          -a       +b          +a       -b        +res 
  else if ( ((a < 0 && b > 0) || (a > 0 && b < 0)) && (a*b) > 0) {
    throw std::overflow_error("");
  }
  */

  // if ( (a*b) > INT32_MAX ||  (a*b) < INT32_MIN) {
  //     throw std::overflow_error("");
  // }

}


/*
int main () {

  int max = INT32_MAX;
  int min = INT32_MIN; 

  std::cout << "Sum between:" << SumBetween(INT32_MIN, INT32_MAX) << std::endl; 

} 
*/
