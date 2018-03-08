/******************************************************************************/
/*!
\file   Point.h
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

////////////////////////////////////////////////////////////////////////////////
#ifndef POINT_H
#define POINT_H
////////////////////////////////////////////////////////////////////////////////


#include <iostream> // istream, ostream

namespace CS170
{
  /******************************************************************************/
  /*!
  \class Point
  \brief  
    Overload various functions to be able to do arithmitic with points

    Operations include:

    - Adding two points or adding a point with a factor
    - Subtracting two points or a point with a factor
    - Scaling a point by a factor
    - Rotating a point
    - Finding midpoint and distances between two points
    - Post/pre inc/dec a point's value
    - Negate a point
    - Print a point's cordinates

  */
  /******************************************************************************/
  class Point
  {
    public:
        // Constructors (2)
        Point(double x, double y);
        Point();

        // Overloaded operators (14 member functions)
        const Point operator+(const Point& rhs) const;
        const Point operator+(const double factor) const;
        const Point operator-(const double factor) const;
        const Point operator*(const double factor) const;
        const Point operator%(const double degrees) const;
        double operator-(const Point& rhs) const;
        const Point operator^(const Point& rhs) const;
        Point& operator+=(const Point& rhs);
        Point& operator+=(const double factor);
        Point& operator++();
        Point operator++(int);
        Point& operator--();
        Point operator--(int);
        Point operator-(); 
        
        // Overloaded operators (2 friend functions)
        friend std::ostream& operator<<(std::ostream& os, const Point& rhs);
        friend std::istream& operator>>(std::istream& is, Point& rhs);
        
    private:
      /*!< x_ x-coordinate of point */
      double x_; // The x-coordinate of a Point
      /*!< y_ y-coordinate of point */
      double y_; // The y-coordinate of a Point

        // Helper functions
      double DegreesToRadians(double degrees) const;
      double RadiansToDegrees(double radians) const;
  };
  
    // Overloaded operators (2 non-member, non-friend functions)
    const Point operator+(const double factor, const Point &pt);
    const Point operator*(const double factor, const Point &pt);
    
} // namespace CS170

#endif
////////////////////////////////////////////////////////////////////////////////
