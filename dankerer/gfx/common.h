//
// Created by dan on 25/10/18.
//

#ifndef DANKERER_COMMON_H
#define DANKERER_COMMON_H

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

//default vertex structure
//TODO: Let the material.xml file define this...
struct Vertex {
    bool operator==(const Vertex& other) const {
        return position == other.position && normal == other.normal && texCoord == other.texCoord;
    }

    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

#endif //DANKERER_COMMON_H
