//
// Created by dan on 21/12/18.
//

#ifndef DKR_RENDERQUEUE_H
#define DKR_RENDERQUEUE_H

#include "common.h"
#include "opengl/shaderProgram.h"
#include "renderPass.h"

namespace dk {
    namespace gfx {
        class CommandBuffer;
        class Device;
        class RenderPass;
        class ElementBuffer;
        class RenderQueueItem;
        using RendererFunc = void (*)(CommandBuffer*, const RenderQueueItem*, u32);

        struct RenderQueueItem {
            //function ptr handles how to draw the object
            RendererFunc m_rendererFunction;
            //extra data needed to draw the object
            void* m_renderInfo;
            //sort key
            u32 m_sortKey;
        };

        class CommandBuffer {
        public:
            explicit CommandBuffer(Device* d);
            ~CommandBuffer() = default;

            void sort();
            void execute();
            void reset();

            void beginRenderPass();
            void endRenderPass();

            void setShaderProgram(ShaderProgram* p);
            void setVao(GLuint vao);
            void setElementBuffer(ElementBuffer* e);

            template <typename T>
            void push();

            Device* getDevice() {
                return m_device;
            }

            void draw(u32 startVertex, u32 count);
            void drawElements(u32 vertexCount, u32 indexOffset);

        private:
            Device* m_device;
            ShaderProgram* m_currentShp;

            RenderPass* m_currentRenderPass;

            std::vector<RenderQueueItem> m_queueItems;
        };
    }
}

#endif //DKR_RENDERQUEUE_H
