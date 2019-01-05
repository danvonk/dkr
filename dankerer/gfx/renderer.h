#pragma once

#include "scene.h"
#include "opengl/device.h"
#include "commandBuffer.h"
#include "renderPass.h"

namespace dk {
	namespace gfx {
		class Renderer {
		public:
			enum class RendererType {
				Forward,
				Deferred
			};

			Renderer(RendererType t, Device* d);
			~Renderer() = default;

			CommandBuffer* getCommandBuffer() {
				return &m_cmdBuf;
			}

			void addRenderPass(RenderPass* p);
		private:
			Device* m_device;
			RendererType m_rendererType;
			CommandBuffer m_cmdBuf;

			std::vector<std::unique_ptr<RenderPass>> m_renderPasses;

			glm::mat4 m_view;
			glm::mat4 m_proj;
		};
	}
}