#pragma once

#include "common.h"
#include "entt/entity/registry.hpp"
#include "staticMesh.h"

namespace dk {
	namespace gfx {
	    class StaticMesh;
		struct RenderComponent {
			StaticMesh* m_mesh;
		};

		struct PhysicalObjectComponent {
			glm::vec3 m_position;
			float m_velocity;
		};

		class Scene {
		public:
		    Scene();
			~Scene() = default;

		private:
		    entt::DefaultRegistry m_registry;
		    std::unique_ptr<StaticMesh> m_testMesh; //just for now, till glTF loader is done
		};
	}
}