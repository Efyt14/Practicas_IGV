#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif // defined(__APPLE__) && defined(__MACH__)

#include "cgvTriangleMesh.h"

/**
* Model parts
*/
enum part
{
    basex ///< Identifies the base of the model
    , lowerbody ///< Identifies the lower body of the model
    , upperbody ///< Identifies the upper body of the model
    , arm ///< Identifies the arm of the model
    };




/**
 * Objects of this class represent 3D scenes for visualisation.
 */
class cgvScene3D
{  private:
    // Attributes
    bool axes = true;   ///< Indicates whether to draw the coordinate axes or not
    float x, y, z, z2;

    // Section A: Add attributes with rotation angles in X, Y, and Z here.
    double rotX, rotY, rotZ = 0.0;
    cgvTriangleMesh *mesh = nullptr; ///< Triangle mesh associated with the scene



public:
    //CREACION DE ESCENAS
    std::string currentSceneName;

    void renderSceneA(); // Cilindro
    void renderSceneB(); // Vacía
    void renderSceneC(); // Vacía


    // Default constructors and destructor
    cgvScene3D ();
    ~cgvScene3D ();

    // Methods
    // Method with OpenGL calls to visualise the scene
    void display();
    // TODO: Methods to visualize each part of the model
    void paintCube();
    void drawMastil(float lenght);
    void drawFlag(float lenght);
    void drawEsferaArmilar(float lenght);

    //TODO: Add methods here to modify the model's degrees of freedom

    void rotateBaseY(float _xbase) { x = x + _xbase; }
    float get_rotateBaseY() { return x; };

    void rotateBodyX(float _xbody) { y = y + _xbody; }
    float get_rotateBodyX() { return y; };

    void rotateBodyupZ(float _zbodyup) { z = z + _zbodyup; }
    float get_rotateBodyupZ() { return z; };

    void rotateArmZ(float _zArms) { z2 = z2 + _zArms; }
    float get_rotateArmZ() { return z2; };

    bool get_axes ();

    void set_axes ( bool _axes );

    //Section A: methods to increase angles
    cgvTriangleMesh* getMesh() const
    {
        return mesh;
    }

    void incrX(){
        rotX+= 10;
    }

    void incrY(){
        rotY += 10;
    }

    void incrZ(){
        rotZ += 10;
    }

    //Methods to decrease the angle
    void decrX() {
        rotX -= 10;
    }

    void decrY() {
        rotY -= 10;
    }

    void decrZ() {
        rotZ -= 10;
    }

    // Section A: methods to obtain angle values
    double getRotX() const;

    void setRotX(double rotX);

    double getRotY() const;

    void setRotY(double rotY);

    double getRotZ() const;

    void setRotZ(double rotZ);

private:
    void paint_axes ();
};

#endif   // __CGVSCENE3D

