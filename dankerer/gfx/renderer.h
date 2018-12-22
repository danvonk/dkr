#pragma once

#include "scene.h"
#include "opengl/device.h"
#include "renderQueue.h"

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

			void begin();
			void pushToRenderQueue();
			void flush();

		private:
			Device* m_device;
			RendererType m_rendererType;
			RenderQueue m_rendQueue;
		};
	}
}