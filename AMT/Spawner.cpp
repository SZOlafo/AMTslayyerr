#include "Spawner.h"
/*
Spawner::Spawner(glm::vec3 position, CustomMutex& mtx, std::vector<AntGrunt>& enemies, int* globalAntId, glm::vec3& playerPos, std::vector<Sphere>& antProjectiles, int* globalSID, CustomMutex& antProjectileMtx, float playerWidth, float playerHeight, int* playerHp, std::vector<VAO>& antsVao, std::vector<VBO>& antsVBO, std::vector<EBO>& antsEBO, CustomMutex& spawnMtx)
    : _position(position), _mtx(mtx), _enemies(enemies), _globalAntID(globalAntId), _playerPos(playerPos), _antProjectiles(antProjectiles), _globalSID(globalSID), _projectileMtx(antProjectileMtx), _antsVAO(antsVao), _antsVBO(antsVBO), _antsEbo(antsEBO), _spawnMtx(spawnMtx) {
    _height = 25.0f;
    _width = 20.0f;
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
}

void Spawner::spawnAnt(glm::vec3 antPos) {
    _spawnMtx.lock();
    AntGrunt antGrunt(antPos,_mtx,_enemies, _globalAntID,_playerPos,_antProjectiles,_globalSID,_projectileMtx,_playerWidth,_playerHeight,_playerHp, _antsVAO, _antsVBO, _antsEbo, _spawnMtx);
    _spawnMtx.unlock();
}
void Spawner::spawnerLoop(glm::vec3 antPos) {
    spawnAnt(antPos);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}*/