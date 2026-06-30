//
// Created by Akira Mujawar on 08/09/22.
//

#include "Vertex.hpp"

using MeowEngine::Vertex;

bool Vertex::operator==(const MeowEngine::Vertex &other) const {
    return Position == other.Position && TextureCoord == other.TextureCoord;
}