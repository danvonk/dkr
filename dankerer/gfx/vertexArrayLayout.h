//
// Created by dan on 25/10/18.
//

#ifndef DANKERER_VERTEXARRAYCONFIG_H
#define DANKERER_VERTEXARRAYCONFIG_H

#include "common.h"

namespace dk {
    namespace gfx {
		class Device;
        struct VertexArrayLayoutEntry {
            int m_layoutLocation;
            int m_numComponents;
            GLenum m_type;
            int m_offset;
            size_t m_stride;
        };

        class VertexArrayLayout {
        public:
            explicit VertexArrayLayout(Device* d);
            ~VertexArrayLayout();

            void addAttribute(int index, int numComponents, GLenum type);
            void bindAttribute();

        private:
            Device* m_device;
            std::vector<VertexArrayLayoutEntry> m_entries;
            GLuint m_vao;
            bool m_previouslyBound;

        };
    }
}


#endif //DANKERER_VERTEXARRAYCONFIG_H
