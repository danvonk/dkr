//
// Created by dan on 26/10/18.
//

#include "shaderProgram.h"
#include "shader.h"
#include "dankerer/gfx/shaderProgram.h"


using dk::gfx::ShaderProgram;
using dk::gfx::Shader;

ShaderProgram::ShaderProgram() {
    m_shp = glCreateProgram();

}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(m_shp);

}

void ShaderProgram::addShader(Shader *shader) {
    glAttachShader(m_shp, shader->getID());

}

bool dk::gfx::ShaderProgram::link() {
    glBindFragDataLocation(m_shp, 0, "outColour"); //TODO: remove...
    glLinkProgram(m_shp);
    glUseProgram(m_shp);

    GLint isLinked = 0;
    glGetProgramiv(m_shp, GL_LINK_STATUS, (int*)&isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxlen = 0;
        glGetProgramiv(m_shp, GL_INFO_LOG_LENGTH, &maxlen);
        std::vector<GLchar> infoLog(maxlen);
        glGetProgramInfoLog(m_shp, maxlen, &maxlen, &infoLog[0]);

        printf(&infoLog[0]);
        return false;
    }

    GLint posAtt = glGetAttribLocation(m_shp, "position");
    glEnableVertexAttribArray(posAtt);
    glVertexAttribPointer(posAtt, 2, GL_FLOAT, GL_FALSE, 0, 0);
    return true;
}

void ShaderProgram::setUniform(GLuint bindingPoint, int value) {
    glUniform1i(bindingPoint, value);
}
