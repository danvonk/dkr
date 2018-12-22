#pragma once

#include "common.h"
#include "scene.h"

namespace dk {
    namespace gfx {
        //load a glTF file and return a Scene class
        class SceneLoader {
        public:
            SceneLoader();
            ~SceneLoader();

            //load the glTF scene representation
            void loadFromFile(const std::string& path);

            //return a non-owning ptr to the loaded scene
            Scene* getScene();

        private:
            std::unique_ptr<Scene> m_scene;
        };
    }
}