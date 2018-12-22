#include "sceneLoader.h"

using namespace dk::gfx;

SceneLoader::SceneLoader() {
    m_scene = std::make_unique<Scene>();
}

SceneLoader::~SceneLoader() {

}


Scene* SceneLoader::getScene() {
    return m_scene.get();
}

