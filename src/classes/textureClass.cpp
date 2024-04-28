//
// Created by Murilo on 27/04/2024.
//

#include "../../include/headers/textureClass.h"

TextureClass::TextureClass(const char* image, const char* texType, GLuint slot, GLenum format, GLenum pixelType)
{
    // Assigns the type of the TextureClass ot the TextureClass object
    type = texType;

    // Stores the width, height, and the number of color channels of the image
    int widthImg, heightImg, numColCh;
    // Flips the image so it appears right side up
    stbi_set_flip_vertically_on_load(true);
    // Reads the image from a file and stores it in bytes
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

    // Generates an OpenGL TextureClass object
    glGenTextures(1, &ID);
    // Assigns the TextureClass to a TextureClass Unit
    glActiveTexture(GL_TEXTURE0 +  slot);
    unit = slot;
    glBindTexture(GL_TEXTURE_2D, ID);

    // Configures the type of algorithm that is used to make the image smaller or bigger
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Configures the way the TextureClass repeats (if it does at all)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Extra lines in case you choose to use GL_CLAMP_TO_BORDER
    // float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    // glTexParameterfv(GL_TextureClass_2D, GL_TextureClass_BORDER_COLOR, flatColor);

    // Assigns the image to the OpenGL TextureClass object
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
    // Generates MipMaps
    glGenerateMipmap(GL_TEXTURE_2D);

    // Deletes the image data as it is already in the OpenGL TextureClass object
    stbi_image_free(bytes);

    // Unbinds the OpenGL TextureClass object so that it can't accidentally be modified
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureClass::texUnit(ShaderClass& shader, const char* uniform, GLuint unit)
{
    // Gets the location of the uniform
    GLuint texUni = glGetUniformLocation(shader.id, uniform);
    // Shader needs to be activated before changing the value of a uniform
    shader.Activate();
    // Sets the value of the uniform
    glUniform1i(texUni, unit);
}

void TextureClass::Bind()
{
    glActiveTexture(GL_TEXTURE0 +  unit);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void TextureClass::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureClass::Delete()
{
    glDeleteTextures(1, &ID);
}
