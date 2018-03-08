/******************************************************************************/
/*!
\file   Point.cpp
\author Robb Cutrell
\par    email: r.cutrell\@digipen.edu
\par    DigiPen login: r.cutrell
\par    Course: CS170
\par    Section: B
\par    assignment 3
\date   03/01/2018
\brief   
    This file contains the implementation of the following functions for the 
    Point assignment.
      
    Functions include:
    
        +Point(double x, double y);
        +Point();
        +const Point operator+(const Point& rhs) const;
        +const Point operator+(const double factor) const;
        +const Point operator-(const double factor) const;
        +const Point operator*(const double factor) const;
        +const Point operator%(const double degrees) const;
        +double operator-(const Point& rhs) const;
        +const Point operator^(const Point& rhs) const;
        +Point& operator+=(const Point& rhs);
        +Point& operator+=(const double factor);
        +Point& operator++();
        +Point operator++(int);
        +Point& operator--();
        +Point operator--(int);
        +Point operator-(); 
        +friend std::ostream& operator<<(std::ostream& os, const Point& rhs);
        +friend std::istream& operator>>(std::istream& is, Point& rhs);
        +double DegreesToRadians(double degrees) const;
        +double RadiansToDegrees(double radians) const;
        +const Point operator+(const double factor, const Point &pt);
        +const Point operator*(const double factor, const Point &pt);
    
    
    
  Hours spent on this assignment: 4.5 hours

  Specific portions that gave you the most trouble:
  
    Figuring when and why to use const in the various overloaded functions

*/
/******************************************************************************/
#include "Point.h"  // Point members
#include <cmath>    // sqrt, atan, sin, cos

