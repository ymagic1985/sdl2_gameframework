#pragma once

#include <string>
#include <unordered_map>

#include <glm.hpp>

#include "core/base.h"

namespace Man520 {
    
    class Shader {
        public:
            virtual ~Shader() = default;

            virtual void bind() = 0;
            virtual void unbind() = 0;

            virtual void setBool(const std::string &name, bool value) const = 0;
            virtual void setInt(const std::string &name, int value) const = 0;
            virtual void setIntArray(const std::string& name, int* values, uint32_t count) const = 0;
            virtual void setFloat(const std::string &name, float value) const = 0;
            virtual void setVec2(const std::string &name, const glm::vec2 &value) const = 0;
            virtual void setVec2(const std::string &name, float x, float y) const = 0;
            virtual void setVec3(const std::string &name, const glm::vec3 &value) const = 0;
            virtual void setVec3(const std::string &name, float x, float y, float z) const = 0;
            virtual void setVec4(const std::string &name, const glm::vec4 &value) const = 0;
            virtual void setVec4(const std::string &name, float x, float y, float z, float w) const = 0;
            virtual void setMat2(const std::string &name, const glm::mat2 &mat) const = 0;
            virtual void setMat3(const std::string &name, const glm::mat3 &mat) const = 0;
            virtual void setMat4(const std::string &name, const glm::mat4 &mat) const = 0;
        
            virtual const std::string& getName() const = 0;

            static Ref<Shader> create(const std::string& filepath);
            static Ref<Shader> create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
    };
    
    class ShaderLibrary {
        public:
            void add(const std::string& name, const Ref<Shader>& shader);
            void add(const Ref<Shader>& shader);
            Ref<Shader> load(const std::string& filepath);
            Ref<Shader> load(const std::string& name, const std::string& filepath);
            Ref<Shader> get(const std::string& name);
            bool exists(const std::string& name) const;
        private:
            std::unordered_map<std::string, Ref<Shader>> mShaders;
    };

}

