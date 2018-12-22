//
// Created by dan on 07/12/18.
//

#ifndef DKR_RENDERPASS_H
#define DKR_RENDERPASS_H

#include "common.h"

namespace dk {
    namespace gfx {
        class Device;

        struct SubPass {

        };

        class RenderPass {
        public:
            RenderPass(Device* d);
            ~RenderPass();

        private:
            Device* m_device;
        };
    }
}


#endif //DKR_RENDERPASS_H
