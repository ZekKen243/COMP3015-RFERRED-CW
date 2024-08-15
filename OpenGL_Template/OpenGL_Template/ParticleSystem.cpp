#include "ParticleSystem.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


ParticleSystem::ParticleSystem(unsigned int maxParticles) : maxParticles(maxParticles) {
    particles.resize(maxParticles);
    initializeParticles();
    setupVAO();
    setupVBO();
}

void ParticleSystem::initializeParticles() {
    for (unsigned int i = 0; i < maxParticles; ++i) {
        particles[i].position = glm::vec3((rand() % 100 - 50) / 10.0f, 10.0f, (rand() % 100 - 50) / 10.0f);
        particles[i].velocity = glm::vec3(0.0f, -1.0f, 0.0f);  // Falling down
        particles[i].lifetime = 5.0f;  // 5 seconds lifetime
    }
}

void ParticleSystem::Update(float deltaTime) {
    for (auto& particle : particles) {
        particle.position += particle.velocity * deltaTime;
        particle.lifetime -= deltaTime;
        if (particle.lifetime <= 0.0f) {
            particle.position = glm::vec3((rand() % 100 - 50) / 10.0f, 10.0f, (rand() % 100 - 50) / 10.0f);
            particle.lifetime = 5.0f;
        }
    }
    // Update vertex data
    particleVertices.clear();
    for (const auto& particle : particles) {
        particleVertices.push_back(particle.position);
    }

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, particleVertices.size() * sizeof(glm::vec3), particleVertices.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void ParticleSystem::Render(Shader& shader, const glm::mat4& viewProjectionMatrix) {
    shader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "viewProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix));

    glBindVertexArray(vao);
    glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(particleVertices.size()));
    glBindVertexArray(0);
}

void ParticleSystem::setupVAO() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, maxParticles * sizeof(glm::vec3), nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void ParticleSystem::setupVBO() {
    // VBO setup is done in setupVAO
}
