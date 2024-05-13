#include"Player.h"

Player::Player(glm::vec3 position, CustomMutex& mtx, std::vector<AntGrunt>& enemies, Camera& camera)
    : _position(position), _mtx(mtx), _enemies(enemies), _camera(camera) {
    _hp = 100;
    _projectileDmg = 40;
    _meleeDmg = 60;
    
}

void Player::move() {

}