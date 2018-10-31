//
// Created by dan on 25/10/18.
//

#include "shader.h"

#include <fstream>
#include <sstream>


using dk::gfx::Shader;

Shader::Shader(GLenum shaderType, std::string const &fileName) {
    m_isCompiled = false;
    m_shader = glCreateShader(shaderType);
    m_fileName = fileName;
    m_shaderType = shaderType;
}

Shader::Shader(GLenum shaderType) {
    m_shader = glCreateShader(shaderType);
    m_shaderType = shaderType;
}

Shader::~Shader() {
    glDeleteShader(m_shader);
}

bool Shader::compile(std::string const &fileName) {
    std::ostringstream sstream;
    std::ifstream ifs(fileName);
    sstream << ifs.rdbuf();

    std::string sourceCode = sstream.str();
    const char* ptrSrc = sourceCode.c_str();

    glShaderSource(m_shader, 1, &ptrSrc, nullptr);
    glCompileShader(m_shader);

    GLint vertCompiled = 0;
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &vertCompiled);
    if (vertCompiled == GL_FALSE) {
        GLint maxlen = 0;
        glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &maxlen);
        std::vector<GLchar> errorLog(maxlen);
        glGetShaderInfoLog(m_shader, maxlen, &maxlen, &errorLog[0]);
        printf(&errorLog[0]);
        return false;
    }
    m_isCompiled = true;
    return true;
}

bool Shader::compile() {
    if (!m_fileName.empty()) {
        //shader can be compiled with file
        return compile(m_fileName);
    }
    return false;

}

bool Shader::isCompiled() {
    return m_isCompiled;
}