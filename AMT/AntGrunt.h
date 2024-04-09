#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"EnemyState.cpp"
#include<glad/glad.h>

class AntGrunt
{
private:
	int _hp;
	int _meleeDmg;
	int _projectileDmg;
	float _width;
	float _height;
	glm::vec3 _position;
	int _attackTimer;
	EnemyState _Enemy_state;
public:
	GLfloat coordinates[32];
	GLuint _indices[6];
	AntGrunt(glm::vec3 position);
	void Idle();
	void Attack();
	void Chase();
	void updateCoord();
	void AntGruntLoop();
};

