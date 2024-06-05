#include "Crosshair.h"

float crosshairVertices[] = {
    // Positions
    -0.01f,  0.0f,
     0.01f,  0.0f,
     0.0f,  -0.01f,
     0.0f,   0.01f,
};

Crosshair::Crosshair() {
    setup();
}

Crosshair::~Crosshair() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Crosshair::setup() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(crosshairVertices), crosshairVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0); // Use location 4
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Crosshair::render(Shader& shader) {
    shader.Activate();
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 4);
    glBindVertexArray(0);
}
