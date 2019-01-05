//
// Created by dan on 25/10/18.
//

#ifndef DANKERER_VERTEXARRAYCONFIG_H
#define DANKERER_VERTEXARRAYCONFIG_H

#include "common.h"
#include <unordered_map>
#include <boost/container_hash/hash.hpp>

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

        std::size_t hash_value(VertexArrayLayoutEntry const& v) {
            boost::hash<int> hasher;
        }

        bool operator==(const VertexArrayLayoutEntry& a, const VertexArrayLayoutEntry& b) {
            return (a.m_layoutLocation == b.m_layoutLocation) && (a.m_numComponents == b.m_numComponents)
                   && (a.m_type == b.m_type) && (a.m_offset == b.m_offset) && (a.m_stride == b.m_stride);
        }

        class VertexArrayLayout {
        public:
            explicit VertexArrayLayout(Device* d);
            ~VertexArrayLayout();

            void addAttribute(int index, int numComponents, GLenum type);
            void bindAttribute();
            int getHash();

        private:
            Device* m_device;
            std::vector<VertexArrayLayoutEntry> m_entries;
            GLuint m_vao;
            bool m_previouslyBound;

        };
    }
}


#endif //DANKERER_VERTEXARRAYCONFIG_H
