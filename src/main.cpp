#include <Arduino.h>
#include "../lib/LiquidCrystal_I2C/LiquidCrystal_I2C.h"
#include "characters.h"

#define Serial_Baud 9600

#define LCD_ADDRESS_SCORE 0x3E
#define LCD_ADDRESS_DEBUG 0x3F

char buffer[8];
bool buffer_read = false;

char tool_id; int item_id; char function_id; unsigned char value1; unsigned char value2; unsigned char value3; unsigned char value4; unsigned char value5;

LiquidCrystal_I2C lcd(LCD_ADDRESS_SCORE,16,2);
LiquidCrystal_I2C lcd_debug(LCD_ADDRESS_DEBUG,16,2);

void custom0(int col)
{ // Uses segments to build numbers/letters, in this case numbers from 0 to 9
  lcd.setCursor(col, 0);
  lcd.write(2);
  lcd.write(8);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
}

void custom1(int col)
{
  lcd.setCursor(col,0);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
  lcd.setCursor(col,1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom2(int col)
{
  lcd.setCursor(col,0);
  lcd.write(5);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(6);
}

void custom3(int col)
{
  lcd.setCursor(col,0);
  lcd.write(5);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(7);
  lcd.write(6);
  lcd.write(1);
}

void custom4(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom5(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(col, 1);
  lcd.write(7);
  lcd.write(6);
  lcd.write(1);
}

void custom6(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
}

void custom7(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(8);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom8(int col)
{
  lcd.setCursor(col, 0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
}

void custom9(int col)
{
  lcd.setCursor(col, 0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(7);
  lcd.write(6);
  lcd.write(1);
}
	// Function which determines which number we are going to print and in which col
void printNumber(int value, int col) {
  if (value == 0) {
    custom0(col);
  } if (value == 1) {
    custom1(col);
  } if (value == 2) {
    custom2(col);
  } if (value == 3) {
    custom3(col);
  } if (value == 4) {
    custom4(col);
  } if (value == 5) {
    custom5(col);
  } if (value == 6) {
    custom6(col);
  } if (value == 7) {
    custom7(col);
  } if (value == 8) {
    custom8(col);
  } if (value == 9) {
    custom9(col);
  }
}


void display_number(int first, int second, int third) {
  printNumber(first, 7);		  //Printing digit x, starting on col 7
  printNumber(second, 10);		//Printing digit y, starting on col 10
  printNumber(third, 13);     //Printing digit z, starting on col 13
}

void setup_dispaly() {
  lcd.createChar(1,bar1);
  lcd.createChar(2,bar2);
  lcd.createChar(3,bar3);
  lcd.createChar(4,bar4);
  lcd.createChar(5,bar5);
  lcd.createChar(6,bar6);
  lcd.createChar(7,bar7);
  lcd.createChar(8,bar8);

  // Using segments to make letter E
  lcd.setCursor(0, 0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(3);
  lcd.setCursor(0, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(6);

  // Using segments to make letter P
  lcd.setCursor(3, 0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(3,1);
  lcd.write(2);

  display_number(0,0,0);
}


void setup() {
  Serial.begin(Serial_Baud);
  lcd.init();
  lcd.backlight();
  lcd_debug.init();
  lcd_debug.backlight();

  setup_dispaly();

}

void loop() {
    if(Serial.available() >= 8) {
      Serial.readBytes(buffer, 8);
      buffer_read = true;
    }

    if(buffer_read) {
      tool_id     = buffer[0];
      item_id     = buffer[1];
      function_id = buffer[2];
      value1      = buffer[3];
      value2      = buffer[4];
      value3      = buffer[5];
      value4      = buffer[6];
      value5      = buffer[7];

      if(tool_id == 'd') {
        if(item_id == 's') {  // score
          if(function_id == 'u') { // update
            display_number(value1,  value2, value3);
          } else if(function_id == 'c') { // clear
            // clear the display to 0
            display_number(0,0,0);
          } else if(function_id == 'f') { // flash em
            lcd.noBacklight();
            delay(500);
            lcd.backlight();
          }
        } else if(item_id == 'd') { // debug
          if(function_id == 'p') { // write out position
            lcd_debug.clear();
            lcd_debug.setCursor(0, 0);
            lcd_debug.print("X: ");
            lcd_debug.print((value1 << 8) + value2);
            lcd_debug.setCursor(0, 1);
            lcd_debug.print("Y: ");
            lcd_debug.print((value3 << 8) + value4);

          } else if(function_id == 'i') { // info
            // display info like: what side, battery and info about startup
            // value1 = battery voltage in V (odometry)
            // value2 = battery voltage in V (glavna)
            // value3 = which side (1 or 0)
            // value4 = tactic name

            value1 /= 10; value2 /= 10; // to get decimal value

            lcd_debug.clear();
            lcd_debug.setCursor(0, 0);
            lcd_debug.print("Bat O ");
            lcd_debug.print((float)value1);       // in Volts
            lcd_debug.print(" G ");
            lcd_debug.print((float)value2);       // in Volts
            lcd_debug.setCursor(0, 1);
            lcd_debug.print("Sd: ");              // Side
            lcd_debug.print(value3);              // add if and write whole out
            lcd_debug.print(" Tac: ");
            lcd_debug.print(value4);              // add if and write whole out

          } else if(function_id == 'r') { // we are ready to kick ass
            // print out ready message!
            lcd_debug.clear();
            lcd_debug.print("LET'S FUKKEN GO!");
          } else if(function_id == 'w') { // we are setting up to smash some ass
            // print out the wait message!
            lcd_debug.clear();
            lcd_debug.print("Setting shit up...");

          }
        }
      } else if(tool_id == 'b') { // board

      }

      Serial.write(1); // signaling glavna that everything is okay

      buffer_read = false;
    }
}
