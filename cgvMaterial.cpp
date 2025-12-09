#include "cgvMaterial.h"

// Constructor Methods

/**
* Copy constructor
* @param p Material from which properties are copied
*/
cgvMaterial::cgvMaterial ( const cgvMaterial &p ): Ka ( p.Ka ), Kd ( p.Kd )
                                                   , Ks ( p.Ks ), Ns ( p.Ns )
{}

/**
* Parameterized constructor
* @param _Ka Value for the ambient reflection coefficient
* @param _Kd Value for the diffuse reflection coefficient
* @param _Ks Value for the specular reflection coefficient
* @param _Ns Value for the Phong exponent
*/
cgvMaterial::cgvMaterial ( cgvColor _Ka, cgvColor _Kd, cgvColor _Ks, double _Ns ):
                         Ka ( _Ka ), Kd ( _Kd ), Ks ( _Ks ), Ns ( _Ns )
{}

// Public Methods

/**
* Method to apply material1 properties by calling OpenGL functions
*/
void cgvMaterial::apply ()
{
    // TODO: SECTION B
    // Apply the values of the cgvMaterial object attributes:
    // - Ambient light reflection coefficient
    glMaterialfv(GL_FRONT, GL_AMBIENT, Ka.cloneToFloatArray());
    // - Diffuse reflection coefficient
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Kd.cloneToFloatArray());
    // - Specular reflection coefficient
    glMaterialfv(GL_FRONT, GL_SPECULAR, Ks.cloneToFloatArray());
    // - Phong exponent
    GLfloat phong = Ns;
    glMaterialfv(GL_FRONT, GL_SHININESS, &phong);

    // Set emission color to (0.0, 0.0, 0.0) (the object is not a light source)
    GLfloat color[3] = { 0.0, 0.0, 0.0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, color);
    // - exponente de Phong
    glMaterialf(GL_FRONT, GL_SHININESS, Ns);

    // establecer como color de emisión (0.0, 0.0, 0.0) (el objeto no es una fuente de luz)
    GLfloat emision[] = { 0, 0, 0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, emision);
}

/**
* Changes material1 properties
* @param _Ka Value for the ambient reflection coefficient
* @param _Kd Value for the diffuse reflection coefficient
* @param _Ks Value for the specular reflection coefficient
* @param _Ns Value for the Phong exponent
* @pre Assumes parameters have valid values
* @post The material1 properties change
*/
void cgvMaterial::set ( cgvColor _Ka, cgvColor _Kd, cgvColor _Ks, double _Ns )
{  Ka = _Ka;
   Kd = _Kd;
   Ks = _Ks;
   Ns = _Ns;
}
