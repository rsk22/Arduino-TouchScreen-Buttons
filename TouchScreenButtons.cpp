/*
   TouchScreenButton.cpp - Library for creating buttons for the Seeed Studio TFT touch screen.
   Created by Richard Kirkpatrick, 26 June 2014
*/

#include "Arduino.h"
#include "TouchScreenButtons.h"

#include <stdint.h>
#include <TouchScreen.h>
#include <TouchScreenGeometry.h>
#include <TouchScreenStrings.h>
#include <TFT.h>
#include <math.h>

/*
----------------------------------------------------------------
                        Button Class
----------------------------------------------------------------
*/

Button::Button()
{
    button = Rectangle();
}

Button::Button(const int myXStart, const int myYStart, const int myWidth, const int myHeight, unsigned int myBorderColor, unsigned int myFillColor)
{
    button = Rectangle(myXStart, myYStart, myWidth, myHeight, myBorderColor, myFillColor);
}

Button::Button(char* myButtonText, const int myXStart, const int myYStart, const int myWidth, const int myHeight, unsigned int myBorderColor, unsigned int myFillColor, unsigned int myTextColor)
{
    button = Rectangle(myXStart, myYStart, myWidth, myHeight, myBorderColor, myFillColor);
    buttonText = TouchScreenString(myButtonText, myXStart + myWidth / 2, myYStart + myHeight / 2, 1, myTextColor);
}

void Button::setValues(const int myXStart, const int myYStart, const int myWidth, const int myHeight)
{
    button.setUpperLeft(myXStart, myYStart);
    button.setSize(myWidth, myHeight);
}

void Button::setTextValues(char* myText, const int myXStart, const int myYStart, const int myFontSize, const unsigned int myTextColor)
{
    buttonText.setText(myText);
    buttonText.setTextCoord(myXStart, myYStart);
    buttonText.setFontSize(myFontSize);
    buttonText.setTextColor(myTextColor);
}

void Button::setText(char* myText)
{
    buttonText.setText(myText);
}

void Button::setTextCoord(const int myXStart, const int myYStart)
{
    buttonText.setTextCoord(myXStart, myYStart);
}

void Button::setFontSize(const int myFontSize)
{
    buttonText.setFontSize(myFontSize);
}

void Button::setTextColor(const unsigned int myTextColor)
{
    buttonText.setTextColor(myTextColor);
}

void Button::setSize(const int myWidth, const int myHeight)
{
    button.setSize(myWidth, myHeight);
}

void Button::setBorderColor(unsigned int myBorderColor)
{
    button.setBorderColor(myBorderColor);
}

void Button::setFillColor(unsigned int myFillColor)
{
    button.setFillColor(myFillColor);
}

const int Button::getXStart()
{
    return button.getXStart();
}

const int Button::getYStart()
{
    return button.getYStart();
}

const int Button::getXEnd()
{
    return button.getXEnd();
}

const int Button::getYEnd()
{
    return button.getYEnd();
}

const int Button::getWidth()
{
    return button.getWidth();
}

const int Button::getHeight()
{
    return button.getHeight();
}

const unsigned int Button::getBorderColor()
{
    return button.getBorderColor();
}

const unsigned int Button::getFillColor()
{
    return button.getFillColor();
}

bool Button::isPressed(const int xInput, const int yInput)
{
    return ((xInput > button.getXStart() && xInput < button.getXEnd()) && (yInput > button.getYStart() && yInput < button.getYEnd()));
}

void Button::draw()
{
    button.draw();
    buttonText.drawText();
}

void Button::fill()
{
    button.fill();
    buttonText.drawText();
}

void Button::buttonDisplay(unsigned int myHighlightColor)
{
    unsigned int originalBorderColor = button.getBorderColor(); ///< Saves the original border color
    unsigned int originalTextColor = buttonText.getTextColor(); ///< Saves the original text color
    setBorderColor(myHighlightColor);
    buttonText.setTextColor(myHighlightColor);
    draw();
    delay(100);
    setBorderColor(originalBorderColor);
    buttonText.setTextColor(originalTextColor);
    draw();
}


/*
----------------------------------------------------------------
                        RadioButton Class
----------------------------------------------------------------
*/
RadioButton::RadioButton(const int myXStart, const int myYStart, const unsigned int myBorderColor, const unsigned int myFillColor)
    : radioButton(myXStart, myYStart, 10, myBorderColor, myFillColor), savedFillColor(myFillColor), buttonState(false)
{

}

void RadioButton::setCenter(const int myXStart, const int myStart)
{
    radioButton.setCenter(myXStart, myStart);
}

void RadioButton::setBorderColor(const unsigned int myBorderColor)
{
    radioButton.setBorderColor(myBorderColor);
}

void RadioButton::setFillColor(const unsigned int myFillColor)
{
    radioButton.setFillColor(myFillColor);
    savedFillColor = myFillColor;
}

const int RadioButton::getXStart()
{
    return radioButton.getXCoord();
}

const int RadioButton::getYStart()
{
    return radioButton.getYCoord();
}

const unsigned int RadioButton::getBorderColor()
{
    return radioButton.getBorderColor();
}

const unsigned int RadioButton::getFillColor()
{
    return savedFillColor;
}

bool RadioButton::isButtonPressed(const int xInput, const int yInput)
{
    // Button is pressed if the input falls within the boundaries of the button
    return (pow(xInput - radioButton.getXCoord(),2) + pow(yInput - radioButton.getYCoord(),2) <= pow(radioButton.getRadius(), 2));
}

void RadioButton::draw()
{
    if (buttonState) {
        radioButton.draw();
        radioButton.setFillColor(savedFillColor);
        radioButton.fill();
    } else {
        radioButton.draw();
        radioButton.setFillColor(0x0000);
        radioButton.fill();
    }
}

void RadioButton::resetButtonState()
{
    buttonState = !buttonState;
    draw();
}

bool RadioButton::getButtonState()
{
    return buttonState;
}

void RadioButton::setButtonState(bool newValue)
{
    buttonState = newValue;
}


