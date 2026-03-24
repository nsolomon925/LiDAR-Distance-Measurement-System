 #include <Arduino.h>     // Every sketch needs this
#include <Wire.h>        // Instantiate the Wire library
#include <TFLI2C.h>      // TFLuna-I2C Library v.0.1.1
#include <LiquidCrystal.h> //Library for LCD
LiquidCrystal lcd(12, 10, 5, 4, 3, 2);  //pins used for the LCD screen



//#loop forever
//while True:
//  if GPIO.input(button) == True: # Checks if the pin is HIGH
//    print("HIGH")
//  time.sleep(0.01) # In order to not overburden the CPU

TFLI2C tflI2C; //class I2C
int tfDist;    // distance in centimeters
int tfAddr = TFL_DEF_ADR;  // Use this default I2C address or

const int Button= 13;  // sets the digital pin 13 as output

void setup()
{
    Serial.begin( 115200);  // Initalize serial port
    Wire.begin();           // Initalize Wire library
    lcd.begin(16, 2);   // putting in the diaentions of the LCD
    pinMode(Button, INPUT); // setup pin 13 as input to read the button

}

void loop()  // Forever loop
{
    delay(100); // delay for our eyes to be able to see the LCD properly
    if (digitalRead(Button) == LOW){ //  if the digital pin voltage reading is at ZERO / Ground, The LIDAR reading will continue
      if( tflI2C.getData( tfDist, tfAddr)) // If read okay...
      {
          lcd.clear();               // clear LCD screen
          lcd.setCursor(2,0);        // sets cursor to row 0 column 2
          lcd.print("Dist: ");       // print "Dist: " on LCD
          lcd.print(tfDist);          // print the data...
          lcd.print("cm ");          // print "cm " on LCD
      }
    }
      else{ 
      tflI2C.printStatus();           // Debugging to serial monitor: Ready or Print Error
      delay(100);                     //delay for our eyes to be able to see the serial monitor properly
  }
}
