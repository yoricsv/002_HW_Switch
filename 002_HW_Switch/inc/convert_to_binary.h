#pragma once
#ifndef CONVERT_TO_BINARY_H
#define CONVERT_TO_BINARY_H

#include <iostream>
#include <limits>       // std::numeric_limits<unsigned long>::max()
//#include <tchar.h>    // unicode
#include <cstdlib>      // abs() - number modulus

void convert_to_binary(uint32_t converting_value);

class Binary            // This class allows you to convert any integer to binary.
{
    unsigned long decimal;    // or uint64_t
public:
    Binary(unsigned long convert_value) : decimal(convert_value) {}
    friend std::ostream & operator << (std::ostream & outStream, const Binary & tmpObj);
};

inline     std::ostream & operator << (std::ostream & outStream, const Binary & tmpObj)
{
    const unsigned long MAX = std::numeric_limits<unsigned long>::max();    // important! get max length for UL (bits)
          unsigned long bit = ~(MAX >> 1);                                  // important! high bit

    while(bit)
    {
        outStream << (tmpObj.decimal & bit ? '1' : '0');
        bit >>= 1;
    }

    return outStream;
}
/*
    *********************************************************************************
    * NOTE (LOGIC):                                                                 *
    * In binary, the maximum value is all ones                                      *
    * MAX    = std::numeric_limits<unsigned long>::max();                           *
    * (result -> 0x 1111 1111 1111 1111)                                            *
    *                                                                               *
    * In the second line, all bits are shifted to the right by rank (divide by 2)   *
    * Of course the first one (low) will be skipped after the shifting              *
    * The left (high) bit will be assigned zero (modulo value)                      *
    * MAX    >> 1                                                                   *
    * (result -> 0x 0111 1111 1111 1111)    // (allowed change bits)                *
    *                                                                               *
    * After, this value will be inverted by ~ 'NOT' (Bitwise complement) that       *
    * make value of variable BIT like a mask                                        *
    * bit =   ~ (MAX >> 1)                  // (invert for set remain bits)         *
    * (result -> 0x 1000 0000 0000 0000)                                            *
    *
    * In a loop, we are checking
    *
    * mask = 0x 0000 1111 1111 1111 (allowed change bits)                       *
    *
    *
    * ~mask = 0x 1111 0000 0000 0000 (invert for set remain bits)       *
    * result = result & ~mask                                           *
    * result = result \ port_state (modify 7-bits 0101 1011)            *
    * result -> 0x 0000 0000 0101 1011                                  *
    *********************************************************************
*/


// Next, the high one value shifted to 1 range untill the BIT won't set in zero 0.

//      short a = -2;
//      cout << Binary(a) << endl;

// However, this class always output into stream only fixed number of bit  that consist of unsigned long type.
// For fixed, we need make this class like template, for output some numbers of the bits (Listing 14.14).


template <typename T>
class TBinary;          // Template Effector Pre-Declarations

template <typename T>
std::ostream & operator << (std::ostream & outStream, const TBinary<T> & tmpObj);

template <typename T>
class TBinary
{
    T decimal;
public:
    TBinary(T convert_value): decimal(convert_value) {}
    friend  std::ostream & operator << (std::ostream & outStream, const TBinary<T> & tmpObj);
};

template <typename T>
inline      std::ostream & operator << (std::ostream & outStream, const TBinary<T> & tmpObj)
{
    T MAX = std::numeric_limits<T>::max();
    T bit = ~(MAX >> 1);

    while(bit)
    {
        outStream << (tmpObj.decimal & bit ? '1' : '0');
        bit >>= 1;
    }

    return outStream;
}
/*
    ******************************************************************
    * LOGIC:                                                         *
    * get a port_state like 0x 0000 0000 0101 1011                   *
    * mask = 0x 0000 1111 1111 1111 (allowed change bits)            *
    * ~mask = 0x 1111 0000 0000 0000 (invert for set remain bits)    *
    * result = result & ~mask                                        *
    * result = result \ port_state (modify 7-bits 0101 1011)         *
    * result -> 0x 0000 0000 0101 1011                               *
    ******************************************************************
*/
// Notice the pre-declarations and the template function prototype operator << into Binary class.
// We might use the template class as a manipulator:

//      short a = -2;
//      std::cout << binary<unsigned short>(a)   << std::endl;  // Output: 1111111111111110
//      std::cout << binary<unsigned char> (128) << std::endl;  // Output: 10000000

// We might see the numbers of bits as types of unsigned short and unsigned char.
// Note that the use of a signed type is prohibited because we are receiving a program loop.

// CONVERT DECIMAL NUMBER TO BINARY BY FUNCTION (CLASS-FREE) BEGIN //
      void printBin       ( int convert_value);
// CONVERT DECIMAL NUMBER TO BINARY BY FUNCTION (CLASS-FREE) END   //

// CONVERTER BINARY NUMBER TO DECIMAL AND VICE VERSA BEGIN //
const  int BITS  = 32;    // length of array binary[]
       int arrLength      (char str[]);
       int exponentiation ( int decimal, int extent);
      void dec_to_bin     ( int decimal);
       int bin_to_dec     (char inBinary[]);
// CONVERTER BINARY NUMBER TO DECIMAL AND VICE VERSA END   //

#endif // CONVERT_TO_BINARY_H
