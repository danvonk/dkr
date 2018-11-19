//
// Created by dan on 25/10/18.
//

#ifndef DANKERER_VERTEXARRAYCONFIG_H
#define DANKERER_VERTEXARRAYCONFIG_H

#include "common.h"

namespace dk {
    namespace gfx {
        enum class VertexAttributeLayout {
            PositionNormalTexture,
            PositionNormal,
            PositionColour
        };

        class VertexArrayConfig {
        public:
            VertexArrayConfig();
            ~VertexArrayConfig();

            void createNewConfig();
            void bindConfig();

        private:
            std::vector<GLuint> m_vaos;

        };
    }
}


#endif //DANKERER_VERTEXARRAYCONFIG_H
