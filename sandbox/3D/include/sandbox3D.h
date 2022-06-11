#pragma once
#include <glm.hpp>

#include "Man520.h"
#include "camera.h"


class Sandbox3D : public Man520::Layer {
    public:
        Sandbox3D();
        virtual ~Sandbox3D();

        virtual void onAttach() override;
        virtual void onDetach() override;
        virtual void onUpdate() override;
        virtual bool onEvent(SDL_Event& event) override;
    private:
        //temp :
        Man520::Ref<Man520::Shader> boxShader, lightCubeShader;
        Man520::Ref<Man520::Texture2D> texture1, texture2;
        Man520::Ref<Man520::VertexBuffer> boxVB;
        Man520::Ref<Man520::IndexBuffer> boxIB;
        Man520::Ref<Man520::VertexArray> boxVA, lightVA;
        Camera camera{glm::vec3(0.0f, 0.0f, 3.0f)};
        float mouseX = .0f, mouseY = .0f;
        glm::vec3 lightPos; //{1.2f, 1.0f, 2.0f};

        glm::vec3 cubePositions[10]; /* = {
                glm::vec3( 0.0f,  0.0f,  0.0f),
                glm::vec3( 2.0f,  5.0f, -15.0f),
                glm::vec3(-1.5f, -2.2f, -2.5f),
                glm::vec3(-3.8f, -2.0f, -12.3f),
                glm::vec3( 2.4f, -0.4f, -3.5f),
                glm::vec3(-1.7f,  3.0f, -7.5f),
                glm::vec3( 1.3f, -2.0f, -2.5f),
                glm::vec3( 1.5f,  2.0f, -2.5f),
                glm::vec3( 1.5f,  0.2f, -1.5f),
                glm::vec3(-1.3f,  1.0f, -1.5f)
        };*/
        float timeElpased = 0.0f;
        float deltatime = 0.0f;
        float fps = 0.0f;
        bool firstmouse = true;
        float fov = 45.0f;
        float wheelY = 0.0f;
        bool printFPS = false;
};
