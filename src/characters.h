
#include <Arduino.h>

//Making custom characters, 8 of them is maximum, so we made it so every number can be made with combination of these 8 parts
byte bar1[8] =
{
        B11110,
        B11110,
        B11110,
        B11110,			// 1's will be shown on the lcd, 0's aren't on
        B11110,
        B11110,
        B11110,
        B11110
};
byte bar2[8] =
{
        B01111,
        B01111,
        B01111,
        B01111,			// 1's will be shown on the lcd, 0's aren't on
        B01111,
        B01111,
        B01111,
        B01111
};
byte bar3[8] =
{
        B11111,
        B11111,
        B00000,
        B00000,			// 1's will be shown on the lcd, 0's aren't on
        B00000,
        B00000,
        B11111,
        B11111
};
byte bar4[8] =
{
        B11110,
        B11110,
        B00000,
        B00000,			// 1's will be shown on the lcd, 0's aren't on
        B00000,
        B00000,
        B11110,
        B11110
};
byte bar5[8] =
{
        B01111,
        B01111,
        B00000,
        B00000,			// 1's will be shown on the lcd, 0's aren't on
        B00000,
        B00000,
        B01111,
        B01111
};
byte bar6[8] =
{
        B00000,
        B00000,
        B00000,
        B00000,			// 1's will be shown on the lcd, 0's aren't on
        B00000,
        B00000,
        B11111,
        B11111
};
byte bar7[8] =
{
        B00000,
        B00000,
        B00000,
        B00000,			// 1's will be shown on the lcd, 0's aren't on
        B00000,
        B00000,
        B01111,
        B01111
};
byte bar8[8] =
{
        B11111,
        B11111,
        B00000,
        B00000,			// 1's will be shown on the lcd, 0's aren't on
        B00000,
        B00000,
        B00000,
        B00000
};
