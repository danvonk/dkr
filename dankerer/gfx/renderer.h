//
// Created by dan on 25/10/18.
//

#ifndef DANKERER_RENDERER_H
#define DANKERER_RENDERER_H

#include "dankerer/base/short_alloc.h"
#include "common.h"
#include "camera.h"
#include "material.h"

#include <optional>

#include "vertexBuffer.h"
#include "elementBuffer.h"
#include "shader.h"
#include "shaderProgram.h"
#include "texture.h"
#include "uniformBuffer.h"
#include "commandBuffer.h"
#include "vertexArrayConfig.h"
#include "framebuffer.h"

namespace dk {
    namespace gfx {
        class Renderer {
        public:
            Renderer(int width, int height);
            ~Renderer();

            void setWindowWidth(int w);
            int getWindowWidth();

            void setWindowHeight(int h);
            int getWindowHeight();

            void submit(CommandBuffer* buf);
            void clear();

            VertexBufferHandle createVertexBuffer();
            VertexBuffer& accessVertexBuffer(VertexBufferHandle h);
            void deleteVertexBuffer(VertexBufferHandle h);

            //centralised memory management for render subsystem objects
            ElementBufferHandle createElementBuffer();
            ElementBuffer& accessElementBuffer(ElementBufferHandle h);
            void deleteElementBuffer(ElementBufferHandle h);

            UniformBufferHandle createUniformBuffer();
            UniformBuffer& accessUniformBuffer(UniformBufferHandle h);
            void deleteUniformBuffer(UniformBufferHandle h);

            ShaderHandle createShader(GLenum type);
            ShaderHandle createShader(GLenum type, absl::string_view file);
            Shader& accessShader(ShaderHandle h);
            void deleteShader(ShaderHandle h);

            ShaderProgramHandle createShaderProgram();
            ShaderProgram& accessShaderProgram(ShaderProgramHandle h);
            void deleteShaderProgram(ShaderProgramHandle h);

            FramebufferHandle createFramebuffer();
            Framebuffer& accessFramebuffer(FramebufferHandle h);
            void deleteFramebuffer(FramebufferHandle h);

            TextureHandle createTexture();
            Texture& accessTexture(TextureHandle h);
            void deleteTexture(TextureHandle h);

            MaterialHandle createMaterial();
            Material& accessMaterial(MaterialHandle h);
            void deleteMaterial(MaterialHandle h);

            VertexArrayConfig& getVertexArrayConfig();

        private:
            std::string m_deviceVendor;
            std::string m_deviceRenderer;
            std::string m_deviceVersion;

            VertexArrayConfig m_vaoConfig;

            //probably switch from standard new to an arena allocator
            std::array<std::pair<VertexBuffer*, u32>, 4096> m_vertexBuffers;
            std::array<std::pair<ElementBuffer*, u32>, 4096> m_eleBuffers;
            std::array<std::pair<UniformBuffer*, u32>, 4096> m_uniformBuffers;
            std::array<std::pair<Shader*, u32>, 4096> m_shaders;
            std::array<std::pair<ShaderProgram*, u32>, 4096> m_shaderPrograms;
            std::array<std::pair<Framebuffer*, u32>, 4096> m_framebuffers;
            std::array<std::pair<Texture*, u32>, 4096> m_textures;
            std::array<std::pair<Material*, u32>, 4096> m_materials;

            int m_windowWidth;
            int m_windowHeight;
            GLbitfield m_mask;
        };
    }
}


#endif //DANKERER_RENDERER_H
