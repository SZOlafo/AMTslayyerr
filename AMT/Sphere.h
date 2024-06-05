#include <vector>
#include <cmath>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "EBO.h"
#include "VAO.h"

#pragma once
class Sphere {
public:
	glm::vec3 _position;
	glm::vec3 _posChange;
	float _range;
	unsigned int _rings;
	unsigned int _sectors;
	int _travelCounter;
	std::vector<Sphere>& _antProjectiles;
	glm::vec3& _playerPos;
	int* _globalSID;
	int _id;
	float _playerWidth;
	float _playerHeight;
	int* _playerHp;

	VAO _vao;
	VBO* _vbo; 
	EBO* _ebo;
	std::vector<glm::vec3> _vertices;
	std::vector<unsigned int> _indices;

	Sphere(glm::vec3 position, glm::vec3 positionChange, int* globalSID, std::vector<Sphere>& antProjectiles, glm::vec3& playerPos, float playerWidth, float playerHeight, int* playerHp);
	std::vector<glm::vec3> generateVertices(float radius, unsigned int rings, unsigned int sectors);
	std::vector<unsigned int> generateIndices(unsigned int rings, unsigned int sectors);
	//void drawSphere(VAO& vao, VBO& vbo, EBO& ebo, std::vector<glm::vec3>& vertices, std::vector<unsigned int>& indices);
	void draw();
	void move();
	bool collision();
};