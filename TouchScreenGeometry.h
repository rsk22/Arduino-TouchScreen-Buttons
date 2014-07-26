/*! \mainpage Main Page
 *
 * \section intro_sec Introduction
 * \brief Arduino library for creating geometries shapes for the Seeed Studio TFT touch screen (Version 1).
 * \author Richard Kirkpatrick
 * \date 17 July 2014
 * \copyright GNU Public License.
 *
 * This is the Arduino library for creating geometries shapes for the Seeed Studio TFT touch screen (Version 1).
 * The user can create polygons, rectangles, triangle and circles.
 * See the Wiki documentation page for more info!
 *
 */

#ifndef TouchScreenGeometry_h
#define TouchScreenGeometry_h

#include "Arduino.h"


/*
----------------------------------------------------------------
                          Point2D Class
              NOTE: Consider adding draw method to this
----------------------------------------------------------------
*/
/*!
@class Point2D
@brief Abstract data type for representing a point in the 2D cartesian plane.
*/
class Point2D {
 public:
    ///@brief Default constructor for the Point2D class
    Point2D();

    /*!
    @brief Parameter constructor for the Point2D class
    @param  myX  The x-coordinate of the point
    @param  myY   The y-coordinate of the point
    */
    Point2D(const int myX, const int myY);

    /*!
    @brief Copy constructor for the Point2D class.
    @param  otherPoint  The other Point2D instance that is to be copied.
    */
    Point2D(Point2D& otherPoint);

    ///@brief Getter method for the x coordinate
    const int getX();

    ///@brief Getter method for the y coordinate
    const int getY();

    ///@brief Setter method for the x coordinate
    void setX(const int myX);

    ///@brief Setter method for the y coordinate
    void setY(const int myY);

private:
    int x, y; // x and y coordinates of the Point2D instance
};

/*
----------------------------------------------------------------
                         Point2DArray Class
                NOTE: Consider adding draw method to this
----------------------------------------------------------------
*/
/*!
 @class Point2DArray
 @brief Abstract data class for arrays of Point2D objects.
*/
class Point2DArray {
 public:
    ///@brief Default constructor for the Point2DArray class
    Point2DArray();

    ///@brief Parameter constructor for the Point2DArray class
    Point2DArray(const Point2D points[], const int size);

    /*!
    @brief Copy constructor for the Point2DArray class
    @param  other   The other Point2DArray instance that is to be copied.
    */
    Point2DArray(const Point2DArray &other);

    ///@brief Destructor for the Point2DArray class
    ~Point2DArray();

    ///@brief Removes everything from the Point2DArray instance and sets it size to zero.
    void clear();

    ///@brief Getter method for the size of the Point2DArray instance
    int getSize();

    /*!
    @brief Adds a Point2D instance to the end of the array
    @param  point The Point2D instance that is to be added to the array.
    */
    void pushBack(const Point2D &point);

    /*!
    @brief Changes the value of the Point2D instance in the Point2D array.
    @param  pos     The index of the Point2D instance.
    @param  point     The new value of the Point2D instance.
    */
    void setPoint(const int pos, const Point2D &point);

    /*!
    @brief Inserts a Point2D instance at the designated position in the Point2DArray instance, and
           then shifts the remaining elements to the right.
    @param  pos     The index location where the Point2D instance will be added.
    @param  point   The Point2D instance that is to be added to the Point2DArray instance.
    */
    void insert(const int pos, const Point2D &point);

    /*!
    @brief Removes the Point2D instance at the designated index location, and shifts the remaining
           elements to the left.
    @param  pos     The index location of the Point2D instance that will be removed.
    */
    void remove(const int pos);

    /*!
    @brief Returns a pointer to the Point2D instance at the designated location.
    @param  pos     The index location of the Point2D instance.
    */
    Point2D *get(const int pos);

    /*!
    @brief Returns a pointer to the Point2D instance at the designated location.
    @param  pos     The index location of the Point2D instance.
    */
    const Point2D *get(const int pos) const;

 private:
    /*!
    @brief Resizes the Point2DArray
    @param  The size of the array.
    */
    void resize(int size);

    int size; // Size of the array
    Point2D *points;
};

/*
----------------------------------------------------------------
                    Polygon Base Class
----------------------------------------------------------------
*/
/*!
@class Polygon
@brief Base class for drawing Polygon objects to the TFT touch screen.
*/
class Polygon {
 public:
    /*!
    @brief Constructor for the Polygon class
    @param &pa  The Point2DArray that defines the vertices of the Polygon.
    @param  myBorderColor   The border color of the rectangle.  Default is WHITE.
    @param  myFillColor     The fill color of the rectangle.  Default is BLACK.
    */
    Polygon(const Point2DArray &pa, const unsigned int myBorderColor = 0xffff, const unsigned int myFillColor = 0x0000);

