//
// Created by dan on 26/10/18.
//

#ifndef DANKERER_SHADERPROGRAM_H
#define DANKERER_SHADERPROGRAM_H

#include "common.h"
#include "dankerer/gfx/shader.h"


namespace dk {
    namespace gfx {
        class Shader;
        class ShaderProgram {
        public:
            ShaderProgram();
            ~ShaderProgram();

            void addShader(Shader* shader);
            bool link();

            void setUniform(GLuint bindingPoint, int value);
            GLuint getID() {
                return m_shp;
            }

        private:
            GLuint m_shp;

        };
    }
}


#endif //DANKERER_SHADERPROGRAM_H
