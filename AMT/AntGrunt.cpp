#include"AntGrunt.h"
#include"CustomMutex.h"
#include<random>
#include<glad/glad.h>
#include <thread>
#include "glm/vec3.hpp"
#include <GLFW/glfw3.h>
AntGrunt::AntGrunt(glm::vec3 position, CustomMutex& mtx, std::vector<AntGrunt>& enemies, int* globalAntId, glm::vec3& playerPos, std::vector<Sphere>& antProjectiles,int* globalSID, CustomMutex& antProjectileMtx, float playerWidth, float playerHeight, int* playerHp, std::vector<VAO>& antsVao, std::vector<VBO>& antsVBO, std::vector<EBO>& antsEBO, CustomMutex& spawnMtx, bool& shooting, glm::vec3& cameraPos, glm::vec3& shotPos, std::barrier<>& sync)
    : _position(position), _mtx(mtx), _enemies(enemies), _globalAntID(globalAntId), _playerPos(playerPos), _antProjectiles(antProjectiles), _globalSID(globalSID), _projectileMtx(antProjectileMtx), _antsVAO(antsVao), _antsVBO(antsVBO), _antsEbo(antsEBO), _spawnMtx(spawnMtx), _shooting(shooting), _cameraPos(cameraPos), _shotPos(shotPos), _sync(sync)  { 
    _hp = 100;
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
    id = (*globalAntId);
    (*globalAntId)++;
    _playerWidth = playerWidth;
    _playerHeight = playerHeight;
    _playerHp = playerHp;
    /*GLfloat vertices[] =
    { //     COORDINATES     /        COLORS      /   TexCoord  //
        -100.0f, 0.0f,  100.0f,     0.5f, 0.5f, 0.5f,    0.0f, 1.0f, // Lewy górny
        -100.0f, 0.0f, -100.0f,     0.5f, 0.5f, 0.5f,    0.0f, 0.0f, // Lewy dolny
         100.0f, 0.0f, -100.0f,     0.5f, 0.5f, 0.5f,    1.0f, 0.0f, // Prawy dolny
         100.0f, 0.0f,  100.0f,     0.5f, 0.5f, 0.5f,    1.0f, 1.0f  // Prawy górny
         
    };

    // Indices for vertices order
    GLuint indices[] =
    {
        0, 1, 2, // Pierwszy trójk¹t
        0, 2, 3  // Drugi trójk¹t
       
    };

    VAO VAO1;
    VAO1.Bind();

    // Generates Vertex Buffer Object and links it to vertices
    VBO VBO1(vertices, sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    EBO EBO1(indices, sizeof(indices));

    // Links VBO attributes such as coordinates and colors to VAO
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();
    antsVao.push_back(VAO1);
    antsVBO.push_back(VBO1);
    antsEBO.push_back(EBO1);*/
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
        if (enemy._globalAntID != _globalAntID) {
            //std::cout << enemy._position[0] << std::endl;
            float x1 = enemy._position[0] - enemy._width / 2;
            float x2 = enemy._position[0] + enemy._width / 2;
            float z1 = enemy._position[2] - enemy._width / 2;
            float z2 = enemy._position[2] + enemy._width / 2;
            if ((_position[0] > x1 && _position[0] < x2) && (_position[2] > z1 && _position[2] < z2)) {
                return true;
            }
        }
    }
    //std::cout << enemy._position[0] << std::endl;
    float x1 = _playerPos[0] - 10;
    float x2 = _playerPos[2] + 10;
    float z1 = _playerPos[0] - 10;
    float z2 = _playerPos[2] + 10;
    if ((_position[0] > x1 && _position[0] < x2) && (_position[2] > z1 && _position[2] < z2)) {
        return true;
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
        _enemies[id]._position = _position;
        //std::cout << _enemies[*_globalAntID]._position[0] << std::endl;
    }
    else directionTimer = -1;
    directionTimer--;
    AntGrunt::_mtx.unlock();
    std::this_thread::sleep_for(std::chrono::nanoseconds(100));

}

