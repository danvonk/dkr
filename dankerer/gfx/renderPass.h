//
// Created by dan on 07/12/18.
//

#ifndef DKR_RENDERPASS_H
#define DKR_RENDERPASS_H

#include "common.h"
#include "texture.h"
#include <functional>

namespace dk {
    namespace gfx {
        class Device;

        struct SubPass {

        };

        //RenderPass class will populate this struct and send it to the cmd buffer
        struct RenderPassInfo {
            std::vector<Texture*> m_colourAttachments;
            Texture* m_depthAttachment = nullptr;
            Texture* m_stencilAttachment = nullptr;

            glm::vec3 m_clearColour;
        };

        class RenderPass {
        public:
            explicit RenderPass(Device* d);
			~RenderPass() = default;
			RenderPass(RenderPass&&) = default;

            void setName(std::string const& name);
            std::string getName() const;

            void addInput(std::string const& name);
            void addOutput(std::string const& name);
            void setClearColour(glm::vec4 colour);

            void bind();
        private:
            std::string m_nameOfPass;
            glm::vec3 m_clearColour;

            std::vector<TextureHandle> m_inputs;
            std::vector<TextureHandle> m_outputs;

            Device* m_device;
            FramebufferHandle m_frame;
            RenderPassInfo m_renderPassInfo;
        };
    }
}


#endif //DKR_RENDERPASS_H
