#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"EnemyState.cpp"
#include<glad/glad.h>
#include<barrier>
#include"CustomMutex.h"
#include"Sphere.h"

#pragma once
class AntGrunt
{
private:
	enum AntGruntState {
		IDLE,
		WAKEUP
	};
	int _meleeDmg;
	int _projectileDmg;
	int _attackTimer;
	AntGruntState _Enemy_state;
	CustomMutex& _mtx;
	CustomMutex& _projectileMtx;
	std::barrier<>& _sync;
	std::vector<AntGrunt>& _enemies;
	

public:
	bool& _shooting;
	int _hp;
	glm::vec3& _cameraPos;
	glm::vec3& _shotPos;
	std::vector<VAO>& _antsVAO;
	std::vector<VBO>& _antsVBO;
	std::vector<EBO>& _antsEbo;
	CustomMutex& _spawnMtx;
	int* _globalAntID;
	int id;
	int* _globalSID;
	glm::vec3 _position;
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

	AntGrunt(glm::vec3 position, CustomMutex& mtx, std::vector<AntGrunt>& enemies, int* globalAntID, glm::vec3& playerPos, std::vector<Sphere>& antProjectiles, int* globalSID,CustomMutex& antProjectileMtx, float playerWidth, float playerHeight, int* playerHp, std::vector<VAO>& antsVao, std::vector<VBO>& antsVBO, std::vector<EBO>& antsEBO, CustomMutex& spawnMtx, bool& shooting, glm::vec3& cameraPos, glm::vec3& shotPos, std::barrier<>& sync);
	void Idle();
	void Attack();
	void Chase();
	void Bite();
	void updateCoord();
	void AntGruntLoop();
	void ChooseDirection();
	bool collisionCheck();
	bool shotCollision(const glm::vec3& cameraPos, const glm::vec3& shotPos);
	void Die();
	void shot();
	void handleShooting();
};
 

