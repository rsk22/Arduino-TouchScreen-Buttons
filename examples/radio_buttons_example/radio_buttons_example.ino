/* 
  Title: TouchScreenRadioButton Tutorial
  About: Example/tutorial file for how to create radio buttons with the TouchScreenRadioButtons library
  Author: Richard Kirkpatrick
  Date: 20 July 2014
*/

// Libraries
#include <stdint.h>  
#include <TouchScreen.h>  // Library for the Seeed Studio TFT Touch Shield 
#include <TFT.h>      // Library for the Seeed Studio TFT Touch Shield 
#include <TouchScreenButtons.h> // Library for creating buttons for the keypad

#ifdef SEEEDUINO
  #define YP A2   // must be an analog pin, use "An" notation!
  #define XM A1   // must be an analog pin, use "An" notation!
  #define YM 14   // can be a digital pin, this is A0
  #define XP 17   // can be a digital pin, this is A3 
#endif

#ifdef MEGA
  #define YP A2   // must be an analog pin, use "An" notation!
  #define XM A1   // must be an analog pin, use "An" notation!
  #define YM 54   // can be a digital pin, this is A0
  #define XP 57   // can be a digital pin, this is A3 
#endif 

//Measured ADC values for (0,0) and (210-1,320-1)
//TS_MINX corresponds to ADC value when X = 0
//TS_MINY corresponds to ADC value when Y = 0
//TS_MAXX corresponds to ADC value when X = 240 -1
//TS_MAXY corresponds to ADC value when Y = 320 -1
#define TS_MINX 140
#define TS_MAXX 900
#define TS_MINY 120
#define TS_MAXY 940

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// Global variables
RadioButton radioButton1(50, 50, WHITE, RED);
RadioButton radioButton2(50, 75, WHITE, YELLOW);
RadioButton radioButton3(50, 100, WHITE, GREEN);

boolean buttonState1 = false;
boolean buttonState2 = false;
boolean buttonState3 = false;


void setup()
{
  // Initializes the TFT library
  Tft.init();      
 
  // Start the Serial port. Used to determine which button was pressed.
  Serial.begin(9600); 
  
  // Draw the radio buttons
  radioButton1.draw();
  radioButton2.draw();
  radioButton3.draw(); 
}


void loop()
{
  // A point objects holds x, y, and z coordinates
  Point p = ts.getPoint(); 
  p.x = map(p.x, TS_MINX, TS_MAXX, 240, 0);
  p.y = map(p.y, TS_MINY, TS_MAXY, 320, 0);
  
  // Determine which button was pressed
  int userInput = -1; // -1 means no button is pressed.  Resets for each loop.
  if (p.z > ts.pressureThreshhold) 
    userInput = getButtonNumber(p.x, p.y); 
  
  // Show which button was pressed on the Serial monitor
  if (userInput >= 1 && userInput <= 3) {
    Serial.print("Radio Button #: ");
    Serial.println(userInput);
    Serial.print("Radio Button #'s State: ");
    Serial.print(radioButton1.getButtonState());
    Serial.print(radioButton2.getButtonState());
    Serial.println(radioButton3.getButtonState());
  }
  
  delay(50);
}


// Determines which radio button was pressed
const int getButtonNumber(const int xInput, const int yInput)
{
  if (radioButton1.isButtonPressed(xInput, yInput)) {
    radioButton1.resetButtonState();
    return 1;
  } else if (radioButton2.isButtonPressed(xInput, yInput)) {
    radioButton2.resetButtonState();  
    return 2;
  } else if (radioButton3.isButtonPressed(xInput, yInput)) {
    radioButton3.resetButtonState();
    return 3; 
  } else {
    return -1; // signified no button was pressed
  }
}
  
  