void AntGrunt::Attack() {
    _projectileMtx.lock();
    glm::vec3 misslePos = { _position[0] + 10,_height,_position[2] };
    glm::vec3 posChange = { _playerPos[0] - misslePos[0],_playerPos[1] - misslePos[1],_playerPos[2] - misslePos[2] };
    Sphere sphere = Sphere(misslePos,posChange,_globalSID,_antProjectiles,_playerPos, _playerWidth,_playerHeight, _playerHp);
    _antProjectiles.push_back(sphere);
    _projectileMtx.unlock();
}
void AntGrunt::Chase() {
    _mtx.lock();
    if (_playerPos[0] > _position[0]) {
        dx = 1.0;
    }
    else {
        dx = -1.0;
    }
    if (_playerPos[2] > _position[2]) {
        dz = 1.0;
    }
    else {
        dz = -1.0;
    }
    bool check = collisionCheck();
    if (check == false) {
        AntGrunt::_position[0] += dx;
        AntGrunt::_position[2] += dz;
        _enemies[id]._position = _position;
        updateCoord();
        //std::cout << _enemies[*_globalAntID]._position[0] << std::endl;
    }
    else {
        _playerHp -= 20;
    }
    _mtx.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}
void AntGrunt::Bite() {
    if (((_playerPos[0] - _position[0] < 1.0) && (_playerPos[0] - _position[0] > -1.0)) && ((_playerPos[2] - _position[2] < 1.0) && (_playerPos[2] - _position[2] > -1.0)));
    _playerHp -= 20;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}
bool AntGrunt::shotCollision(const glm::vec3& rayOrigin, const glm::vec3& rayDirection) {
    glm::vec3 min = _position - glm::vec3(_width / 2, 0, _width / 2);
    glm::vec3 max = _position + glm::vec3(_width / 2, _height, _width / 2);

    float tmin = (min.x - rayOrigin.x) / rayDirection.x;
    float tmax = (max.x - rayOrigin.x) / rayDirection.x;

    if (tmin > tmax) std::swap(tmin, tmax);

    float tymin = (min.y - rayOrigin.y) / rayDirection.y;
    float tymax = (max.y - rayOrigin.y) / rayDirection.y;

    if (tymin > tymax) std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
        tmin = tymin;

    if (tymax < tmax)
        tmax = tymax;

    float tzmin = (min.z - rayOrigin.z) / rayDirection.z;
    float tzmax = (max.z - rayOrigin.z) / rayDirection.z;

    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    return true;
}
void AntGrunt::Die() {
    glm::vec3 currPos = _position;
    _position[0] = -1000.0f;
    _position[1] = -1000.0f;
    _position[2] = -1000.0f;
    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::uniform_int_distribution<> distr(1, 5);

    int randomInt = distr(gen);
    std::this_thread::sleep_for(std::chrono::seconds(randomInt));
    _hp = 100;
    _position = currPos;
}
void AntGrunt::shot() {
    _hp -= 20;
    std::cout << _hp << std::endl;
    if (_hp < 1) {
        AntGrunt::Die();
    }
}
void AntGrunt::handleShooting() {
    bool changed = true;
    while (true) {
        if (_shooting && changed) {
            changed = false;
            std::cout << "SHOOTING" << std::endl;
            if (shotCollision(_cameraPos, _shotPos)) {
                shot();
            }
        }
        if (_shooting == false) {
            changed = true;
        }
        //std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
void AntGrunt::AntGruntLoop() {
    //calculate how long should one frame take 
    const int targetFPS = 60;
    const double frameDuration = 1.0 / targetFPS;
    ///////////////////////
    std::thread shootingThread(&AntGrunt::handleShooting, this);
    while (1) {
        double startTime = glfwGetTime();
        if (AntGrunt::_Enemy_state == IDLE) {
            if (directionTimer < 0) {
                std::cout << directionTimer << std::endl;
                ChooseDirection();
                directionTimer = 100000;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                _Enemy_state = WAKEUP;
            }
            Idle();
        }
        if (_Enemy_state == WAKEUP) {
            Chase();
            /*if (_shooting) {
                std::cout << "SHOOTING" << std::endl;
                if (shotCollision(_cameraPos, _shotPos)) {
                    shot();
                }
            }*/
        }
        //updateCoord();
        //_sync.arrive_and_wait();
        //max 60fps
        double frameTime = glfwGetTime() - startTime;
        if (frameTime < frameDuration) {
            std::this_thread::sleep_for(std::chrono::milliseconds((int)((frameDuration - frameTime) * 1000)));
        }
    }
    shootingThread.join();
}
