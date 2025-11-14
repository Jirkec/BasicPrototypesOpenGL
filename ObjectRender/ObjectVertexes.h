#pragma once
#include "RenderObject.h"
#include <array>
//
//static const std::array<Vertex, 12> tetrahedron = 
//{ {
//        // Face 1 (Red)
//        { { -0.6f, -0.4f, 0.f }, { 1.f, 0.f, 0.f }, { 0.0f, 0.0f } },
//        { {  0.6f, -0.4f, 0.f }, { 1.f, 0.f, 0.f }, { 1.0f, 0.0f } },
//        { {   0.f,  0.6f,  0.f }, { 1.f, 0.f, 0.f }, { 0.5f, 1.0f } },
//
//        // Face 2 (Green)
//        { { -0.6f, -0.4f, 0.f }, { 0.f, 1.f, 0.f }, { 0.0f, 0.0f } },
//        { {  0.6f, -0.4f, 0.f }, { 0.f, 1.f, 0.f }, { 1.0f, 0.0f } },
//        { {   0.f,  0.f,  0.6f }, { 0.f, 1.f, 0.f }, { 0.5f, 1.0f } },
//
//        // Face 3 (Blue)
//        { {  0.6f, -0.4f, 0.f }, { 0.f, 0.f, 1.f }, { 1.0f, 0.0f } },
//        { {   0.f,  0.6f,  0.f }, { 0.f, 0.f, 1.f }, { 0.5f, 1.0f } },
//        { {   0.f,  0.f,  0.6f }, { 0.f, 0.f, 1.f }, { 0.0f, 0.0f } },
//
//        // Face 4 (Yellow)
//        { {   0.f,  0.6f,  0.f }, { 1.f, 1.f, 0.f }, { 0.5f, 1.0f } },
//        { { -0.6f, -0.4f, 0.f }, { 1.f, 1.f, 0.f }, { 0.0f, 0.0f } },
//        { {   0.f,  0.f,  0.6f }, { 1.f, 1.f, 0.f }, { 1.0f, 0.0f } },
//} };

static const Vertex tetrahedron[] = {
    // Face 1 (Red)
    { { -0.6f, -0.4f, 0.f }, { 1.f, 0.f, 0.f }, { 0.0f, 0.0f } },
    { {  0.6f, -0.4f, 0.f }, { 1.f, 0.f, 0.f }, { 1.0f, 0.0f } },
    { {   0.f,  0.6f,  0.f }, { 1.f, 0.f, 0.f }, { 0.5f, 1.0f } },

    // Face 2 (Green)
    { { -0.6f, -0.4f, 0.f }, { 0.f, 1.f, 0.f }, { 0.0f, 0.0f } },
    { {  0.6f, -0.4f, 0.f }, { 0.f, 1.f, 0.f }, { 1.0f, 0.0f } },
    { {   0.f,  0.f,  0.6f }, { 0.f, 1.f, 0.f }, { 0.5f, 1.0f } },

    // Face 3 (Blue)
    { {  0.6f, -0.4f, 0.f }, { 0.f, 0.f, 1.f }, { 1.0f, 0.0f } },
    { {   0.f,  0.6f,  0.f }, { 0.f, 0.f, 1.f }, { 0.5f, 1.0f } },
    { {   0.f,  0.f,  0.6f }, { 0.f, 0.f, 1.f }, { 0.0f, 0.0f } },

    // Face 4 (Yellow)
    { {   0.f,  0.6f,  0.f }, { 1.f, 1.f, 0.f }, { 0.5f, 1.0f } },
    { { -0.6f, -0.4f, 0.f }, { 1.f, 1.f, 0.f }, { 0.0f, 0.0f } },
    { {   0.f,  0.f,  0.6f }, { 1.f, 1.f, 0.f }, { 1.0f, 0.0f } },
};

