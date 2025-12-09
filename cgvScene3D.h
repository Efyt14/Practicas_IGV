#ifndef __IGVESCENA3D
#define __IGVESCENA3D
#include "cgvLightSource.h"
#include "cgvMaterial.h"
#include "cgvTexture.h"

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif // defined(__APPLE__) && defined(__MACH__)

#include "cgvTriangleMesh.h"
#include <vector>

//FIXME probar si puedo hacer un struct qeu defina el objeto seleccionado lo coloree indique con un bool si esta coloreado y que tenga un puntero a hijo (si tiene hijo)

// Estructura para las monedas
struct Coin {
    double x, y, z; // Posición
    double rot;     // Rotación
};

/**
 * Objects of this class represent 3D scenes for visualisation.
 */
class cgvScene3D
{
    // Para cada objeto vamos a guardar sus transformaciones acumuladas
    struct Transform {
        float tx, ty, tz;   // traslación
        float rx, ry, rz;   // rotación
        float s;            // escala
    };
private:
    // Attributes
    bool axes = true;   ///< Indicates whether to draw the coordinate axes or not
    float x, y, z, z2;
    int currentScene;

    //Practica 3
    cgvLightSource *lightbulb, *spotlight, *ambient, *directional, *beam;
    cgvMaterial *material1, *material2, *material3;
    cgvMaterial *currentMaterial;
    cgvTexture *texture;

    // Valores de material por defecto
    GLfloat defaultAmbient[4];
    GLfloat defaultDiffuse[4];
    GLfloat defaultSpecular[4];
    GLfloat defaultPhong;




    // Section A: Add attributes with rotation angles in X, Y, and Z here.
    double rotX, rotY, rotZ = 0.0;

    //Rotacion wooper
    double wooperPatasRotZ = 0;
    double wooperCabezaRotZ = 0;
    double wooperBranquiasRotX = 0;
    double wooperBranquiasPequesRotY = 0;
    double wooperColaZ = 0;

    //Grados de libertad Bandera
    double mastilRotY = 0;
    double banderaPosY = 0;
    double logoRotZ = 0;
    double baseRotY = 0;

    cgvTriangleMesh *mesh = nullptr; ///< Triangle mesh associated with the scene

    int objetoSeleccionado;

    bool animation = false;
    double timer;

    //Apartado C
    std::vector<Coin> coins; // Lista dinámica de monedas
    bool selectionMode; // Si es true, pintamos colores falsos (ID)
    int idToHighlight = -1;     // El ID del objeto que se va a marcar con "otro color" internamente (se utilizara un id)



public:
    //CREACION DE ESCENAS
    std::string currentSceneName;
    Transform transforms[3];   // un transform por cada objeto
    int selected = 0;          // // 0=A(sc2), 1=B(sc2), 2=Escena3


    //Para los filtros de textura
    int currentMagFilter = GL_LINEAR;
    int currentMinFilter = GL_LINEAR;

    //Booleanos para elegir por menú que luz poner
    bool useDirectional = true;
    bool useSpotlight = true;
    bool useBeam = true;
    cgvLightSource *currentLight;


    void renderSceneA(); // Cilindro
    void renderSceneB(); // Grafos de Escena
    void renderSceneC(); // Mouse


    // Default constructors and destructor
    cgvScene3D ();
    ~cgvScene3D ();

    // Methods
    // Method with OpenGL calls to visualise the scene
    void display();

    void paintCube();
    void drawMastil(float lenght);
    void drawFlag(float lenght);
    void drawEsferaArmilar(float lenght);

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
    cgvTriangleMesh* getMesh() const {return mesh;}
    void incrX(){rotX+= 10;}
    void incrY(){rotY += 10;}
    void incrZ(){rotZ += 10;}

    //Methods to decrease the angle
    void decrX() {rotX -= 10;}
    void decrY() {rotY -= 10;}
    void decrZ() {rotZ -= 10;}

    // Section A: methods to obtain angle values
    double getRotX() const;
    void setRotX(double rotX);

    double getRotY() const;
    void setRotY(double rotY);

    double getRotZ() const;
    void setRotZ(double rotZ);

    int getObjetoSeleccionado() const;
    void setObjetoSeleccionado(int objetoSeleccionado);

    void controlarParte(int parte, double incremento);

    int getCurrentScene() const;
    void setCurrentScene(int currentScene);

    void toggleAnimation();
    void updateAnimation();
    bool isAnimationActive();

    // Métodos para Monedas
    void addCoin();
    void removeCoin();

    // Métodos para Selección
    void setSelectionMode(bool active);
    void setIdToHighlight(int id); // Para decirle qué objeto está seleccionado
    void controlarParteSceneC(int id, double incremento);

    void applyTranslation(float dx, float dy, float dz);
    void applyScaling(float factor);
    void applyRotation(float dx, float dy, float dz);

    void renderSceneContent();

    //Practica 3
    cgvLightSource *getSpotlight() { return spotlight;}
    cgvLightSource *getDirectional() {return directional;}
    cgvLightSource *getBeam() {return beam;}
    cgvMaterial *getMaterial() { return currentMaterial;}

    cgvTexture *getTexture() const;

    void setTexture(cgvTexture *texture);
    void setCurrentMaterial(int id);


private:
    void paint_axes ();
    void drawWooper();
    void drawLogo(float lenght);
    // Helper para configurar el material1 o el color de selección
    void applyColorMaterial(int id, float r, float g, float b);
    void drawCoin(Coin& c); // Método para dibujar una moneda

    //Practica 3
    void paint_quad();
    void paint_quad(float div_x, float div_z);
};

#endif   // __CGVSCENE3D