#pragma once
/*
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<thread>
#include<functional>
#include<vector>
#include "AntGrunt.h"

class Spawner {
public:
	glm::vec3 _position;
	int* _globalAntID;
	int id;
	int* _globalSID;
	float _width;
	float _height;
	GLfloat coordinates[32];
	GLuint _indices[6];
	float dx;
	float dz;
	int directionTimer;
	glm::vec3& _playerPos;
	std::vector<Sphere>& _antProjectiles;
	float _playerWidth;
	float _playerHeight;
	int* _playerHp;
	CustomMutex& _mtx;
	CustomMutex& _projectileMtx;
	std::vector<AntGrunt>& _enemies;
	std::vector<VAO>& _antsVAO;
	std::vector<VBO>& _antsVBO;
	std::vector<EBO>& _antsEbo;
	CustomMutex& _spawnMtx;



	Spawner(glm::vec3 position, CustomMutex& mtx, std::vector<AntGrunt>& enemies, int* globalAntID, glm::vec3& playerPos, std::vector<Sphere>& antProjectiles, int* globalSID, CustomMutex& antProjectileMtx, float playerWidth, float playerHeight, int* playerHp, std::vector<VAO>& antsVao, std::vector<VBO>& antsVBO, std::vector<EBO>& antsEBO, CustomMutex& spawnMtx);
	void spawnAnt(glm::vec3 antPos);
	void spawnerLoop(glm::vec3 antPos);
};*/