#include "convert_to_binary.h"

void convert_to_binary(uint32_t converting_value)
{
    int number_Of_DisplayBits = 16;    // length of showing bits
    int separate_OnGroup      = 4;     // separate by a space into groups of four
    int conversion_result     = 0;

    while (number_Of_DisplayBits)
    {
        if (number_Of_DisplayBits % separate_OnGroup == 0)
            std::cout << " ";
        std::cout << ((converting_value & 0x8000) >> 15);
        number_Of_DisplayBits--;
        converting_value <<= 1; // left binary shift by 1 (multiply by 2)
    }
} // CONVERT IN BINARY FORMAT FUNCTION END //



#include <string>
//Сразу напишем общую версию для всех целочисленных типов
template <typename T>
std::string intToBin(T val) {
    if (val == 0)
        return "0";  //Здесь сработает конструктор std::string

    
    //Буфер для записи двоичного представления
    //Всего битов в числе sizeof(T) * 8, и ещё один на терминальный символ
    char bary[sizeof(T) * 8 + 1];
    
    //Индекс записи в буфер выше
    int idigit = 0;
    
    bool meetOne = false;

    //Спускаемся от старшего к младшему биту
    for (int i = sizeof(T) * 8 - 1; i >= 0; i--) 
    {
        if (val & (T(1) << i)) //Если бит номер i установлен...
        {
            //...записываем 1 в соответствующий бит строкового представления
            //и устанавливаем флаг встречи с 1
            meetOne = true;
            bary[idigit++] = '1'; 
        }
        else 
        {
            //...записываем ноль, но только если до этого была единица,
            //так избавимся от ненужных ведущих нулей
            if (meetOne) 
            {
                bary[idigit++] = '0';
            }
        }
    }
    //Завершение строки терминальным символом
    bary[idigit] = '\0';

    return bary;  //Конструктор std::string
}

while(std::scanf("%d", &val) != EOF)
{
    std::printf("%s ", intToBin(val).c_str());
}


// CONVERT DECIMAL NUMBER TO BINARY BY FUNCTION (CLASS-FREE) BEGIN //
void printBin(int convert_value)
{
    // __int64 y = x;                                               // use for x64 system
    int i = 32;

    while(i)
    {
        //std::cout << (((y  << (33 - i)) & 0x100000000) >> 32);    // use for x64 system
        std::cout << ((convert_value & 0x80000000) >> 31);          // if we use without __int64
        i--;
        convert_value <<= 1;                                        // if we use without __int64
    }

    std::cout << std::endl;
}
// CONVERT DECIMAL NUMBER TO BINARY BY FUNCTION (CLASS-FREE) END   //

// CONVERTER BINARY NUMBER TO DECIMAL AND VICE VERSA BEGIN//

// The decimal number modulo divide by 2. If the result have a residual
// write 1 into i position of "binary" array, in the other case write 0.
// That step repeat up to the value of decimal number variable not equal by 0.


// Check the sign of the variable value. If the variable contains a negative number, it is
// necessary to invert the value of the array "binary [n]" (1 changes to 0 and vice versa)
// (This rights only for negative numbers.)
// Then tidy up the array "binary[n]" by inverting its values until its length reaches 0.

void dec_to_bin (int decimal)
{
    int decimal_2,
        i,
        binary[BITS];

    decimal_2 = decimal;

    for (i = 0; i < BITS; i++)
        binary[i] = 0;
    for (i = 0; decimal != 0; i++)
    {
        binary[i] = abs(decimal) % 2; // for the current value of the array, assign 1 or 0
        decimal   = abs(decimal) / 2;
    }
    if (decimal_2 < 0)
    {
        for (i = BITS - 1; i >= 0; i--)
            if (binary[i] == 1)
                binary[i] = 0;
            else
                binary[i] = 1;
    }
    for (i = 0; i < BITS; i++)
    {
        if (binary[i] == 1)
            binary[i] = 0;
        else
        {
            binary[i] = 1;
            break;
        }
    }

    std::cout << "Binary format is:" << std::endl;

    for (int i = BITS - 1; i >= 0; i--)
    {
        std::cout << binary[i];
    }
}


// First, describe a function to exponentiate a number to get the length of an array.
int arrLength(char str[])
{
    int i = 0;

    while (str[i] != 0)
        i++;

    return i - 1;
}

int exponentiation(int decimal, int extent)
{
    int a = 1;

    for(int i = 0; i < extent; i++)
        a *= decimal;

    return a;
}

// Function arrLength(char str[]) return lenth of array arrLength[],
// The exponentiation(int decimal_num, int extent) raises the value to the power of 2 extent.
// bin_to_dec(char inBinary[]) get an array inBinary[]. If first symbol equal to 1 it is negotive number.
// We must invert all symbols up to first 1 after that check again and replace all symbols by 0
// Next, convert it to decimal by exponentiation() function/

int bin_to_dec(char inBinary[])
{
    int i,
        decimal_num = 0,
        range       = 0,
        number_sign = 1;

    if (inBinary[0] == '1')                  // check first symbol (1 - negotive, 0 - positive)
    {
        for (i = BITS - 1; i >= 0; i--)      // invert up to first 1
            if (inBinary[i] == '0')
                inBinary[i] =  '1';
            else
            {
                inBinary[i] = '0';
                break;
            }

        for (i = 0; i < BITS; i++)           // invert value after first 1
            if (inBinary[i] == '1')
                inBinary[i] = '0';
            else
                inBinary[i] = '1';

        number_sign *= -1;                   // change sign of number
    }

    for (i = BITS - 1; i >= 0; i--, range++) // converter binary to decimal
        if(inBinary[i] == '1')
            decimal_num += exponentiation(2, range);

    return decimal_num * number_sign;
}
// CONVERTER BINARY NUMBER TO DECIMAL AND VICE VERSA END//
