//
// Created by dan on 25/10/18.
//

#ifndef DANKERER_FRAMEBUFFER_H
#define DANKERER_FRAMEBUFFER_H

#include "common.h"

namespace dk {
    namespace gfx {
        class Device;
        class Texture;
        class Framebuffer {
        public:
            explicit Framebuffer(Device* d);
            ~Framebuffer();

            void addColourAttachment(Texture* t);
			void addDepthAttachment(Texture* t);
			void addStencilAttachment(Texture* t);
			void clearAttachments();

            void bind();

        private:
            Device* m_device;

            std::vector<Texture*> m_colourAttachments;
            Texture* m_depthAttachment;
            Texture* m_stencilAttachment;

            GLuint m_fbo;
        };
    }
}


#endif //DANKERER_FRAMEBUFFER_H