    /*!
    @brief Parameter constructor for the the Polygon class
    @param  points[]    Array of Point2D objects that define the vertices of the Polygon.
    @param  numPoints   The number of vertices of the Polygon.
    @param  myBorderColor   The border color of the rectangle.  Default is WHITE.
    @param  myFillColor     The fill color of the rectangle.  Default is BLACK.
    */
    Polygon(const Point2D points[], const int numPoints, const unsigned int myBorderColor = 0xffff, const unsigned int myFillColor = 0x0000);

    ///@brief Destructor for the Polygon class. Decrements numPolygons and erases the drawn Polygon.
    ~Polygon() { --numPolygons; }

    ///@brief Getter method for the number of polygons that have been created.
    static int getNumPolygons() { return numPolygons; }

    ///@brief Gets the number of sides of the Polygon instance.
    int getNumSides() { return points.getSize(); }

    ///@brief Returns an unmodifiable pointer to the PointArray of the Polygon
    const Point2DArray *getPoints() const;

    /*!
    @brief Sets the border color of the geometry.
    @param myBorderColor The border color of the geometry.
    */
    void setBorderColor(unsigned int myBorderColor = 0xffff);

    /*!
    @brief Sets the fill color of the geometry.  NOTE: This needs upgraded in future.
    @param myFillColor The fill color of the geometry.
    */
    void setFillColor(unsigned int = 0x0000);

    /*!
    @brief Gets the border color of the geometry.
    @return Border color of the geometry.
    */
    const unsigned int getBorderColor();

    /*!
    @brief Gets the fill color of the geometry.
    @return Fill color of the geometry.
    */
    const unsigned int getFillColor();

    ///@brief Draws the Polygon using the TFT library
    void draw();

    ///@brief Fills the Polygon using the TFT library
    void fill();

    ///@brief Erases the Polygon
    void erase();

  protected:
    static int numPolygons; /// Keeps track of the number of Polygon objects
    Point2DArray points; /// Vertices for the Polygon instance
    unsigned int borderColor; /// Border color of the Polygon
    unsigned int fillColor; /// Fill color of the Polygon.  Currently not being used.  Future upgrade will include use of this.
};


/*
----------------------------------------------------------------
				  Rectangle Subclass
----------------------------------------------------------------
*/

///@class Rectangle
///@brief Class for handling the geometry rendering and functions for the TFT Touch Screen
class Rectangle : public Polygon {
 public:
    ///@brief Default constructor for the Rectangle class.
    Rectangle();

    /*!
    @brief Parameter constructor for the rectangle subclass.
    @param upperLeft    The upper left vertice of the rectangle.
    @param lowerRight   The lower right vertice of the rectangle.
    @param myBorderColor The border color of the rectangle.
    @param myFillColor The fill color of the rectangle.
    */
    Rectangle(Point2D &upperLeft, Point2D &lowerRight, const unsigned int myBorderColor = 0xffff, const unsigned int myFillColor = 0x0000);

    /*!
    @brief Parameter constructor for the rectangle subclass.
    @param myXStart The starting x-coordinate of the rectangle.
    @param myYStart The starting y-coordinate of the rectangle.
    @param myWidth The width of the rectangle.
    @param myHeight The height of the rectangle.
    @param myBorderColor The border color of the rectangle.
    @param myFillColor The fill color of the rectangle.
    */
    Rectangle(const int myXStart, const int myYStart, const int myWidth, const int myHeight, const unsigned int myBorderColor = 0xffff, const unsigned int myFillColor = 0x0000);

    /*!
    @brief Sets the upper left coordinate of the rectangle while retaining its original height and width
    @param  myXStart    The left bound x-coordinate of the rectangle.
    @param  myYStart    The upper bound y-coodinate of the rectangle.
    */
    void setUpperLeft(const int myXStart, const int myYStart);

    /*!
    @brief Sets the values of the rectangle instance.
    @param myXStart The starting x-coordinate of the rectangle.
    @param myYStart The starting y-coordinate of the rectangle.
    @param myWidth The width of the rectangle.
    @param myHeight The height of the rectangle.
    */
    void setValues(const int myXStart, const int myYStart, const int myWidth, const int myHeight);

