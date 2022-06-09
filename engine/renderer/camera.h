#pragma once

#include <glm/glm.hpp>

namespace Man520 {

    class Camera {
        public:
            Camera() = default;
            Camera(const glm::mat4& projection) : mProjection(projection) {}
            virtual ~Camera() = default;

            const glm::mat4& getProjection() { return mProjection; }
        proected:
            glm::mat4 mProjection = glm::mat4(1.0f);
    };

    class EditorCamera {
        public:
            EditorCamera() = default;
            EditorCamera(float fov, float aspectRatio, float nearPlane, float farPlane);

            void onUpdate();
           // void onEvent(SDL_Event& event);
        private:
            glm::mat4 mViewMatrix;
            glm::vec3 mPosition = {0.0f, 0.0f, 0.0f};
            glm::vec3 mFocalPoint = {0.0f, 0.0f, 0.0f};
            glm::vec2 mInitialMousePosition = {0.0f, 0.0f};
            float mFov = 45.0f, mAspectRatio = 1.778f, mNearPlane = 0.1f, mFarPlane = 1000.0f;
            float mDistance = 10.0f;
            float mPitch = 0.0f, mYaw = 0.0f;
            float mViewportWidth = 1280, mViewportHeight = 720;
    };
}
