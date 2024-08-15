#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include <vector>
#include <glm/glm.hpp>
#include "shaderClass.h"

class Particle {
public:
    glm::vec3 position;
    glm::vec3 velocity;
    float lifetime;  // Remaining lifetime of the particle
};

class ParticleSystem {
public:
    ParticleSystem(unsigned int maxParticles);
    void Update(float deltaTime);
    void Render(Shader& shader, const glm::mat4& viewProjectionMatrix);

private:
    unsigned int maxParticles;
    std::vector<Particle> particles;
    unsigned int vao, vbo;
    std::vector<glm::vec3> particleVertices;  // Vertices for each particle

    void initializeParticles();
    void setupVAO();
    void setupVBO();
};

#endif
