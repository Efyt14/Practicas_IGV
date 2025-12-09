#ifndef __CGVPOINT3D
#define __CGVPOINT3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif   // defined(__APPLE__) && defined(__MACH__)

#define CGV_EPSILON 0.000001 ///< Constant for comparisons with 0

#ifndef __ENUM_XYZ
#define __ENUM_XYZ

/**
* Labels for point/vector coordinates
*/
enum Coordinates
{
    X ///< X Coordinate
, Y ///< Y Coordinate
, Z ///< Z Coordinate
};

#endif // __ENUM_XYZ

/**
* Objects of this class represent points and vectors in 3D
*/
class cgvPoint3D {
private:
    double c[3] = {0,0,0}; ///< Components x, y, z of the point or vector

public:
    // Constructors
    /// Default constructor
    cgvPoint3D() = default;
    cgvPoint3D ( const double &x, const double &y, const double &z );

    // Copy constructor
    cgvPoint3D ( const cgvPoint3D &p );

    // Assignment operator
    cgvPoint3D &operator= ( const cgvPoint3D &p );

    /// Destroyer
    ~cgvPoint3D () = default;
    double &operator[] ( const unsigned char idx );
    double operator[] ( const unsigned char idx ) const;
    bool operator== ( const cgvPoint3D &p );
    bool operator!= ( const cgvPoint3D &p );
    void set ( const double &x, const double &y, const double &z );
    float *cloneToFloatArray () const; //Returns the point in a float array
};

/**
* Accessing a point/vector coordinate
* @param idx Coordinate to access (0, 1, or 2)
* @return The corresponding coordinate
* @pre Assumes the parameter value is correct
*/
inline double &cgvPoint3D::operator[] ( const unsigned char idx )
{  return c[idx];
}

/**
* Accessing a point/vector coordinate
* @param idx Coordinate to access (0, 1, or 2)
* @return The corresponding coordinate
* @pre Assumes the parameter value is correct
*/
inline double cgvPoint3D::operator[] ( const unsigned char idx ) const
{  return c[idx];
}
#endif   // __CGVPOINT3D
