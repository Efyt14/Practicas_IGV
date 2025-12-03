#include "cgvLightSource.h"

// M�todos constructores

/**
 * Construye una fuente de luz puntual encendida por defecto
 * @param _idLuz Identificador de la luz (GL_LIGHT0 a GL_LIGHT7)
 * @param _posicion Ubicaci�n de la luz en la escena
 * @param cAmb Color de la componente ambiente de la luz
 * @param cDif Color de la componente difusa de la luz
 * @param cEsp Color de la componente especular de la luz
 * @param a0 Coeficiente de atenuaci�n a0
 * @param a1 Coeficiente de atenuaci�n a1
 * @param a2 Coeficiente de atenuaci�n a2
 * @pre Se asume que los par�metros tienen valores v�lidos
 */
cgvLightSource::cgvLightSource ( const unsigned int _idLuz
                             , const cgvPoint3D &_posicion, const cgvColor &cAmb
                             , const cgvColor &cDif, const cgvColor &cEsp
                             , const double a0, const double a1, const double a2 ):
                           idLuz ( _idLuz ), position( _posicion )
                           , colorAmbient( cAmb ), colorDiffuse( cDif )
                           , colorSpecular( cEsp ), aten_a0( a0 ), aten_a1( a1 )
                           , aten_a2( a2 ), spotlight_direction( { 0, 0, 0 } )
                           , spotlight_angle( 180 ), spotlight_exponent( 0 )
                           , on( true )
{}

/**
 * Construye una fuente de tipo foco encendida por defecto
 * @param _idLuz Identificador de la luz (GL_LIGHT0 a GL_LIGHT7)
 * @param _posicion Ubicaci�n de la luz en la escena
 * @param cAmb Color de la componente ambiente de la luz
 * @param cDif Color de la componente difusa de la luz
 * @param cEsp Color de la componente especular de la luz
 * @param a0 Coeficiente de atenuaci�n a0
 * @param a1 Coeficiente de atenuaci�n a1
 * @param a2 Coeficiente de atenuaci�n a2
 * @param dir_foco Direcci�n hacia la que apunta el foco
 * @param ang_foco �ngulo de apertura del cono de luz
 * @param exp_foco Exponente de atenuaci�n del cono de luz
 * @pre Se asume que los par�metros tienen valores v�lidos
 */
cgvLightSource::cgvLightSource ( const unsigned int _idLuz
                             , const cgvPoint3D &_posicion, const cgvColor &cAmb
                             , const cgvColor &cDif, const cgvColor &cEsp
                             , const double a0, const double a1, const double a2
                             , const cgvPoint3D &dir_foco, const double ang_foco
                             , const double exp_foco ): idLuz( _idLuz )
                           , position( _posicion ), colorAmbient( cAmb )
                           , colorDiffuse( cDif ), colorSpecular( cEsp )
                           , aten_a0( a0 ), aten_a1( a1 ), aten_a2( a2 )
                           , spotlight_direction( dir_foco ), spotlight_angle( ang_foco )
                           , spotlight_exponent( exp_foco ), on( true )
{}

// Public Methods ----------------------------------------

/**
* Checks the light's position
* @return A reference to the light's position
*/
cgvPoint3D &cgvLightSource::getPosition ()
{
    return position;
}
/**
* Changes the light's position
* @param pos New light position
* @post Light position changes
* @pre Parameter is assumed to be valid
*/
void cgvLightSource::setPosition ( cgvPoint3D pos )
{
    position = pos;
}

/**
* Changes the light's color
* @param cAmb New ambient component of the light (values in the range [0,1])
* @param cDif New diffuse component of the light (values in the range [0,1])
* @param cEsp New specular component of the light (values in the range [0,1])
* @pre Parameters are assumed to be valid
* @post Light color changes
*/
void cgvLightSource::set ( const cgvColor &cAmb, const cgvColor &cDif
                         , const cgvColor &cEsp )
{  colorAmbient = cAmb;
   colorDiffuse = cDif;
   colorSpecular = cEsp;
}

/**
* Changes the ambient light component color
* @param cAmb New ambient light color (values in the range [0,1])
* @pre Assumes the parameter is valid
* @post Changes the ambient light component color
*/
void cgvLightSource::setAmbient ( const cgvColor &cAmb )
{  colorAmbient = cAmb;
}

