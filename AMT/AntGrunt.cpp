#include"AntGrunt.h"
#include<random>
#include<glad/glad.h>
#include <thread>
AntGrunt::AntGrunt(glm::vec3 position) {
	AntGrunt::_hp = 60;
	AntGrunt::_meleeDmg = 20;
	AntGrunt::_attackTimer = 15;
	AntGrunt::_height = 25.0f;
	AntGrunt::_width = 20.0f;
	AntGrunt::_Enemy_state = IDLE;
	AntGrunt::_position = position;
    AntGrunt::_indices[0] = 0;
    AntGrunt::_indices[1] = 1;
    AntGrunt::_indices[2] = 2;
    AntGrunt::_indices[3] = 0;
    AntGrunt::_indices[4] = 2;
    AntGrunt::_indices[5] = 3;
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

void AntGrunt::Idle() {
	std::random_device rd; // Seed with a real random value, if available
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<float> distrib(-0.01, 0.01);

	float dx, dz;
	dx = distrib(gen);
	dz = distrib(gen);

    if (AntGrunt::_position[0] > 99 || AntGrunt::_position[0] < -99) {
        dz = -dz;
    }
    AntGrunt::_position[0] += dx;
    if (AntGrunt::_position[2] > 99 || AntGrunt::_position[2] < -99) {
        dz = -dz;
    }
    for (int i = 0; i < 1000; i++) {
       
         
        AntGrunt::_position[0] += dx;
        AntGrunt::_position[2] += dz;
        updateCoord();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

}

void AntGrunt::AntGruntLoop() {
    while (_hp > 0) {
        if(AntGrunt::_Enemy_state == IDLE)
        Idle();
        updateCoord();
        
    }
}
