#include"Player.h"

Player::Player(glm::vec3 position, CustomMutex& mtx, std::vector<AntGrunt>& enemies)
    :  _mtx(mtx), _enemies(enemies) {
    _hp = 100;
    _projectileDmg = 40;
    _meleeDmg = 60;
}

void Player::move() {
    
}

bool Player::collisionCheck() {
    for (const auto& enemy : _enemies) {
        //std::cout << enemy._position[0] << std::endl;
        float x1 = enemy._position[0] - enemy._width / 2;
        float x2 = enemy._position[0] + enemy._width / 2;
        float z1 = enemy._position[2] - enemy._width / 2;
        float z2 = enemy._position[2] + enemy._width / 2;
        if ((_position[0] > x1 && _position[0] < x2) && (_position[2] > z1 && _position[2] < z2)) {
            return true;
        }
    }
    return false;  // Brak kolizji
}