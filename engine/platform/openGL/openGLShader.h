#pragma once

#include "renderer/shader.h"


namespace Man520 {
    
    class OpenGLShader : public Shader {
        public:
            OpenGLShader(const std::string& filepath);
            OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
            virtual ~OpenGLShader();

            virtual void bind() override;
            virtual void unbind() override;

            virtual void setBool(const std::string &name, bool value) const override;
            virtual void setInt(const std::string &name, int value) const override;
            virtual void setIntArray(const std::string& name, int* values, uint32_t count) const override;
            virtual void setFloat(const std::string &name, float value) const override;
            virtual void setVec2(const std::string &name, const glm::vec2 &value) const override;
            virtual void setVec2(const std::string &name, float x, float y) const override;
            virtual void setVec3(const std::string &name, const glm::vec3 &value) const override;
            virtual void setVec3(const std::string &name, float x, float y, float z) const override;
            virtual void setVec4(const std::string &name, const glm::vec4 &value) const override;
            virtual void setVec4(const std::string &name, float x, float y, float z, float w) const override;
            virtual void setMat2(const std::string &name, const glm::mat2 &mat) const override;
            virtual void setMat3(const std::string &name, const glm::mat3 &mat) const override;
            virtual void setMat4(const std::string &name, const glm::mat4 &mat) const override;
        
            virtual const std::string& getName() const override { return mName; }
           
            void uploadUniformInt(const std::string& name, int value) const;
            void uploadUniformIntArray(const std::string& name, int* values, uint32_t count) const;
            void uploadUniformFloat(const std::string& name, float value) const;
            void uploadUniformFloat2(const std::string& name, const glm::vec2& value) const;
            void uploadUniformFloat3(const std::string& name, const glm::vec3& value) const;
            void uploadUniformFloat4(const std::string& name, const glm::vec4& value) const;
            void uploadUniformMat2(const std::string& name, const glm::mat2& matrix) const;
            void uploadUniformMat3(const std::string& name, const glm::mat3& matrix) const;
            void uploadUniformMat4(const std::string& name, const glm::mat4& matrix) const;
        private:
            std::string readFile(const std::string& filepath) { return std::string{}; };
            void checkCompileErrors(unsigned int shader, std::string type);
            //TODO: caching and 
        private:
            uint32_t mRendererID;
            std::string mFilePath;
            std::string mName;

    };

}


