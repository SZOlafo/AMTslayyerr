#include"AntGrunt.h"
#include"CustomMutex.h"
#include<random>
#include<glad/glad.h>
#include <thread>
#include "glm/vec3.hpp"
#include <GLFW/glfw3.h>
AntGrunt::AntGrunt(glm::vec3 position, CustomMutex& mtx, std::vector<AntGrunt>& enemies)
    : _position(position), _mtx(mtx), _enemies(enemies) { 
    _hp = 60;
    _meleeDmg = 20;
    _attackTimer = 15;
    _height = 25.0f;
    _width = 20.0f;
    _Enemy_state = IDLE;
    _indices[0] = 0;
    _indices[1] = 1;
    _indices[2] = 2;
    _indices[3] = 0;
    _indices[4] = 2;
    _indices[5] = 3;
    directionTimer = -1;
}

//aktualizacjia wspó³rzêdnym potrzebnych do rysowania przeciwnika
void AntGrunt::updateCoord() {
    float halfWidth = _width / 2.0f;

    // Lewy górny wierzcho³ek
    coordinates[0] = _position[0] - halfWidth; // X
    coordinates[1] = _position[1] + _height; // Y
    coordinates[2] = _position[2]; // Z
    coordinates[3] = 0.5f; // R
    coordinates[4] = 0.0f; // G
    coordinates[5] = 0.0f; // B
    coordinates[6] = 0.0f; // Wspó³rzêdna tekstury X
    coordinates[7] = 1.0f; // Wspó³rzêdna tekstury Y

    // Lewy dolny wierzcho³ek
    coordinates[8] = _position[0] - halfWidth; // X
    coordinates[9] = _position[1]; //+_height; // Y
    coordinates[10] = _position[2]; // Z
    coordinates[11] = 0.5f; // R
    coordinates[12] = 0.0f; // G
    coordinates[13] = 0.0f; // B
    coordinates[14] = 0.0f; // Wspó³rzêdna tekstury X
    coordinates[15] = 0.0f; // Wspó³rzêdna tekstury Y

    // Prawy dolny wierzcho³ek
    coordinates[16] = _position[0] + halfWidth; // X
    coordinates[17] = _position[1];// + _height; // Y
    coordinates[18] = _position[2]; // Z
    coordinates[19] = 0.5f; // R
    coordinates[20] = 0.0f; // G
    coordinates[21] = 0.0f; // B
    coordinates[22] = 1.0f; // Wspó³rzêdna tekstury X
    coordinates[23] = 0.0f; // Wspó³rzêdna tekstury Y

    // Prawy górny wierzcho³ek
    coordinates[24] = _position[0] + halfWidth; // X
    coordinates[25] = _position[1] +_height; // Y
    coordinates[26] = _position[2]; // Z
    coordinates[27] = 0.5f; // R
    coordinates[28] = 0.0f; // G
    coordinates[29] = 0.0f; // B
    coordinates[30] = 1.0f; // Wspó³rzêdna tekstury X
    coordinates[31] = 1.0f; // Wspó³rzêdna tekstury Y
}

void AntGrunt::ChooseDirection() {
    std::random_device rd; // Seed with a real random value, if available
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<float> distrib(-0.15, 0.15);

    
    dx = distrib(gen);
    dz = distrib(gen);
}

bool AntGrunt::collisionCheck() {
    for (const auto& enemy : _enemies) {
        
        /*if (std::abs(_position[0] - enemy._position[0]) < (_width / 2 + enemy._width / 2) &&
            std::abs(_position[2] - enemy._position[2]) < (_height / 2 + enemy._height / 2)) {
            return true;  // Kolizja wykryta
        }*/
        if ((_position[0] - _width / 2 > enemy._position[0] - enemy._width / 2) && (_position[0] + _width / 2 < enemy._position[0] + enemy._width / 2)
            /* && _position[2] == enemy._position[2]) */){
            return true; // kolizja wykryta
        }
    }
    return false;  // Brak kolizji
}
void AntGrunt::Idle() {
    AntGrunt::_mtx.lock();
	

    if (AntGrunt::_position[0] > 99 || AntGrunt::_position[0] < -99) {
        dx = -dx;
    }
    AntGrunt::_position[0] += dx;
    if (AntGrunt::_position[2] > 99 || AntGrunt::_position[2] < -99) {
        dz = -dz;
    }
    bool check = collisionCheck();
    if (check == false) {
        AntGrunt::_position[0] += dx;
        AntGrunt::_position[2] += dz;
    }
    else directionTimer = -1;
    directionTimer--;
    AntGrunt::_mtx.unlock();
    std::this_thread::sleep_for(std::chrono::nanoseconds(100));

}

void AntGrunt::AntGruntLoop() {
    //obliczenie ile ma trwaæ klatka aby osi¹gn¹æ max 60fps
    const int targetFPS = 60;
    const double frameDuration = 1.0 / targetFPS;
    ///////////////////////
    while (_hp > 0) {
        double startTime = glfwGetTime();
        if (AntGrunt::_Enemy_state == IDLE) {
            if (directionTimer < 0) {
                std::cout << directionTimer << std::endl;
                ChooseDirection();
                directionTimer = 100000;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            Idle();
        }
        updateCoord();

        //ograniczenie do max 60fps
        double frameTime = glfwGetTime() - startTime;
        if (frameTime < frameDuration) {
            std::this_thread::sleep_for(std::chrono::milliseconds((int)((frameDuration - frameTime) * 1000)));
        }
    }
}
