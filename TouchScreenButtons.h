/*! \mainpage Main Page
 *
 * \section intro_sec Introduction
 * \brief Arduino Library for creating buttons (square buttons and radio buttons) for the Seeed Studio TFT touch screen (Version 1)
          See example folder for tutorials.
 * \author Richard Kirkpatrick
 * \date 26 July 2014
 * \copyright GNU Public License.

 * See the Wiki documentation page for more info!
 *
 */


#ifndef TOUCHSCREENBUTTONS_H_INCLUDED
#define TOUCHSCREENBUTTONS_H_INCLUDED

#include "Arduino.h"
#include <TouchScreenGeometry.h>
#include <TouchScreenStrings.h>

///@class Button
///@brief Abstract class for drawing rectangular buttons to the Seeed Studio TFT touch screen.
class Button {
public:
    ///@brief Default constructor for the Button class
    Button();

    /**
    @brief Parameter constructor for the button class.  This constructor assumes the user does not want any button text or that it will be created later.
    @param myXStart The starting x-coordinate of the button.
    @param myYStart The starting y-coordinate of the button.
    @param myWidth The width of the button.
    @param myHeight The height of the button.
    @param myBorderColor The border color of the button. Default color is white.
    @param myFillColor The fill color of the button. Default color is black.
    */
    Button(const int myXStart,
           const int myYStart,
           const int myWidth,
           const int myHeight,
           unsigned int myBorderColor = 0xffff,
           unsigned int myFillColor = 0x0000);

    /**
    @brief Parameter constructor for the button class.  This constructor allows the user to specify the button's text.
    @param myButtonText The text for the button.
    @param myXStart The starting x-coordinate of the button.
    @param myYStart The starting y-coordinate of the button.
    @param myWidth The width of the button.
    @param myHeight The height of the button.
    @param myBorderColor The border color of the button. Default color is white.
    @param myFillColor The fill color of the button. Default color is black.
    @param myTextColor The color of the button's text.  Default is white.
    */
    Button(char* myButtonText,
           const int myXStart,
           const int myYStart,
           const int myWidth,
           const int myHeight,
           unsigned int myBorderColor = 0xffff,
           unsigned int myFillColor = 0x0000,
           unsigned int myTextColor = 0xffff);

    /**
    @brief Sets the values of the button instance.
    @param myXStart The starting x-coordinate of the button.
    @param myYStart The starting y-coordinate of the button.
    @param myWidth The width of the button.
    @param myHeight The height of the button.
    */
    void setValues(const int myXStart, const int myYStart, const int myWidth, const int myHeight);

    /**
    @brief Sets the values for the button's text.
    @param myText   The text for the button.
    @param myXStart The x-coordinate for the text.
    @param myYStart The y-coordinate for the text.
    @param myFontSize The font size for the text.
    @param myTextColor The font color for the text.  Default is white.
    */
    void setTextValues(char* myText, const int myXStart, const int myYStart, const int myFontSize, const unsigned int myTextColor = 0xffff);

    /**
    @brief Sets the text for the button.
    @param myText   The text for the button.
    */
    void setText(char* myText);

    /**
    @brief Sets the coordinates for the text
    @param myXStart The x-coordinate for the text.
    @param myYStart The y-coordinate for the text.
    */
    void setTextCoord(const int myXStart, const int myYStart);

    /**
    @brief Sets the font size for the text.
    @param myFontSize The font size for the text.
    */
    void setFontSize(const int myFontSize);

    /**
    @brief Sets the text color.
    @param myTextColor The font color for the text.
    */
    void setTextColor(const unsigned int myTextColor);

    /**
    @brief Sets the size of the button
    @param myWidth      The width of the button.
    @param myHeight     The height of the button.
    */
    void setSize(const int myWidth, const int myHeight);

    /**
    @brief Sets the border color of the button instance.
    @param myBorderColor The border color of the button instance.
    */
    void setBorderColor(unsigned int myBorderColor);

    /**
    @brief Sets the fill color of the button instance.
    @param myFillColor The fill color of the button instance.
    */
    void setFillColor(unsigned int myFillColor);