    ///@brief Returns the left bound x-coordinate of the rectangle.
    const int getXStart();

    ///@brief Returns the upper bound y-coordinate of the rectangle
    const int getYStart();

    ///@brief Returns the right bound x-coordinate of the rectangle
    const int getXEnd();

    ///@brief Returns the lower bound x-coordinate of the rectangle
    const int getYEnd();

    ///@brief Returns the width of the rectangle
    const int getWidth();

    ///@brief Returns the height of the rectangle
    const int getHeight();

    ///@brief Fills the Rectangle using the TFT library
    void fill();

    ///@brief Erases the Circle
    void erase();

    /*!
    @brief Sets the size of the rectangle.  Does no redraw the rectangle.
    @param  myWidth   The width of the rectangle.
    @param  myHeight  The height of the rectangle.
    */
    void setSize(const int myWidth, const int myHeight);

    /*!
    @brief Moves the rectangle at the specified amount.
           Assumes the specified amount is not outside the screen boundaries.
    @param  dx The amount in the +x-direction (left to right) to move the rectangle.
    @param  dy The amount in the +y-direction (up to down) to move the rectangle.
    */
    void move(const int dx, const int dy);

    /*!
    @brief Resizes the rectangle based on the factor.
           Assumes the scaling factor is neither too small or too big.
    @param  factor The amount the rectangle is to be resized.
    */
    void scale(const float factor);
};

/*
----------------------------------------------------------------
                         Triangle
----------------------------------------------------------------
*/
///@class Triangle
///@brief Class for drawing Triangles to the TFT touch screen
class Triangle : public Polygon {
 public:
    /*!
    @brief Parameter constructor for the Triangle class.
    @param  a   The 1st vertice of the triangle.
    @param  b   The 2nd vertice of the triangle.
    @param  c   The 3rd vertice of the triangle.
    @param  myBorderColor   The border color of the triangle.  Default is white.
    @param myFillColor The fill color of the rectangle.  Default is black.
    */
    Triangle(const Point2D &a, const Point2D &b, const Point2D &c, const unsigned int myBorderColor = 0xffff, const unsigned int myFillColor = 0x0000);
};

/*
----------------------------------------------------------------
				  Ellipse Class
----------------------------------------------------------------
*/
/*!
@class Ellipse
@brief Base class for drawing Ellipses to the touch screen
*/
class Ellipse {
 public:
    /*!
    @brief Parameter constructor for the Ellipse class.
    @param myCenter  The coordinates of the Ellipse's center.
    @param myWidth  The width of the Ellipse.
    @param myHeight The height of the Ellipse.
    @param myBorderColor The border color of the Ellipse.  Default is white.
    @param myFillColor The fill color of the Ellipse.  Default is black.
    */
    Ellipse(const Point2D &myCenter, const int myWidth, const int myHeight, const unsigned int myBorderColor = 0xffff, const unsigned int myFillColor = 0x0000);

    /*!
    @brief Parameter constructor for the Ellipse class.
    @param myXStart     The x-coordinate of the Ellipse's center.
    @param myYStart     The y-coordinate of the Ellipse's center.
    @param myWidth  The width of the Ellipse.
    @param myHeight The height of the Ellipse.
    @param myBorderColor    The border color of the Ellipse.  Default is white.
    @param myFillColor      The fill color of the Ellipse.  Default is black.
    */
    Ellipse(const int myXStart, const int myYStart, const int myWidth, const int myHeight, const unsigned int myBorderColor = 0xffff, const unsigned int myFillColor = 0x0000);

    /*!
    @brief Resets the center for the Ellipse
    @param myX     The new center x-coordinate for the Ellipse.
    @param myY     The new center y-coordinate for the Ellipse.
    */
    void setCenter(const int myX, const int myY);

    /*!
    @brief Sets the width of the Ellipse.  Method is private to ensure subclasses do not inherit method.
    @param myWidth  The width of the Ellipse.
    */
    void setWidth(const int myWidth);

    /*!
    @brief Sets the height of the Ellipse.  Method is private to ensure subclasses do not inherit method.
    @param myHeight  The height of the Ellipse.
    */
    void setHeight(const int myHeight);

    /*!
    @brief Sets the border color of the Ellipse.
    @param myBorderColor    The border color of the Ellipse.  Default is white.
    */
    void setBorderColor(unsigned int myBorderColor = 0xffff);

    /*!
    @brief Sets the fill color of the Ellipse.
    @param  myFillColor     The fill color of the Ellipse. Default is black.
    */
    void setFillColor(unsigned int = 0x0000);

