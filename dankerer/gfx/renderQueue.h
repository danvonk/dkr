//
// Created by dan on 21/12/18.
//

#ifndef DKR_RENDERQUEUE_H
#define DKR_RENDERQUEUE_H

#include "common.h"
#include "opengl/shaderProgram.h"

namespace dk {
    namespace gfx {
        class RenderQueue;
        class Device;
        class RenderQueueItem;
        using RendererFunc = void (*)(RenderQueue*, const RenderQueueItem*, u32);

        struct RenderQueueItem {
            //function ptr handles how to draw the object
            RendererFunc m_rendererFunction;
            //extra data needed to draw the object
            void* m_renderInfo;
            //sort key
            u32 m_sortKey;
        };

        class RenderQueue {
        public:
            explicit RenderQueue(Device* d);
            ~RenderQueue() = default;

            void sort();
            void reset();

            void beginRenderPass();
            void endRenderPass();

            void setShaderProgram(ShaderProgram* p);

            void push();


            void draw(u32 startVertex, u32 count);
            void drawElements(u32 vertexCount, u32 indexOffset);

        private:
            Device* m_device;
            ShaderProgram* m_currentShp;
            std::vector<RenderQueueItem> m_queueItems;
        };
    }
}

#endif //DKR_RENDERQUEUE_H
