//
// Created by dan on 21/12/18.
//

#ifndef DKR_RENDERQUEUE_H
#define DKR_RENDERQUEUE_H

#include "common.h"
#include "device.h"
#include "staticMesh.h"

namespace dk {
    namespace gfx {
        class RenderPass;
        class ElementBuffer;
    
		class CommandBuffer;
		struct RenderQueueItem;
        using RendererFunc = void (*)(CommandBuffer*, const RenderQueueItem*, u32);

        struct RenderQueueItem {
            //function ptr handles how to draw the object
            RendererFunc m_rendererFunction;
            //extra data needed to draw the object
            StaticMeshInfo m_renderInfo;
            //sort key
            u32 m_sortKey;
        };

        class CommandBuffer {
        public:
            explicit CommandBuffer(Device* d);
            ~CommandBuffer() = default;

            void sort();
            void execute();
            void flush();

            void beginRenderPass(RenderPass* rp);
            void endRenderPass();

            void setShaderProgram(ShaderProgram* p);
            void setVao(GLuint vao);
            void setElementBuffer(ElementBuffer* e);

			void push(u64 sortKey, RendererFunc rendFunc, StaticMeshInfo smi);

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
