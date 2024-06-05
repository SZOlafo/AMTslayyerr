#ifndef CROSSHAIR_H
#define CROSSHAIR_H

#include <glad/glad.h>
#include "shaderClass.h"

class Crosshair {
public:
    Crosshair();
    ~Crosshair();
    void render(Shader& shader);

private:
    unsigned int VAO, VBO;
    void setup();
};

#endif