    ///@brief Gets the x-coordinate of the Ellipse's center
    const int getXCoord();

    ///@brief Gets the y-coordinate of the Ellipse's center
    const int getYCoord();

    ///@brief Gets the width of the Ellipse. Method is private to ensure subclasses do not inherit method.
    const int getWidth();

    ///@brief Gets the height of the Ellipse. Method is private to ensure subclasses do not inherit method.
    const int getHeight();

    ///@brief Gets the border color of the Ellipse.
    const unsigned int getBorderColor();

    /*!
    @brief Gets the fill color of the Ellipse.
    @return Fill color of the Ellipse.
    */
    const unsigned int getFillColor();

    ///@brief Uses the Seeed Studio TFT library to draw the Ellipse.
    void draw();

    ///@brief Uses the Seeed Studio TFT library to fill the Ellipse.
    void fill();

    ///@brief Erases the Ellipse
    void erase();

    /*!
    @brief Moves the Ellipse at the specified amount.
           Assumes the specified amount is not outside the screen boundaries.
    @param dx   The amount in the +x-direction (left to right) to move the Ellipse.
    @param dy   The amount in the +y-direction (up to down) to move the Ellipse.
    @param fillEllipse  Does not fill the Ellipse if set to false.  Otherwise, it fills.
                        Note that filling any shapes result in performance decreases.
    */
    void move(const int dx, const int dy, bool fillEllipse = false);

    /*!
    @brief Resizes the Ellipse based on the factor.
           Assumes the scaling factor is neither too small or too big.
    @param factor   The amount the Ellipse is to be resized.
    @param fillEllipse  Does not fill the Ellipse if set to false.  Otherwise, it fills.
                        Note that filling any shapes result in performance decreases.
    */
    void scale(const float factor, bool fillEllipse = false);

 protected:
    Point2D center; // The center of the Ellipse.
    unsigned int borderColor;
    unsigned int fillColor;

 private:
    int width, height; /// Members are private to ensure the Circle class does not have unneccesary dupliate values
};

/*
----------------------------------------------------------------
				  Circle Class
----------------------------------------------------------------
*/

///@class Circle
///@brief The class for drawing circles to the TFT touch screen.
class Circle : public Ellipse {
 public:
    /*!
    @brief Parameter constructor for the circle class.
    @param myCenter  The coordinates of the circle's center.
    @param myRadius   The radius of the circle.
    @param myBorderColor    The border color of the circle.  Default is white.
    @param myFillColor  The fill color of the circle.  Default is black.
    */
    Circle(const Point2D &myCenter, const int myRadius, const unsigned int myBorderColor = 0xffff, const unsigned int myFillColor = 0x0000);

    /*!
    @brief Parameter constructor for the circle class.
    @param myXStart     The x-coordinate of the circle's center.
    @param myYStart     The y-coordinate of the circle's center.
    @param myRadius     The radius of the circle.
    @param myBorderColor    The border color of the circle.  Default is white.
    @param myFillColor  The fill color of the circle.  Default is black.
    */
    Circle(const int myXStart, const int myYStart, const int myRadius, const unsigned int myBorderColor = 0xffff, const unsigned int myFillColor = 0x0000);

    /*!
    @brief Sets the radius of the circle.  Does NOT redraw the circle.
    @param myRadius     The radius of the circle.
    */
    void setRadius(const int myRadius);

    ///@brief Gets the radius of the circle.
    const int getRadius();

    ///@brief Uses the Seeed Studio TFT library to draw the circle.
    void draw();

    ///@brief Uses the Seeed Studio TFT library to fill the circle.
    void fill();

    ///@brief Erases the Circle
    void erase();

    /*!
    @brief Moves the circle at the specified amount.
           Assumes the specified amount is not outside the screen boundaries.
    @param dx   The amount in the +x-direction (left to right) to move the circle.
    @param dy   The amount in the +y-direction (up to down) to move the circle.
    @param fillCircle  Does not fill the Circle if set to false.  Otherwise, it fills.
                        Note that filling any shapes result in performance decreases.
    */
    void move(const int dx, const int dy, bool fillCircle = false);

    /*!
    @brief Resizes the circle based on the factor.
           Assumes the scaling factor is neither too small or too big.
    @param factor   The amount the circle is to be resized.
    @param fillCircle  Does not fill the Circle if set to false.  Otherwise, it fills.
                    Note that filling any shapes result in performance decreases.
    */
    void scale(const float factor, bool fillCircle = false);

 private:
    int radius;
};

#endif
