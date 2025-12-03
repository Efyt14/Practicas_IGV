#ifndef __CGVCOLOR
#define __CGVCOLOR

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif   // defined(__APPLE__) && defined(__MACH__)
/**
* Color components
*/
enum cColor
{
    R ///< Red
    , G ///< Green
    , B ///< Blue
    , A ///< Alpha (transparency)
};
/**
 * Objects in this class represent RGBA colors
 */
class cgvColor
{
protected:
    // attributes
    double color[4] = { 0, 0, 0, 0 }; ///< Components R, G, B, A of the color
    // Methods

public:
    // Default constructors and destructor
    cgvColor () = default;
    ~cgvColor () = default;

    // Other constructors
    cgvColor ( const double r, const double g, const double b );
    cgvColor ( const double r, const double g, const double b, const double a );
    cgvColor ( const cgvColor &p );   //copy

    // Methods
    double &operator[] ( const unsigned char idx );
    double operator[] ( const unsigned char idx ) const;
    void apply();
    float *cloneToFloatArray() const; //Returns the color as a float array.
};
#endif   // __CGVCOLOR
