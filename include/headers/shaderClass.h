//
// Created by Murilo on 26/04/2024.
//

#ifndef CG2_SHADERCLASS_H
#define CG2_SHADERCLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

using namespace std;

string get_file_contents(const char* filename);

class ShaderClass{

public:
    GLuint id;

    ShaderClass(const char* vertexFile, const char* fragmentFile);

    void Activate();
    void Delete();

private:
    // basicamente capturando possíveis erros no shaders
    void compileErrors(unsigned int shader, const char* type);
};


#endif //CG2_SHADERCLASS_H
