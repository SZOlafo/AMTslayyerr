#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"EnemyState.cpp"
#include<glad/glad.h>
#include"CustomMutex.h"


#pragma once
class AntGrunt
{
private:
	enum AntGruntState {
		IDLE,
		WAKEUP
	};
	int _hp;
	int _meleeDmg;
	int _projectileDmg;
	int _attackTimer;
	AntGruntState _Enemy_state;
	CustomMutex& _mtx;
	std::vector<AntGrunt>& _enemies;
	

public:
	int* _globalAntID;
	int id;
	glm::vec3 _position;
	float _width;
	float _height;
	GLfloat coordinates[32];
	GLuint _indices[6];
	float dx;
	float dz;
	int directionTimer;
	glm::vec3& _playerPos;

	AntGrunt(glm::vec3 position, CustomMutex& mtx, std::vector<AntGrunt>& enemies, int* globalAntID, glm::vec3& playerPos);
	void Idle();
	void Attack();
	void Chase();
	void updateCoord();
	void AntGruntLoop();
	void ChooseDirection();
	bool collisionCheck();
};
 

