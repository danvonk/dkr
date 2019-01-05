#include "scene.h"

using namespace dk::gfx;

Scene::Scene() {
    m_testMesh = std::make_unique<StaticMesh>();
   /* auto mesh1 = m_registry.create();
    m_registry.assign<RenderComponent>(mesh1, m_testMesh.get());*/
}