    ///@brief Gets the left bound x-coordinate
    const int getXStart();

    ///@brief Gets the upper bound y-coordinate
    const int getYStart();

    ///@brief Gets the right bound x-coordinate
    const int getXEnd();

    ///@brief Gets the lower bound y-coordinate
    const int getYEnd();

    ///@brief Gets the width of the button
    const int getWidth();

    ///@brief Gets the height of the button
    const int getHeight();

    ///@brief Gets the border color of the button
    const unsigned int getBorderColor();

    ///@brief Gets the fill color of the button
    const unsigned int getFillColor();

    ///@brief Gets the button's text
    char* getText();

    ///@brief Gets the x-coordinate for the button's text
    const int getTextXStart();

    ///@brief Gets the y-coordinate for the button's text
    const int getTextYStart();

    ///@brief Gets the font size for the button's text
    const int getFontSize();

    ///@brief Gets the text color for the button's text
    const unsigned int getTextColor();

    /**
    @brief Determines if the button was pressed
    @param xScreen The x-coordinate of the user's input.
    @param yScreen The y-coordinate of the user's input.
    @return Returns True if the user pressed the button within the boundaries.  False otherwise.
    */
    bool isPressed(const int xScreen, const int yScreen);

    ///@brief Draws the button
    void draw();

    ///@brief Fills the button
    void fill();

    /**
    @brief Displays the button when pressed.
    @param myHighlightColor The color that button will display when pressed.  Default is red.
    */
    void buttonDisplay(unsigned int myHighlightColor = 0xf800);

private:
    Rectangle button;
    TouchScreenString buttonText;
};


/*!
@class RadioButton
@brief Class for drawing a radio button to the Arduino touch screen.
*/
class RadioButton {
 public:
    /*!
    @brief Constructor of the RadioButton class.
    @param myXStart     The x-coordinate of the RadioButton.
    @param myYStart     The y-coordinate of the RadioButton.
    @param myBorderColor    The border color of the RadioButton.
    @param myFillColor      The fill color of the RadioButton.
    */
    RadioButton(const int myXStart, const int myYStart, const unsigned int myBorderColor, const unsigned int myFillColor);

    /*!
    @brief Set the xstart and ystart of the RadioButton.
    @param myXStart     The x-coordinate of the RadioButton.
    @param myYStart     The y-coordinate of the RadioButton.
    */
    void setCenter(const int myXStart, const int myYStart);

    /*!
    @brief Sets the border color of the RadioButton.
    @param myBorderColor    The border color of the RadioButton.
    */
    void setBorderColor(const unsigned int myBorderColor);

    /*!
    @brief Sets the fill color of the RadioButton.
    @param myFillColor      The fill color of the RadioButton.
    */
    void setFillColor(const unsigned int myFillColor);

    ///@brief Gets the x-coordinate of the RadioButton.
    const int getXStart();

    ///@brief Gets the y-coordinate of the RadioButton.
    const int getYStart();

    ///@brief Gets the border color of the RadioButton.
    const unsigned int getBorderColor();

    ///@brief Gets the fill color of the RadioButton.
    const unsigned int getFillColor();

    /*!
    @brief Determines if the user's input was within the RadioButton's boundaries.
    @param xInput   The x-coordinate of the user's input.
    @param yInput   The y-coordinate of the user's input.
    @return Returns true if the RadioButton was pressed; false otherwise.
    */
    bool isButtonPressed(const int xInput, const int yInput);

    ///@brief Resets the button's state and then draws it.  If button is true, it is set to false and vice versa.
    void resetButtonState();

    ///@brief Returns the button's current state.
    bool getButtonState();

    ///@brief Sets the buttons state
    void setButtonState(bool newValue);

    ///@brief Draws the RadioButton to the screen based on the button's state.
    void draw();

 private:
    Circle radioButton;
    unsigned int savedFillColor; // Used for saving the fill color
    bool buttonState; // Saves the state of the button (On/Off)
};


#endif // TOUCHSCREENBUTTON_H_INCLUDED
