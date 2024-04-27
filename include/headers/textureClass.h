//
// Created by Murilo on 27/04/2024.
//

#ifndef CG2_TEXTURECLASS_H
#define CG2_TEXTURECLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>
#include"shaderClass.h"

class TextureClass
{
public:
    GLuint ID;
    GLenum type;
    TextureClass(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

    // Assigns a texture unit to a texture
    void texUnit(ShaderClass& shader, const char* uniform, GLuint unit);
    // Binds a texture
    void Bind();
    // Unbinds a texture
    void Unbind();
    // Deletes a texture
    void Delete();
};

#endif //CG2_TEXTURECLASS_H