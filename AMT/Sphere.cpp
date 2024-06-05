#include "Sphere.h"

Sphere::Sphere(glm::vec3 position, glm::vec3 positionChange, int* globalSID, std::vector<Sphere>& antProjectiles, glm::vec3& playerPos, float playerWidth, float playerHeight, int* playerHp):
    _globalSID(globalSID), _antProjectiles(antProjectiles), _playerPos(playerPos) {
	_position = position;
    _posChange = positionChange;
	_travelCounter = 1024;
    _id = (*globalSID);
    (*globalSID)++;
    _playerWidth = playerWidth;
    playerHeight = playerHeight;
    _playerHp = playerHp;
    _range = 1.5f;
    _sectors = 10;
    _rings = 10;

    _vertices = generateVertices(_range, _rings, _sectors);
    _indices = generateIndices(_rings, _sectors);

    _vao.Bind();
    _vbo = new VBO(_vertices); // Dynamic allocation
    _ebo = new EBO(_indices); // Dynamic allocation

    _vao.LinkAttrib(*_vbo, 0, 3, GL_FLOAT, sizeof(glm::vec3), (void*)0);
    _vao.Unbind();
    _vbo->Unbind();
    _ebo->Unbind();
}

std::vector<glm::vec3> Sphere::generateVertices(float radius, unsigned int rings, unsigned int sectors) {
    std::vector<glm::vec3> vertices;
    const float PI = 3.14159265359f;
    const float R = 1.0f / (float)(rings - 1);
    const float S = 1.0f / (float)(sectors - 1);

    for (unsigned int r = 0; r < rings; ++r) {
        for (unsigned int s = 0; s < sectors; ++s) {
            float y = sin(-PI / 2.0 + PI * r * R);
            float x = cos(2.0 * PI * s * S) * sin(PI * r * R);
            float z = sin(2.0 * PI * s * S) * sin(PI * r * R);

            vertices.push_back({ x * radius, y * radius, z * radius });
        }
    }

    return vertices;
}

std::vector<unsigned int> Sphere::generateIndices(unsigned int rings, unsigned int sectors) {
    std::vector<unsigned int> indices;
    for (unsigned int r = 0; r < rings - 1; ++r) {
        for (unsigned int s = 0; s < sectors - 1; ++s) {
            indices.push_back(r * sectors + s);
            indices.push_back(r * sectors + (s + 1));
            indices.push_back((r + 1) * sectors + (s + 1));
            indices.push_back((r + 1) * sectors + (s + 1));
            indices.push_back((r + 1) * sectors + s);
            indices.push_back(r * sectors + s);
        }
    }

    return indices;
}
void Sphere::draw() {
    _vao.Bind();
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    _vao.Unbind();
}
/*
void drawSphere(VAO& vao, VBO& vbo, EBO& ebo, std::vector<glm::vec3>& vertices, std::vector<unsigned int>& indices)
{

    vao.Bind();
    
    vbo.Bind();
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    ebo.Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(glm::vec3), (void*)0);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    vao.Unbind();
}*/

void Sphere::move() {
    _position[0] += _posChange[0];
    _position[1] += _posChange[1];
    _position[2] += _posChange[2];
    _travelCounter--;
}

bool Sphere::collision() {
    if (_position[0]<_playerPos[0] + _playerWidth && _position[0]>_playerPos[0] - _playerWidth) {
        if (_position[2]<_playerPos[2] + _playerWidth && _position[2]>_playerPos[2] - _playerWidth) {
            if (_position[1] < _playerPos[1] + _playerHeight) {
                *_playerHp -= 20;
                return true;    //collision detected
            }
        }
    }
    return false;// no collision
}