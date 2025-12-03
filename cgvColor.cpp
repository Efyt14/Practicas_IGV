#include "cgvColor.h"
// Constructors

/**
* RGB parameterized constructor. The alpha component is set to 0
* @param r Red component of the new color (value in the range [0,1])
* @param g Green component of the new color (value in the range [0,1])
* @param b Blue component of the new color (value in the range [0,1])
* @pre Assumes that the parameters have valid values
*/
cgvColor::cgvColor ( const double r, const double g, const double b ):
color { r, g, b, 0 }
{}

/**
* Parameterized RGBA constructor
* @param r Red component of the new color (value in the range [0,1])
* @param g Green component of the new color (value in the range [0,1])
* @param b Blue component of the new color (value in the range [0,1])
* @param a Alpha component (transparency) of the new color (value in the range [0,1])
* @pre Assumes that the parameters have valid values
*/
cgvColor::cgvColor ( const double r, const double g, const double b
                     , const double a ): color { r, g, b, a }
{}

/**
 * Copy builder
 * @param p Color from which values ​​are copied
 */
cgvColor::cgvColor ( const cgvColor &p ): color { p.color[R], p.color[G]
                                                , p.color[B], p.color[A] }
{}

// Public Methods

/**
* Access to a color component
* @param idx Value of the component to query (R, G, B, A)
* @return A reference to the requested component
*/
double &cgvColor::operator[] ( const unsigned char idx )
{  return color[idx];
}

/**
* Access to a color component
* @param idx Value of the component to query (R, G, B, A)
* @return A copy of the requested component value
*/
double cgvColor::operator[] ( const unsigned char idx ) const
{  return color[idx];
}

/**
* Calls the corresponding OpenGL function to apply the color
*/
void cgvColor::apply ()
{
    glColor4dv ( color );
}

/**
* Allocates a block of memory with the color in float format
* @return The memory address of the allocated block
* @note At some point in the program code, it is necessary to free this block
*/
float *cgvColor::cloneToFloatArray () const
{
    float *res = new float[4] { (float) color[0], (float) color[1], (float) color[2], (float) color[3] };
    return res;
}