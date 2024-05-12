#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"EnemyState.cpp"
#include<glad/glad.h>
#include"CustomMutex.h"

class AntGrunt
{
private:
	int _hp;
	int _meleeDmg;
	int _projectileDmg;
	glm::vec3 _position;
	int _attackTimer;
	EnemyState _Enemy_state;
	CustomMutex& _mtx;
	std::vector<AntGrunt>& _enemies;
public:
	float _width;
	float _height;
	GLfloat coordinates[32];
	GLuint _indices[6];
	float dx;
	float dz;
	int directionTimer;
	AntGrunt(glm::vec3 position, CustomMutex& mtx, std::vector<AntGrunt>& enemies);
	void Idle();
	void Attack();
	void Chase();
	void updateCoord();
	void AntGruntLoop();
	void ChooseDirection();
	bool collisionCheck();
};

