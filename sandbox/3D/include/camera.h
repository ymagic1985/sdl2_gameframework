#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>

const float YAW         = -90.0f;
const float PITCH       = 0.0f;
const float SPEED       = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM        = 45.0f;

class Camera {
    public:
        enum class DIRECTION {
            FORWARD,
            BACKWARD,
            LEFT,
            RIGHT
        };

        Camera(const glm::vec3& pos = glm::vec3(0.0f, 0.0f, 0.0f), 
               const glm::vec3& up  = glm::vec3(0.0f, 1.0f, 0.0f),
               float yaw = YAW, float pitch = PITCH) : mPosition{pos},
               mUp{up}, mYaw{yaw}, mPitch{pitch}, mSpeed{SPEED}, 
               mFront{glm::vec3(0.0f, 0.0f, -1.0f)} {
            updateCameraVectors();
        }

        ~Camera() {}

        void move(DIRECTION d, float dt) {
            float speed = mSpeed * dt;
//            std::cout<<"speed: "<<speed<<"   dt: "<<dt<<"   fps:"<<1.0f/dt<<"\n";
            switch (d) {
                case DIRECTION::FORWARD:
                    mPosition += speed * mFront;
                    break;
                case DIRECTION::BACKWARD:
                    mPosition -= speed * mFront;
                    break;
                case DIRECTION::LEFT:
                    mPosition -= glm::normalize(glm::cross(mFront, mUp)) * speed;
                    break;
                case DIRECTION::RIGHT:
                    mPosition += glm::normalize(glm::cross(mFront, mUp)) * speed;
                    break;
            }
        } 

        void lookAround(float yawoffset, float pitchoffset) {
            mYaw += yawoffset;
            mPitch -= pitchoffset;
            if(mPitch > 89.0f) mPitch = 89.0f;
            if(mPitch < -89.0f) mPitch = -89.0f;
            updateCameraVectors();
        }

        glm::mat4 getViewMat4() const { 
            return glm::lookAt(mPosition, mPosition + mFront, mUp);
        }

        glm::vec3 getPosition() const { return mPosition; }
    private:
        void updateCameraVectors() {
            glm::vec3 front;
            front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
            front.y = sin(glm::radians(mPitch));
            front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
            mFront = glm::normalize(front);
        }

        glm::vec3 mUp;
        glm::vec3 mRight;
        glm::vec3 mPosition;
        glm::vec3 mFront;
        float mPitch;
        float mYaw;
        float mSpeed;
};


        
