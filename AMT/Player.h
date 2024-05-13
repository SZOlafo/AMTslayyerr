#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"EnemyState.cpp"
#include<glad/glad.h>
#include "Camera.h"
#include "CustomMutex.h"
#include <vector>
#include "AntGrunt.h"

class Player {
private:
	int _hp;
	int _meleeDmg;
	int _projectileDmg;
	glm::vec3 _position;
	Camera& _camera;
	CustomMutex& _mtx;
	std::vector<AntGrunt>& _enemies;
	
public:
	float _width;
	float _height;
	float _dx;
	float _dz;

	Player(glm::vec3 position, CustomMutex& mtx, std::vector<AntGrunt>& enemies, Camera& camera);
	void move();
	void shoot();
	void melee();

};