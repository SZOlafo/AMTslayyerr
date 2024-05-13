#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glad/glad.h>
#include "Camera.h"
#include "CustomMutex.h"
#include "AntGrunt.h"
#ifndef PLAYER_H
#define PLAYER_H
#pragma once
class Player {
private:
	int _hp;
	int _meleeDmg;
	int _projectileDmg;
	
	//Camera& _camera;
	
	
	
public:
	glm::vec3 _position;
	CustomMutex& _mtx;
	std::vector<AntGrunt>& _enemies;
	float _width;
	float _height;
	float _dx;
	float _dz;

	Player(glm::vec3 position, CustomMutex& mtx, std::vector<AntGrunt>& enemies);
	void move();
	void shoot();
	void melee();
	bool collisionCheck();

};
#endif