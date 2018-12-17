#pragma once

#include "scene.h"
#include "opengl/commandBuffer.h"

namespace dk {
	namespace gfx {
		class Renderer {
		public:
			enum class RendererType {
				Classic,
				Deferred
			};

			Renderer(RendererType t);
			~Renderer();

		private:
			Device* m_device;
			RendererType m_rendererType;
			CommandBuffer m_cmdBuffer;
		};
	}
}