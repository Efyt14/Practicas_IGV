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
 * Objects of this class represent 3D scenes for visualisation.
 */
class cgvScene3D
{  private:
    // Attributes
    bool axes = true;   ///< Indicates whether to draw the coordinate axes or not

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

