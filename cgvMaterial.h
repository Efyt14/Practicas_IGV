#ifndef __CGVMATERIAL
#define __CGVMATERIAL

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif   // defined(__APPLE__) && defined(__MACH__)

#include "cgvColor.h"
/**
* Objects of this class represent material properties
*/
class cgvMaterial
{
private:
    // Attributes
    cgvColor Ka = { 0, 0, 0 }; ///< Ambient reflection coefficient
    cgvColor Kd = { 0, 0, 0 }; ///< Diffuse reflection coefficient
    cgvColor Ks = { 0, 0, 0 }; ///< Specular reflection coefficient
    double Ns = 0; ///< Phong exponent

    // Methods
public:
    // Default constructors and destructor
    // Default constructor
    cgvMaterial() = default;

    // Destructor
    ~cgvMaterial() = default;

    // Other constructors
    cgvMaterial(const cgvMaterial &p); // Copy constructors
    cgvMaterial(cgvColor _Ka, cgvColor _Kd, cgvColor _Ks, double _Ns);

    // Methods
    void apply();
    void set(cgvColor _Ka, cgvColor _Kd, cgvColor _Ks, double _Ns);
    void incrementDiffuse(float quantity) { Kd[0] += quantity; }
    void incrementSpecular(float quantity) { Ks[0] += quantity; }
    void incrementExpPhong(float quantity) { Ns += quantity; }
};

#endif   // __CGVMATERIAL

