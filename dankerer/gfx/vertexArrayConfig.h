//
// Created by dan on 25/10/18.
//

#ifndef DANKERER_VERTEXARRAYCONFIG_H
#define DANKERER_VERTEXARRAYCONFIG_H

#include "common.h"
#include <unordered_map>

namespace dk {
    namespace gfx {
        enum class VertexAttributeLayout {
            Default,
            Position3Normal3Colour3,
            Position3Normal3,
            Position3Colour3,
            Position3Normal3Tex2
        };

        class VertexArrayConfig {
        public:
            VertexArrayConfig();
            ~VertexArrayConfig();

            //return false if the layout was already in the cache
            //will automatically bind
            bool addLayout(VertexAttributeLayout l);
            //return false if a new layout was added (i.e. not in cache)
            bool bindLayout(VertexAttributeLayout l);
            void deleteLayout(VertexAttributeLayout l);

        private:
            std::unordered_map<VertexAttributeLayout, GLuint> m_vaoMap;
        };
    }
}


#endif //DANKERER_VERTEXARRAYCONFIG_H
