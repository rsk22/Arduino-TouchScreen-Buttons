/* 
  Title: TouchScreenButton Tutorial
  About: Example/tutorial file for how to create buttons with the TouchScreenButtons library
  Author: Richard Kirkpatrick
  Date: 20 July 2014
*/

// Libraries
#include <stdint.h>  
#include <TouchScreen.h>  // Library for the Seeed Studio TFT Touch Shield 
#include <TFT.h>      // Library for the Seeed Studio TFT Touch Shield 
#include <TouchScreenGeometry.h> // Library for drawing geometric shapes for the touch screen
#include <TouchScreenStrings.h> // Library for drawing strings for the touch screen
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
Button bigButton;
Button buttons[12];

void setup() 
{
  // Initializes the TFT library
  Tft.init();      
 
  // Start the Serial port. Used to determine which button was pressed.
  Serial.begin(9600); 
  
  // Draw the big button
  bigButton.setValues(15, 15, 216, 35);
  bigButton.draw();
  
  // Draw the big button's text
  TouchScreenString bigButtonText("BIG BUTTON", 40, 30, 2, WHITE);
  bigButtonText.drawText();
  
  // Parameters for the array of buttons
  const int xstartButton[] = {15, 95, 175};           // x-min for keypads
  const int ystartButton[] = {65, 127, 189, 251};     // y-min for keypads
  const int xendButton[] = {65, 145, 225};            // x-max for keypads
  const int yendButton[] = {115, 177, 239, 301};      // y-min for keypads
  const int widthButton = 50;
  const int heightButton = widthButton;
  
  // Sets the coordinates and sizes of the keypad buttons, and sets all the values for the buttons' text
  const int noRows = 4;
  const int noColumns = 3;
  for(int y = 0; y < noRows; y++) {
      for(int x = 0; x < noColumns; x++) {
          int buttonNumber = noColumns * y + x;
          buttons[buttonNumber].setValues(xstartButton[x], ystartButton[y], widthButton, heightButton);
      }
  }
  
  // Draw the array of buttons
  for (int i = 0; i < 12; i++) 
    buttons[i].draw();
}

void loop()
{
  // A point objects holds x, y, and z coordinates
  Point p = ts.getPoint(); 
  p.x = map(p.x, TS_MINX, TS_MAXX, 240, 0);
  p.y = map(p.y, TS_MINY, TS_MAXY, 320, 0);
  
  // Determine which button was pressed
  int userInput = -1; // -1 means no button is pressed
  if (p.z > ts.pressureThreshhold) 
    userInput = getButtonNumber(p.x, p.y); 
 
  // Show which button was pressed on the Serial monitor
  if (userInput >= 0 && userInput < 12) {
    buttons[userInput].buttonDisplay();
    Serial.print("Button #: ");
    Serial.println(userInput + 1);
  } 
  else if (userInput == 13) {
    Serial.println("Big button was pressed!");
    bigButton.buttonDisplay();
  }
  delay(10);
}

// Gets which button was pressed.  If no button is pressed, -1 is returned.
int getButtonNumber(int xInput, int yInput)
{
  for (int i = 0; i < 12; i++) {
    if (buttons[i].isPressed(xInput, yInput)) 
      return i; // Returns the button number that was pressed
  }

  if (bigButton.isPressed(xInput, yInput)) {
    return 13; // Signifies big button was pressed
  } else {
  return -1; // Signifies no button was pressed
  }
}


