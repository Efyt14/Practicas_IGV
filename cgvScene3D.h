#include <vector>
#include <functional>
#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif   // defined(__APPLE__) && defined(__MACH__)

/**
* Objects of this class represent 3D scenes for display
*/
class cgvScene3D {
public:

    // Para cada objeto vamos a guardar sus transformaciones acumuladas
    struct Transform {
        float tx, ty, tz;   // traslación
        float rx, ry, rz;   // rotación
        float s;            // escala
    };

    Transform transforms[3];   // un transform por cada objeto
    int selected = 0;          // 0 = A, 1 = B, 2 = C
    bool modeRST = true;       // true = aplicar en orden fijo R-S-T, false = orden pulsado
    std::vector<std::function<void()>> ops[3]; // cola de operaciones si es modo libre
    bool deferredMode;  // false = libre, true = diferido



    const int SceneA = 1; ///< Internal identifier for scene A
    const int SceneB = 2; ///< Internal identifier for scene B
    const int SceneC = 3; ///< Internal identifier for scene C

    const char *Scene_NameA = "Scene A"; ///< Label for scene A
    const char *Scene_NameB = "Scene B"; ///< Label for scene B
    const char *Scene_NameC = "Scene C"; ///< Label for scene C
private:
    // Attributes
    bool axes = true; ///< Indicates whether or not to draw the coordinate axes
    int nStacksX=1;
    int nStacksY=1;
    int nStacksZ=1;

public:
    // Default constructors and destructor
    /// Default constructor
    cgvScene3D();

    /// Destructor
    ~cgvScene3D() = default;

    // Methods
    // Method with OpenGL calls to display the scene
    void display(int scene);

    bool get_axes();

    void set_axes(bool _axes);

    void shoeBox();

    void incrStacksX();

    void decrStacksX();

    void incrStacksY();

    void decrStacksY();

    void incrStacksZ();

    void decrStacksZ();

    void drawGun();

    void drawLock();

    void drawWooper();

    void applyTranslation(float dx, float dy, float dz);

    void applyRotation(float dx, float dy, float dz);

    void applyScaling(float factor);



private:
    void renderSceneA();

    void renderSceneB();

    void renderSceneC();

    void paint_axes();
};

#endif   // __IGVESCENA3D
