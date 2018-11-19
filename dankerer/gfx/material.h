//
// Created by dan on 27/10/18.
//

#ifndef DANKERER_MATERIAL_H
#define DANKERER_MATERIAL_H

#include "common.h"
#include "texture.h"

namespace dk {
    namespace gfx {
        class Renderer;
        enum class IlluminationModel {
            ConstantColour,
            LambertDiffuse,
            Phong
        };

        class Material {
        public:
            Material() = default;
            ~Material() = default;

            //set shaders, uniforms, textures...
            void bind(Renderer* rend);

            const std::string &getName() const;
            void setName(const std::string &name);

            float getSpecularExponent() const;
            void setSpecularExponent(float specularExponent);

            float getRefractiveIndex() const;
            void setRefractiveIndex(float refractiveIndex);

            float getOpacity() const;
            void setOpacity(float opacity);

            const glm::vec3& getTransmissionFilter() const;
            void setTransmissionFilter(const glm::vec3 &transmissionFilter);

            const glm::vec3& getAmbientColour() const;
            void setAmbientColour(const glm::vec3 &ambientColour);

            const glm::vec3 &getDiffuseColour() const;
            void setDiffuseColour(const glm::vec3 &diffuseColour);

            const glm::vec3 &getSpecularColour() const;
            void setSpecularColour(const glm::vec3 &specularColour);

            void addTexture(std::string const& fileName, TextureType tt, Renderer* rend);


            template <typename H>
            friend H AbslHashValue(H h, const Material& m) {
                return H::combine(std::move(h), m.m_name);
            }

        private:
            std::string m_name;
            float m_specularExponent;
            float m_refractiveIndex;
            float m_opacity;
            glm::vec3 m_transmissionFilter;

            glm::vec3 m_ambientColour;
            glm::vec3 m_diffuseColour;
            glm::vec3 m_specularColour;

            std::vector<TextureHandle> m_textures;
        };
    }
}


#endif //DANKERER_MATERIAL_H
