//
// Created by dan on 25/10/18.
//

#include "device.h"

using namespace dk::gfx;

Device::Device(int width, int height) {
    m_windowWidth = width;
    m_windowHeight = height;

    auto vendorString = glGetString(GL_VENDOR);
    auto deviceRenderer = glGetString(GL_RENDERER);
    auto deviceVersion = glGetString(GL_VERSION);

    m_deviceVendor = std::string((const char *) vendorString,
                                 std::strlen(reinterpret_cast<const char *>(vendorString)));
    m_deviceRenderer = std::string((const char *) deviceRenderer, std::strlen((const char *) deviceRenderer));
    m_deviceVersion = std::string((const char *) deviceVersion, std::strlen((const char *) deviceVersion));

    m_mask = GL_COLOR_BUFFER_BIT;
}

Device::~Device() {
}

void Device::clear() {
    glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Device::setWindowWidth(int w) {
    m_windowWidth = w;
}

int Device::getWindowWidth() {
    return m_windowWidth;
}

void Device::setWindowHeight(int h) {
    m_windowHeight = h;
}

int Device::getWindowHeight() {
    return m_windowHeight;
}

VertexBufferHandle Device::createVertexBuffer() {
    VertexBufferHandle h;

    for (auto i = 0u; i < m_vertexBuffers.size(); i++) {
        auto &vbo = m_vertexBuffers[i];
        if (!vbo.first) {
            //free spot
            vbo.first = new VertexBuffer();
            h.m_index = i;
            h.m_generation = vbo.second;

            return h;
        }
    }
    std::cerr << "Critical: No free vertex buffers\n"; //what now?
}

VertexBuffer &Device::accessVertexBuffer(VertexBufferHandle h) {
    assert(h.m_generation == m_vertexBuffers[h.m_index].second);
    return *(m_vertexBuffers[h.m_index].first);
}

void Device::deleteVertexBuffer(VertexBufferHandle h) {
    m_vertexBuffers[h.m_index].second++;
    delete m_vertexBuffers[h.m_index].first;
}

ElementBufferHandle Device::createElementBuffer() {
    ElementBufferHandle h;

    for (auto i = 0u; i < m_eleBuffers.size(); i++) {
        auto &ebo = m_eleBuffers[i];
        if (!ebo.first) {
            //free spot
            ebo.first = new ElementBuffer();
            h.m_index = i;
            h.m_generation = ebo.second;

            return h;
        }
    }
}

ElementBuffer &Device::accessElementBuffer(ElementBufferHandle h) {
    assert(h.m_generation == m_eleBuffers[h.m_index].second);
    return *(m_eleBuffers[h.m_index].first);
}

void Device::deleteElementBuffer(ElementBufferHandle h) {
    m_eleBuffers[h.m_index].second++;
    delete m_eleBuffers[h.m_index].first;
}

UniformBufferHandle Device::createUniformBuffer() {
    UniformBufferHandle h;

    for (auto i = 0u; i < m_uniformBuffers.size(); i++) {
        auto &ubo = m_uniformBuffers[i];
        if (!ubo.first) {
            //free spot
            ubo.first = new UniformBuffer();
            h.m_index = i;
            h.m_generation = ubo.second;

            return h;
        }
    }
}

UniformBuffer &Device::accessUniformBuffer(UniformBufferHandle h) {
    assert(h.m_generation == m_uniformBuffers[h.m_index].second);
    return *(m_uniformBuffers[h.m_index].first);
}

void Device::deleteUniformBuffer(UniformBufferHandle h) {
    m_uniformBuffers[h.m_index].second++;
    delete m_uniformBuffers[h.m_index].first;
}


ShaderHandle Device::createShader(GLenum type) {
    ShaderHandle h;

    for (auto i = 0u; i < m_shaders.size(); i++) {
        auto &sh = m_shaders[i];
        if (!sh.first) {
            //free spot
            sh.first = new Shader(type);
            h.m_index = i;
            h.m_generation = sh.second;

            return h;
        }
    }
}

ShaderHandle Device::createShader(GLenum type, std::string const& file) {
    ShaderHandle h;

    for (auto i = 0u; i < m_shaders.size(); i++) {
        auto &sh = m_shaders[i];
        if (!sh.first) {
            //free spot
            sh.first = new Shader(type, file);
            h.m_index = i;
            h.m_generation = sh.second;

            return h;
        }
    }
}


Shader &Device::accessShader(ShaderHandle h) {
    assert(h.m_generation == m_shaders[h.m_index].second);
    return *(m_shaders[h.m_index].first);
}

void Device::deleteShader(ShaderHandle h) {
    m_shaders[h.m_index].second++;
    delete m_shaders[h.m_index].first;
}

ShaderProgramHandle Device::createShaderProgram() {
    ShaderProgramHandle h;

    for (auto i = 0u; i < m_shaderPrograms.size(); i++) {
        auto &shp = m_shaderPrograms[i];
        if (!shp.first) {
            //free spot
            shp.first = new ShaderProgram();
            h.m_index = i;
            h.m_generation = shp.second;

            return h;
        }
    }
}

ShaderProgram &Device::accessShaderProgram(ShaderProgramHandle h) {
    assert(h.m_generation == m_shaderPrograms[h.m_index].second);
    return *(m_shaderPrograms[h.m_index].first);
}

void Device::deleteShaderProgram(ShaderProgramHandle h) {
    m_shaderPrograms[h.m_index].second++;
    delete m_shaderPrograms[h.m_index].first;
}

FramebufferHandle Device::createFramebuffer() {
    FramebufferHandle h;

    for (auto i = 0u; i < m_framebuffers.size(); i++) {
        auto &fb = m_framebuffers[i];
        if (!fb.first) {
            //free spot
            fb.first = new Framebuffer();
            h.m_index = i;
            h.m_generation = fb.second;

            return h;
        }
    }
}

Framebuffer &Device::accessFramebuffer(FramebufferHandle h) {
    assert(h.m_generation == m_framebuffers[h.m_index].second);
    return *(m_framebuffers[h.m_index].first);
}

void Device::deleteFramebuffer(FramebufferHandle h) {
    m_framebuffers[h.m_index].second++;
    delete m_framebuffers[h.m_index].first;
}

TextureHandle Device::createTexture() {
    TextureHandle h;

    for (auto i = 0u; i < m_textures.size(); i++) {
        auto &tx = m_textures[i];
        if (!tx.first) {
            //free spot
            tx.first = new Texture();
            h.m_index = i;
            h.m_generation = tx.second;

            return h;
        }
    }
}

Texture &Device::accessTexture(TextureHandle h) {
    assert(h.m_generation == m_textures[h.m_index].second);
    return *(m_textures[h.m_index].first);
}

void Device::deleteTexture(TextureHandle h) {
    m_textures[h.m_index].second++;
    delete m_textures[h.m_index].first;
}

MaterialHandle Device::createMaterial() {
    MaterialHandle h;

    for (auto i = 0u; i < m_materials.size(); i++) {
        auto &mat = m_materials[i];
        if (!mat.first) {
            //free spot
            mat.first = new Material(this);
            h.m_index = i;
            h.m_generation = mat.second;

            return h;
        }
    }
}

Material &Device::accessMaterial(MaterialHandle h) {
    if (h.m_generation != m_materials[h.m_index].second) {
        std::cerr << "Handle has gen " << h.m_generation << " but renderer has gen " << m_materials[h.m_index].second << '\n';
    }
    assert(h.m_generation == m_materials[h.m_index].second);
    return *(m_materials[h.m_index].first);
}

void Device::deleteMaterial(MaterialHandle h) {
    m_materials[h.m_index].second++;
    delete m_materials[h.m_index].first;
}

void Device::submit(CommandBuffer *buf) {
    buf->sort();
    for (const auto &el : buf->m_commands) {
		u64 key = std::get<0>(el);
		const DrawIndexed& d = std::get<1>(el);

        //set material
        MaterialHandle h;
        h.m_index = static_cast<u32>(key);
        h.m_generation = 0; //assume it's 0, no checks
        accessMaterial(h).bind();
		
		glDrawElements(GL_TRIANGLES, d.m_vertexCount, GL_UNSIGNED_INT, (void*)(d.m_startIndex * 3 * sizeof(u32)));
	}
    buf->clear();
}

VertexArrayConfig &Renderer::getVertexArrayConfig() {
    return m_vaoConfig;
}