/**
* Changes the color of the diffuse component of the light
* @param cDif New diffuse color of the light (values in the range [0,1])
* @pre Assumes the parameter is valid
* @post The color of the diffuse component of the light changes
*/
void cgvLightSource::setDiffuse ( const cgvColor &cDif )
{
    colorDiffuse = cDif;
}
/**
* Changes the color of the specular component of the light
* @param cEsp New specular color of the light (values in the range [0,1])
* @pre Assumes the parameter is valid
* @post The color of the specular component of the light changes
*/
void cgvLightSource::setSpecular ( const cgvColor &cEsp )
{  colorSpecular= cEsp;
}

/**
* Checks the ambient light component color
* @return A reference to the ambient light component
*/
cgvColor &cgvLightSource::getAmbient ()
{  return colorAmbient;
}

/**
* Checks the color of the diffuse component of light
* @return A reference to the diffuse component of light
*/
 cgvColor &cgvLightSource::getDiffuse ()
{  return colorDiffuse;
}

/**
* Checks the color of the specular component of the light
* @return A reference to the specular component of the light
*/
cgvColor &cgvLightSource::getSpecular ()
{  return colorSpecular;
}

/**
* Changes the coefficients in the light attenuation formula
* @param a0 New value for the attenuation coefficient a0
* @param a1 New value for the attenuation coefficient a1
* @param a2 New value for the attenuation coefficient a2
* @pre Assumes that the parameters have valid values
* @post The light attenuation coefficients change
*/
void cgvLightSource::setAttenuation ( double a0, double a1, double a2 )
{  aten_a0 = a0;
   aten_a1 = a1;
   aten_a2 = a2;
}

/**
* Query the light attenuation coefficients
* @param a0 Stores the attenuation coefficient a0
* @param a1 Stores the attenuation coefficient a1
* @param a2 Stores the attenuation coefficient a2
*/
void cgvLightSource::getAttenuation ( double &a0, double &a1, double &a2 )
{  a0 = aten_a0;
   a1 = aten_a1;
   a2 = aten_a2;
}

/**
* Changes the light's state to on
* @post The light is now on
*/
void cgvLightSource::turnon ()
{
    on = true;
}

/**
* Changes the light's state to off
* @post The light is now off
*/
void cgvLightSource::shutdown ()
{
    on = false;
}

/**
* Check the light status
* @retval true If the light is on
* @retval false If the light is off
*/
bool cgvLightSource::is_on ()
{  return on;
}

/**
* Calls OpenGL functions to apply lighting to the scene
*/
void cgvLightSource::apply () {
    //SECTION A

    // if the light is on

    if (on) {
        // activate the light
            glEnable(idLuz);

        // set the light's position
        glLightfv(idLuz, GL_POSITION, position.cloneToFloatArray());
        // set the ambient, diffuse, and specular colors
        glLightfv(idLuz, GL_AMBIENT, colorAmbient.cloneToFloatArray());
        glLightfv(idLuz, GL_DIFFUSE, colorDiffuse.cloneToFloatArray());
        glLightfv(idLuz, GL_SPECULAR, colorSpecular.cloneToFloatArray());
        // set the radial attenuation
        glLightf(idLuz, GL_CONSTANT_ATTENUATION, aten_a0);
        glLightf(idLuz, GL_LINEAR_ATTENUATION, aten_a1);
        glLightf(idLuz, GL_QUADRATIC_ATTENUATION, aten_a2);
        // Set the angular attenuation and spotlight direction
        glLightfv(idLuz, GL_SPOT_DIRECTION, spotlight_direction.cloneToFloatArray());
        glLightf(idLuz, GL_SPOT_CUTOFF, spotlight_angle);
        glLightf(idLuz, GL_SPOT_EXPONENT, spotlight_exponent);
    }
    // If the light is off
    // Turn off the light
    else
    {
        glDisable(idLuz);
    }
}

void cgvLightSource::move(float dx, float dy, float dz)
{
    position[0] += dx;
    position[1] += dy;
    position[2] += dz;
}