namespace CS170
{
/*!< PI value of pie */
const double PI = 3.1415926535897; //value for pi, given by Mead
/*!< EPSILON rounding error margin to avoid -0 */
const double EPSILON = 0.00001;    //rounding margin to avoid -0, given by Mead

///////////////////////////////////////////////////////////////////////////////
// private member functions 

/******************************************************************************/
/*!
      \brief
        Converts degrees into radians
      
      \param degrees
        Given degree value
        
      \return double
        returns value in radians
      
*/
/******************************************************************************/
double Point::DegreesToRadians(double degrees) const
{
  return (degrees * PI / 180.0); //degree to radian formula
}

/******************************************************************************/
/*!
      \brief
        Converts radians to degrees
      
      \param radians
        Given radian value
        
      \return double
        returns value in degrees
      
*/
/******************************************************************************/
double Point::RadiansToDegrees(double radians) const
{
  return (radians * 180.0 / PI); //radians to degree formula
}


///////////////////////////////////////////////////////////////////////////////
// 16 public member functions (2 constructors, 14 operators)

/******************************************************************************/
/*!
      \brief
        Constructor that takes two double parameters and creates a Point
      
      \param x
        position for the x coordinate of the Point
        
      \param y
        position for the y coordinate of the Point
      
*/
/******************************************************************************/
Point::Point(double x, double y)
{
  x_ = x; //assigns the given x value to the x_ value of the point object
  y_ = y; //assigns the given y value to the y_ value of the point object
}

/******************************************************************************/
/*!
      \brief
        Default Constructor that creates a Point at origin
      
*/
/******************************************************************************/
Point::Point()
{
  x_ = 0.0f; //sets the X coordinate of the object to 0
  y_ = 0.0f; //sets the y coordinate of the object to 0
}

/******************************************************************************/
/*!
      \brief
        binary + overload operate to add together a point and a point
      
      \param rhs
        reference of a Point on rhs to add to lhs
        
      \return Point
        a point that is the sum of both points
      
*/
/******************************************************************************/
const Point Point::operator+(const Point& rhs) const
{
  //create a new point with the sum of the x-cords and y-cords
  Point newPt = Point(x_ + rhs.x_, y_ + rhs.y_);
  return newPt;
}

/******************************************************************************/
/*!
      \brief
        binary + overload operate to add together a point and a point
      
      \param factor
        factor to add to both x and y of lhs
        
      \return Point
        a point that is the sum of the point and factor
      
*/
/******************************************************************************/
const Point Point::operator+(const double factor) const
{
  //new point with the factor added to both x and y of lhs
  Point newPt = Point(x_ + factor, y_ + factor);
  return newPt;
}

/******************************************************************************/
/*!
      \brief
        binary - overload operate to subtract a factor from a point
      
      \param factor
        subtracts factor value from both x and y of lhs
        
      \return Point
        difference between a point and the factor
      
*/
/******************************************************************************/
const Point Point::operator-(const double factor) const
{
  //new point with the factor subtracted from both x and y of lhs
  Point newPt = Point(x_ - factor, y_ - factor);
  return newPt;
}

/******************************************************************************/
/*!
      \brief
        binary * overload operate to scale a point by a factor
      
      \param factor
        the factor to scale both x and y by on the lhs
        
      \return Point
        a point scaled by the factor
      
*/
/******************************************************************************/
const Point Point::operator*(const double factor) const
{
  //new point with the x and y values scaled by factor
  Point newPt = Point(x_ * factor, y_ * factor);
  return newPt;
}

/******************************************************************************/
/*!
      \brief
        binary % overload operator to rotate a point by a given degree
      
      \param degrees
        the degrees to rotate the point by
        
      \return Point
        a point rotated by the given degrees
      
*/
/******************************************************************************/
const Point Point::operator%(const double degrees) const
{
  Point newPt = Point(
                      (cos(DegreesToRadians(degrees)) * x_) + //the new x cord
                      (-sin(DegreesToRadians(degrees)) * y_), //the new x cord
                      (sin(DegreesToRadians(degrees)) * x_ +  //the new y cord
                      (cos(DegreesToRadians(degrees)) * y_))  //the new y cord
                      );
                      
  //if the x value is within the rounding error range, set it to 0.0
  if (newPt.x_ > -EPSILON && newPt.x_ < EPSILON)
  {
    newPt.x_ = 0.0;
  }
  
  //if the y value is within the rounding error range, set it to 0.0
  if (newPt.y_ > -EPSILON && newPt.y_ < EPSILON)
  {
    newPt.y_ = 0.0;
  }
  return newPt;
}

/******************************************************************************/
/*!
      \brief
        binary - overload operator to find the distance between two points
      
      \param rhs
        the second point to calculate distance between
        
      \return double
        the distance between two points
      
*/
/******************************************************************************/
double Point::operator-(const Point& rhs) const
{
  double xDistance = (x_ - rhs.x_) * (x_ - rhs.x_); //square of the diff in x
  double yDistance = (y_ - rhs.y_) * (y_ - rhs.y_); //square of the diff in y
  double tDistance = sqrt(xDistance + yDistance);   //distance of the two pts
  
  return tDistance;
}

/******************************************************************************/
/*!
      \brief
        binary ^ overload operator find the midpoint of two points
      
      \param rhs
        second point to use to find the midpoint.
        
      \return Point
        the midpoint between two points
      
*/
/******************************************************************************/
const Point Point::operator^(const Point& rhs) const
{
  double midXPt = ((x_ + rhs.x_) / 2); //x mid point value
  double midYPt = ((y_ + rhs.y_) / 2); //y mid point value
  Point newPt = Point(midXPt, midYPt); //create a new point at midpoint
  
  return newPt;
}

/******************************************************************************/
/*!
      \brief
        binary += overload operator to add a point to the original point
      
      \param rhs
        point to be added to the original point
        
      \return Point
        the original point added by the given point
      
*/
/******************************************************************************/
Point& Point::operator+=(const Point& rhs)
{
  x_ += rhs.x_; //second point's x value added to original point's x
  y_ += rhs.y_; //second point's y value added to original point's y
  
  return *this; //returns the new 'original' point
}

/******************************************************************************/
/*!
      \brief
        binary += overload operator to add a factor to the original point
      
      \param factor
        factor to be added to the original point
      
      \return Point
        the original point added by a factor
      
*/
/******************************************************************************/
Point& Point::operator+=(const double factor)
{
  x_ += factor; //factor added to the original x value
  y_ += factor; //factor added to the original y value
  
  return *this; //returns the new 'original' point
}

/******************************************************************************/
/*!
      \brief
        unary ++ pre-inc overload operator to increase pts values by 1 each
        
      \return Point
        a point's values pre-inc by 1
      
*/
/******************************************************************************/
Point& Point::operator++()
{
  ++x_;         //increases point's x value immediately by 1
  ++y_;         //increases point's y value immediately by 1
  
  return *this; // returns new point values
}

/******************************************************************************/
/*!
      \brief
        unary ++ post-inc overload operator to increase pts values by 1 each
        
      \return Point
        a point's values original value before being incremented by 1
      
*/
/******************************************************************************/
Point Point::operator++(int)
{
  Point oldPt = Point(x_, y_); //stores old value
  x_++;                        //increases point's x value by 1
  y_++;                        //increases point's y value by 1
  
  return oldPt;                //returns old point
}

/******************************************************************************/
/*!
      \brief
        unary -- pre-dec overload operator to decrease pts values by 1 each
        
      \return Point
        a point's values pre-dec by 1
      
*/
/******************************************************************************/
Point& Point::operator--()
{
  --x_;         //decreases point's x value immediately by 1
  --y_;         //decreases point's y value immediately by 1
  
  return *this; // return new point
}

/******************************************************************************/
/*!
      \brief
        unary -- post-dec overload operator to increase pts values by 1 each
        
      \return Point
        a point's values original value before being decremented by 1
*/
/******************************************************************************/
Point Point::operator--(int)
{
  Point oldPt = Point(x_, y_); //stores old value
  x_--;                        //decreases point's x value by 1
  y_--;                        //decreases point's y value by 1
  
  return oldPt;                //returns old point
}

/******************************************************************************/
/*!
      \brief
        unary - overload operator to negate a point
        
      \return Point
        a point with the negative values of the supplied point
      
*/
/******************************************************************************/
Point Point::operator-()
{ 
  Point newPt = Point(-x_, -y_); //makes new point with the neg of both values
  return newPt;
}

///////////////////////////////////////////////////////////////////////////////
// 2 friend functions (operators)

/******************************************************************************/
/*!
      \brief
        overloads << operator to print output to screen
        
      \param os
        the std output stream
        
      \param rhs
        point with the value's being printed
      
*/
/******************************************************************************/
std::ostream& operator<<(std::ostream& os, const Point& rhs)
{
  os << "(" << rhs.x_ << ", " << rhs.y_ << ")"; //prints and formats pt cords
  return os;
}

/******************************************************************************/
/*!
      \brief
        overloads >> operator to recieve input from user
        
      \param is
        std input stream taking two numbers and storing them into x and y.
        values are seperated by a white space.
        
      \param rhs
        the point that the inputted values are being stored in
      
*/
/******************************************************************************/
std::istream& operator>>(std::istream& is, Point& rhs)
{
  is >> rhs.x_; //stores the first number into x_
  is >> rhs.y_; //stores the second number into y_
  return is;
}

///////////////////////////////////////////////////////////////////////////////
// 2 non-members, non-friends (operators)

/******************************************************************************/
/*!
      \brief
        binary + overload operator that takes a factor and adds it to a Point
        
      \param factor
        The factor to be added to a point
        
      \param &pt
        the point being added too
      
*/
/******************************************************************************/
const Point operator+(const double factor, const Point &pt)
{
  Point newPt = (pt + factor); //adds the factor to the point
  return newPt;
}

/******************************************************************************/
/*!
      \brief
        binary * overload operator that takes a factor and scales a Point by it
        
      \param factor
        The factor to be scaled by
        
      \param &pt
        the point being scaled
      
*/
/******************************************************************************/
const Point operator*(const double factor, const Point &pt)
{
  Point newPt = (pt * factor); //scales the point by the factor
  return newPt;
}


} // namespace CS170



