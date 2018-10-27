//
// Created by dan on 25/10/18.
//

#ifndef DANKERER_SHADER_H
#define DANKERER_SHADER_H

#include "common.h"

namespace dk {
    namespace gfx {
        class Shader {
            friend class ShaderProgram;
        public:
            Shader(GLenum shaderType, std::string const& fileName);
            explicit Shader(GLenum shaderType);
            ~Shader();

            bool compile(std::string const &fileName);
            bool compile();
        private:
            auto getShaderType() {
                return m_shaderType;
            }

            auto getID() {
                return m_shader;
            }

            std::string m_fileName;
            GLuint m_shader;
            GLenum m_shaderType;

        };
    }
}


#endif //DANKERER_SHADER_H
