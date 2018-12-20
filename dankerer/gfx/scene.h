#pragma once

#include "entt/entt.hpp"
namespace dk {
	namespace gfx {

		class Scene {
		public:
			Scene() = default;
			~Scene() = default;

		private:
		    entt::registry m_sceneEntities;
		};
	}
}