#ifndef __IGVFUENTELUZ
#define __IGVFUENTELUZ

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif   // defined(__APPLE__) && defined(__MACH__)

#include "cgvPoint3D.h"
#include "cgvColor.h"

/**
* Objects of this class represent light sources
*/
class cgvLightSource
{
    private:
    // Attributes
    unsigned int idLuz = 0; ///< Light identifier (GL_LIGHT0 to GL_LIGHT7)

    cgvPoint3D position = { 0, 0, 0 }; ///< Light position
    cgvColor colorAmbient = { 0, 0, 0 }; ///< Ambient color of the light
    cgvColor colorDiffuse = { 0, 0, 0 }; ///< Diffuse color of the light
    cgvColor colorSpecular = { 0, 0, 0 }; ///< Specular color of the light

    double aten_a0 = 0; ///< Attenuation coefficient a0
    double aten_a1 = 0; ///< Attenuation coefficient a1
    double aten_a2 = 0; ///< Attenuation coefficient a2

    // parameters to define a focus
    cgvPoint3D spotlight_direction = { 0, 0, 0 }; ///< Vector indicating the direction the focus is pointing
    double spotlight_angle = 0; ///< Spotlight beam angle
    double spotlight_exponent = 0; ///< Exponent for calculating spotlight dimming
    bool on = false; ///< Indicates whether the light is on or off

    // Methods

   public:
    // Default constructors and destructor
    cgvLightSource() = default;
    ~cgvLightSource() = default;

    // Other constructors
    // Build a point light
    cgvLightSource ( const unsigned int _LightID, const cgvPoint3D &_position
                   , const cgvColor &cAmb, const cgvColor &cDif
                   , const cgvColor &cEsp, const double a0, const double a1
                   , const double a2 );

    // Build a focus
    cgvLightSource ( const unsigned int _LightID, const cgvPoint3D &_position
                   , const cgvColor &cAmb, const cgvColor &cDif
                   , const cgvColor &cEsp, const double a0, const double a1
                   , const double a2, const cgvPoint3D &focus_dir
                   , const double ang_focus, const double exp_focus );

    // Methods
    cgvPoint3D &getPosition (); // returns the position of the light
    void setPosition ( cgvPoint3D pos ); // set the position of the light

    void set ( const cgvColor &cAmb, const cgvColor &cDif, const cgvColor &cEsp );
    void setAmbient ( const cgvColor &cAmb );
    void setDiffuse ( const cgvColor &cDif );
    void setSpecular ( const cgvColor &cEsp );
    cgvColor &getAmbient();
    cgvColor &getDiffuse();
    cgvColor &getSpecular();

    void setAttenuation ( double a0, double a1, double a2 );
    void getAttenuation ( double &a0, double &a1, double &a2 );

    void turnon();
    void shutdown();
    bool is_on();

    void apply();
    void move(float dx, float dy, float dz);
};

#endif   // __IGVFUENTELUZ