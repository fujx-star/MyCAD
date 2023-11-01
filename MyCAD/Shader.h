#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:

    unsigned int shaderProgram;

    Shader(const char* vertexPath, const char* fragmentPath);

    void use();

    void setVec3f(const std::string& name, glm::vec3 value) const;

    void setMat4f(const std::string& name, glm::mat4 value) const;

    void setFloat(const std::string& name, float value) const;

    void setImage1i(const std::string& name, unsigned int value) const;

private:

    void checkCompileErrors(unsigned int shader, std::string type);

};

#endif

