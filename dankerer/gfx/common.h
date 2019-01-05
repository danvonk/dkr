//
// Created by dan on 25/10/18.
//

#ifndef DANKERER_COMMON_H
#define DANKERER_COMMON_H

#define GLEW_STATIC

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

template <typename T, u32 n, u32 m>
struct GenericHandle {
    T m_index : n;
    T m_generation : m;
};

using VertexBufferHandle = GenericHandle<u32, 12, 20>;
using ElementBufferHandle = GenericHandle<u32, 12, 20>;
using UniformBufferHandle = GenericHandle<u32, 12, 20>;
using ShaderHandle = GenericHandle<u32, 12, 20>;
using ShaderProgramHandle = GenericHandle<u32, 12, 20>;
using FramebufferHandle = GenericHandle<u32, 12, 20>;
using TextureHandle = GenericHandle<u32, 12, 20>;
using MaterialHandle = GenericHandle<u32, 12, 20>;
using VertexLayoutHandle = GenericHandle<u32, 12, 20>;


//default vertex structure
//TODO: Let the material.xml file define this...
struct Vertex {
    Vertex()
    : position(glm::vec3())
    , normal(glm::vec3())
    , texCoord(glm::vec2())
    {}

    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

#endif //DANKERER_COMMON_H
