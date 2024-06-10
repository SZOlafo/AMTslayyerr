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
	bool* _endGame;
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

	AntGrunt(glm::vec3 position, CustomMutex& mtx, std::vector<AntGrunt>& enemies, int* globalAntID, glm::vec3& playerPos, std::vector<Sphere>& antProjectiles, int* globalSID,CustomMutex& antProjectileMtx, float playerWidth, float playerHeight, int* playerHp, std::vector<VAO>& antsVao, std::vector<VBO>& antsVBO, std::vector<EBO>& antsEBO, CustomMutex& spawnMtx, bool& shooting, glm::vec3& cameraPos, glm::vec3& shotPos, std::barrier<>& sync, bool* endGame);
	void Idle();// runs when player was not spotted
	void Attack();
	void Chase();// chases player and deals damage when in proximity
	void Bite();
	void updateCoord();// updates location of enemy
	void AntGruntLoop(); // calls needed functions in a loop
	void ChooseDirection();// chooses direction in which to move when in Idle state
	bool collisionCheck();// checks collisions wiht player and other enemies
	bool shotCollision(const glm::vec3& cameraPos, const glm::vec3& shotPos);// checks if enemy was shot and deals damage to hit enemy
	void Die();// runs when hp<0
	void shot();
	void handleShooting();// thread which checks if enemy was shot
	void reset();// runs when game is restarted
};
 

