//
// Created by dan on 26/10/18.
//

#ifndef DANKERER_SHADERPROGRAM_H
#define DANKERER_SHADERPROGRAM_H

#include "common.h"
#include "gfx/shader.h"


namespace dk {
    namespace gfx {
        class Shader;
        class Renderer;
        class ShaderProgram {
        public:
            ShaderProgram();
            ~ShaderProgram();

            void addShader(ShaderHandle shader, Renderer* rend);
            bool link(Renderer* rend);

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
