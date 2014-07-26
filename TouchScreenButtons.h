/*! \mainpage Main Page
 *
 * \section intro_sec Introduction
 * \brief Arduino Library for creating buttons for the Seeed Studio TFT touch screen (Version 1)
 * \author Richard Kirkpatrick
 * \date 19 June 2014
 * \copyright GNU Public License.

 * See the Wiki documentation page for more info!
 *
 */


#ifndef TOUCHSCREENBUTTONS_H_INCLUDED
#define TOUCHSCREENBUTTONS_H_INCLUDED

#include "Arduino.h"
#include <TouchScreenGeometry.h>
#include <TouchSceenStrings.h>

///@class Button
///@brief Abstract class for drawing rectangular buttons to the Seeed Studio TFT touch screen.
class Button {
public:
    ///@brief Default constructor for the Button class
    Button();

    /**
    @brief Parameter constructor for the button class.
    @param myXStart The starting x-coordinate of the button.
    @param myYStart The starting y-coordinate of the button.
    @param myWidth The width of the button.
    @param myHeight The height of the button.
    @param myBorderColor The border color of the button. Default color is white.
    @param myFillColor The fill color of the button. Default color is black.
    */
    Button(const int myXStart, const int myYStart, const int myWidth, const int myHeight, unsigned int myBorderColor, unsigned int myFillColor);

    /**
    @brief Sets the values of the button instance.
    @param myXStart The starting x-coordinate of the button.
    @param myYStart The starting y-coordinate of the button.
    @param myWidth The width of the button.
    @param myHeight The height of the button.
    */
    void setValues(const int myXStart, const int myYStart, const int myWidth, const int myHeight);

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
    @details The default border color is RED and the default fill color is BLACK.  Button's border color and fill color is updated.
             The button is then drawn.  After a 100 ms delay, the button is reset back to its original values.
    @param myBorderColor The border color of the button. Default color is red.
    @param myFillColor The fill color of the button. Default color is black.
    */
    void buttonDisplay(unsigned int myBorderColor = 0xf800, unsigned int myFillColor = 0x0000);

private:
    Rectangle button;
};


/*!
@brief RadioButton
@brief Class for drawing a RadioButton to the Arduino touch screen.
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

    ///@brief Sets the x-coordinate of the RadioButton.
    void setXStart(const int myXStart);

    ///@brief Sets the y-coordinate of the RadioButton.
    void setYStart(const int myYStart);

    ///@brief Sets the border color of the RadioButton.
    void setBorderColor(const unsigned int myBorderColor);

    ///@brief Sets the fill color of the RadioButton.
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

    ///@brief Draws the RadioButton to the screen based on the button's state.
    void draw();

 private:
    Circle radioButton;
    bool buttonState;
};


#endif // TOUCHSCREENBUTTON_H_INCLUDED
