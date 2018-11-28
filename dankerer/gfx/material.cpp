//
// Created by dan on 27/10/18.
//

#include "material.h"
#include "renderer.h"

using namespace dk::gfx;

Material::Material(Renderer *rend)
 : m_renderer(rend)
{
    m_shp = rend->createShaderProgram();
}


Material::~Material() {

}

const std::string& Material::getName() const {
    return m_name;
}

void Material::setName(const std::string &name) {
    Material::m_name = name;
}

float Material::getSpecularExponent() const {
    return m_specularExponent;
}

void Material::setSpecularExponent(float specularExponent) {
    Material::m_specularExponent = specularExponent;
}

float Material::getRefractiveIndex() const {
    return m_refractiveIndex;
}

void Material::setRefractiveIndex(float refractiveIndex) {
    Material::m_refractiveIndex = refractiveIndex;
}

float Material::getOpacity() const {
    return m_opacity;
}

void Material::setOpacity(float opacity) {
    Material::m_opacity = opacity;
}

const glm::vec3 &Material::getTransmissionFilter() const {
    return m_transmissionFilter;
}

void Material::setTransmissionFilter(const glm::vec3 &transmissionFilter) {
    Material::m_transmissionFilter = transmissionFilter;
}

const glm::vec3 &Material::getAmbientColour() const {
    return m_ambientColour;
}

void Material::setAmbientColour(const glm::vec3 &ambientColour) {
    Material::m_ambientColour = ambientColour;
}

const glm::vec3 &Material::getDiffuseColour() const {
    return m_diffuseColour;
}

void Material::setDiffuseColour(const glm::vec3 &diffuseColour) {
    Material::m_diffuseColour = diffuseColour;
}

const glm::vec3 &Material::getSpecularColour() const {
    return m_specularColour;
}

void Material::setSpecularColour(const glm::vec3 &specularColour) {
    Material::m_specularColour = specularColour;
}

void Material::bind() {
    m_renderer->accessShaderProgram(m_shp).link(m_renderer);
    if (!m_textures.empty()) {
        //just the first texture for now...
        m_renderer->accessTexture(m_textures[0]).bind(0);
    }
}

void Material::addTexture(std::string fileName, TextureType tt, Renderer* rend) {
    std::replace(fileName.begin(), fileName.end(), '\\', '/');
    auto relPath = absl::StrCat("dankerer/resources" ,fileName);

    auto txHandle = rend->createTexture();
    rend->accessTexture(txHandle).loadImage(relPath, tt);
    m_textures.push_back(txHandle);
}

void Material::addShader(ShaderHandle sh) {
    m_shaders.push_back(sh);
    m_renderer->accessShader(sh).compile();
    m_renderer->accessShaderProgram(m_shp).addShader(sh, m_renderer);
}

