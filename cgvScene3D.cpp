#include <cstdlib>
#include <stdio.h>
#include <cmath>
#include <cgvCylinder.h>

#include "cgvScene3D.h"
#include "cgvTriangleMesh.h"


// Constructor methods

/**
 * Default constructor
 */
cgvScene3D::cgvScene3D ()
{  //Section B: Insert code to create a cylinder
    mesh = new cgvCylinder(1.0f, 1.0f, 40, 2);
    axes = true;
    rotX = rotY = rotZ = 0.0f;
}

/**
 * Destructor
 */
cgvScene3D::~cgvScene3D ()
{  if ( mesh != nullptr )
{  delete mesh;
   mesh = nullptr;
}
}


// Public methods

/**
 * Method for painting the coordinate axes by calling OpenGL functions
 */
void cgvScene3D::paint_axes()
{    GLfloat red[] = { 1,0,0,1.0 };
   GLfloat green[] = { 0,1,0,1.0 };
   GLfloat blue[] = { 0,0,1,1.0 };

   glMaterialfv(GL_FRONT, GL_EMISSION, red);
   glBegin(GL_LINES);
   glVertex3f(1000, 0, 0);
   glVertex3f(-1000, 0, 0);
   glEnd();

   glMaterialfv(GL_FRONT, GL_EMISSION, green);
   glBegin(GL_LINES);
   glVertex3f(0, 1000, 0);
   glVertex3f(0, -1000, 0);
   glEnd();

   glMaterialfv(GL_FRONT, GL_EMISSION, blue);
   glBegin(GL_LINES);
   glVertex3f(0, 0, 1000);
   glVertex3f(0, 0, -1000);
   glEnd();
}

/**
 * Method with OpenGL calls to visualise the scene
 */
void cgvScene3D::display( void )
{
    GLfloat mesh_colour[] = { 0, 0.25, 0 };
    // create lights   // point light to display the cube
    GLfloat light0[4] = { 2.0, 2.5, 3.0, 1 };

   // the light is placed here if it remains fixed and does not move with the scene
   glLightfv ( GL_LIGHT0, GL_POSITION, light0 );
   glEnable(GL_LIGHT0);

   // create the model
   glPushMatrix(); // save the modelling matrix

   // paint the axes
    if (axes) paint_axes();

    // create the model
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);
    glRotatef(rotZ, 0, 0, 1);

    // the light is placed here if it moves with the scene
   glLightfv(GL_LIGHT0,GL_POSITION,light0);
   glMaterialfv ( GL_FRONT, GL_EMISSION, mesh_colour );

   // Section B: the following call must be replaced by the call to the mesh visualisation method
   /*GLUquadric *cyl = gluNewQuadric ();
   gluCylinder ( cyl, 1, 1, 1, 20, 5 );
   gluDeleteQuadric ( cyl );
   cyl = nullptr;
    */
    if (mesh != nullptr)
        mesh->display();

   glPopMatrix (); // restores the modelling matrix
}

/**
 * Method to check whether the axes should be drawn or not
 * @retval true If the axes should be drawn
 * @retval false If the axes should not be drawn
 */
bool cgvScene3D::get_axes ()
{  return axes;
}

/**
 * Method to enable or disable the drawing of the axes
 * @param axes Indicates whether to draw the axes (true) or not (false)
 * @post The status of the object changes with regard to drawing axes,
 *       according to the value passed as a parameter
 */
void cgvScene3D::set_axes ( bool axes )
{  this->axes = axes; //Arreglado
}

double cgvScene3D::getRotX() const {
    return rotX;
}

void cgvScene3D::setRotX(double rotX) {
    cgvScene3D::rotX = rotX;
}

double cgvScene3D::getRotY() const {
    return rotY;
}

void cgvScene3D::setRotY(double rotY) {
    cgvScene3D::rotY = rotY;
}

double cgvScene3D::getRotZ() const {
    return rotZ;
}

void cgvScene3D::setRotZ(double rotZ) {
    cgvScene3D::rotZ = rotZ;
}


//ESCENAS
void cgvScene3D::renderSceneA()
{
    if (mesh != nullptr) delete mesh;

    mesh = new cgvCylinder(1.0f, 1.0f, 40, 2);

    axes = true;

    glutPostRedisplay();
}

// --- ESCENA B ---
void cgvScene3D::renderSceneB()
{
    if (mesh != nullptr) {
        delete mesh;
        mesh = nullptr;
    }

    axes = true;
    glutPostRedisplay();
}

// --- ESCENA C ---
void cgvScene3D::renderSceneC()
{
    if (mesh != nullptr) {
        delete mesh;
        mesh = nullptr;
    }

    axes = true;
    glutPostRedisplay();
}