static const Vertex cube[] = {
    // Front face (red)
    //triangle 1
    { { -0.5f, -0.5f,  0.5f }, { 1.f, 0.f, 0.f }, { 0.0f, 0.0f } }, // bottom-left
    { {  0.5f, -0.5f,  0.5f }, { 1.f, 0.f, 0.f }, { 1.0f, 0.0f } }, // bottom-right
    { {  0.5f,  0.5f,  0.5f }, { 1.f, 0.f, 0.f }, { 1.0f, 1.0f } }, // top-right
    //triangle 2
    { { -0.5f, -0.5f,  0.5f }, { 1.f, 0.f, 0.f }, { 0.0f, 0.0f } }, // bottom-left
    { {  0.5f,  0.5f,  0.5f }, { 1.f, 0.f, 0.f }, { 1.0f, 1.0f } }, // top-right
    { { -0.5f,  0.5f,  0.5f }, { 1.f, 0.f, 0.f }, { 0.0f, 1.0f } }, // top-left

    // Back face (green)
    { {  0.5f, -0.5f, -0.5f }, { 0.f, 1.f, 0.f }, { 1.0f, 0.0f } }, // bottom-right
    { { -0.5f, -0.5f, -0.5f }, { 0.f, 1.f, 0.f }, { 0.0f, 0.0f } }, // bottom-left
    { { -0.5f,  0.5f, -0.5f }, { 0.f, 1.f, 0.f }, { 0.0f, 1.0f } }, // top-left
    { {  0.5f, -0.5f, -0.5f }, { 0.f, 1.f, 0.f }, { 1.0f, 0.0f } }, // bottom-right
    { { -0.5f,  0.5f, -0.5f }, { 0.f, 1.f, 0.f }, { 0.0f, 1.0f } }, // top-left
    { {  0.5f,  0.5f, -0.5f }, { 0.f, 1.f, 0.f }, { 1.0f, 1.0f } }, // top-right

    // Left face (blue)
    { { -0.5f, -0.5f, -0.5f }, { 0.f, 0.f, 1.f }, { 0.0f, 0.0f } }, // bottom-back
    { { -0.5f, -0.5f,  0.5f }, { 0.f, 0.f, 1.f }, { 1.0f, 0.0f } }, // bottom-front
    { { -0.5f,  0.5f,  0.5f }, { 0.f, 0.f, 1.f }, { 1.0f, 1.0f } }, // top-front
    { { -0.5f, -0.5f, -0.5f }, { 0.f, 0.f, 1.f }, { 0.0f, 0.0f } }, // bottom-back
    { { -0.5f,  0.5f,  0.5f }, { 0.f, 0.f, 1.f }, { 1.0f, 1.0f } }, // top-front
    { { -0.5f,  0.5f, -0.5f }, { 0.f, 0.f, 1.f }, { 0.0f, 1.0f } }, // top-back

    // Right face (yellow)
    { { 0.5f, -0.5f,  0.5f }, { 1.f, 1.f, 0.f }, { 0.0f, 0.0f } }, // bottom-front
    { { 0.5f, -0.5f, -0.5f }, { 1.f, 1.f, 0.f }, { 1.0f, 0.0f } }, // bottom-back
    { { 0.5f,  0.5f, -0.5f }, { 1.f, 1.f, 0.f }, { 1.0f, 1.0f } }, // top-back
    { { 0.5f, -0.5f,  0.5f }, { 1.f, 1.f, 0.f }, { 0.0f, 0.0f } }, // bottom-front
    { { 0.5f,  0.5f, -0.5f }, { 1.f, 1.f, 0.f }, { 1.0f, 1.0f } }, // top-back
    { { 0.5f,  0.5f,  0.5f }, { 1.f, 1.f, 0.f }, { 0.0f, 1.0f } }, // top-front

    // Top face (magenta)
    { { -0.5f,  0.5f,  0.5f }, { 1.f, 0.f, 1.f }, { 0.0f, 0.0f } }, // front-left
    { {  0.5f,  0.5f,  0.5f }, { 1.f, 0.f, 1.f }, { 1.0f, 0.0f } }, // front-right
    { {  0.5f,  0.5f, -0.5f }, { 1.f, 0.f, 1.f }, { 1.0f, 1.0f } }, // back-right
    { { -0.5f,  0.5f,  0.5f }, { 1.f, 0.f, 1.f }, { 0.0f, 0.0f } }, // front-left
    { {  0.5f,  0.5f, -0.5f }, { 1.f, 0.f, 1.f }, { 1.0f, 1.0f } }, // back-right
    { { -0.5f,  0.5f, -0.5f }, { 1.f, 0.f, 1.f }, { 0.0f, 1.0f } }, // back-left

    // Bottom face (cyan)
    { { -0.5f, -0.5f, -0.5f }, { 0.f, 1.f, 1.f }, { 0.0f, 1.0f } }, // back-left
    { {  0.5f, -0.5f, -0.5f }, { 0.f, 1.f, 1.f }, { 1.0f, 1.0f } }, // back-right
    { {  0.5f, -0.5f,  0.5f }, { 0.f, 1.f, 1.f }, { 1.0f, 0.0f } }, // front-right
    { { -0.5f, -0.5f, -0.5f }, { 0.f, 1.f, 1.f }, { 0.0f, 1.0f } }, // back-left
    { {  0.5f, -0.5f,  0.5f }, { 0.f, 1.f, 1.f }, { 1.0f, 0.0f } }, // front-right
    { { -0.5f, -0.5f,  0.5f }, { 0.f, 1.f, 1.f }, { 0.0f, 0.0f } }, // front-left
};
