#include "cgvTexture.h"
#include "lodepng.h"

#include <vector>
#include <stdexcept>
#include <iostream>

// Constructor and Destructor Methods

/**
* Parameterized constructor. Loads a texture from a file
* @param file
*/
cgvTexture::cgvTexture ( std::string file )
{
    glEnable ( GL_TEXTURE_2D );

    if ( !glIsTexture ( idTexture ) )
    {
        std::vector<unsigned char> texels;
        unsigned int error = lodepng::decode ( texels, width, height, file );

        if ( error )
        {
            std::string message = "Error reading the file ";
            throw std::runtime_error ( message + file );
        }

        std::cout << width << " " << height << std::endl;
        // TODO: Section F: Add the code here to load the image as an OpenGL texture */
        // - Generate the texture identifier and assign it to the idTexture attribute (glGenTextures)
        glGenTextures(1, &idTexture);
        // - Bind the created identifier to GL_TEXTURE_2D (glBindTexture)
        glBindTexture(GL_TEXTURE_2D, idTexture);
        //- Specify the texture, assigning the image array as the texture (glTexImage2D)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texels.data());
        // - Texture application mode
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        //	- Parámetros de la textura: repetición y filtros
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
}

/**
* Destructor. Removes the related OpenGL texture
* */
cgvTexture::~cgvTexture ()
{  glDeleteTextures ( 1, &idTexture );
}

/**
* Enables the related OpenGL texture
*/
void cgvTexture::apply ()
{  glBindTexture ( GL_TEXTURE_2D, idTexture );
}

/**
* Changes the identifier of the related OpenGL texture
* @param id New texture identifier
* @pre Assumes the parameter is valid
* @post The OpenGL texture identifier changes
*/
void cgvTexture::setTextureId ( unsigned int id )
{  this->idTexture = id;
}

/**
* Query the OpenGL texture identifier
* @return The identifier of the related OpenGL texture
*/
unsigned int cgvTexture::getTextureId ()
{  return this->idTexture;
}
