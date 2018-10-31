//
// Created by dan on 26/10/18.
//

#include "shaderProgram.h"
#include "shader.h"


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
//    glBindFragDataLocation(m_shp, 0, "outColour"); //TODO: remove...
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

    auto pos = glGetAttribLocation(m_shp, "position");
    glEnableVertexAttribArray(pos);
    std::cout << "Val is " << pos << "\n";
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), nullptr);
    auto norm = glGetAttribLocation(m_shp, "colour");
    std::cout << "Val is " << norm << "\n";
    glEnableVertexAttribArray(norm);
    glVertexAttribPointer(norm, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    auto texc = glGetAttribLocation(m_shp, "texCoord");
    std::cout << "Val is " << texc << "\n";
    glEnableVertexAttribArray(texc);
    glVertexAttribPointer(texc, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

    glUniform1i(glGetUniformLocation(m_shp, "tex"), 0);
    return true;
}

void ShaderProgram::setUniform(GLuint bindingPoint, int value) {
    glUniform1i(bindingPoint, value);
}
