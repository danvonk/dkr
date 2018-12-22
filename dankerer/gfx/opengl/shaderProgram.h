//
// Created by dan on 26/10/18.
//

#ifndef DANKERER_SHADERPROGRAM_H
#define DANKERER_SHADERPROGRAM_H

#include "common.h"
#include "opengl/shader.h"


namespace dk {
    namespace gfx {
        class Shader;
        class Device;
        class ShaderProgram {
        public:
            explicit ShaderProgram(Device* d);
            ~ShaderProgram();

            void addShader(ShaderHandle shader, Device* rend);
            bool link(Device* rend);

            void setUniform(GLuint bindingPoint, int value);

            GLuint getID() {
                return m_shp;
            }

        private:
            Device* m_device;
            GLuint m_shp;

        };
    }
}


#endif //DANKERER_SHADERPROGRAM_H
