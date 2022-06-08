#include "openGLShader.h"
#include "mzpch.h"

#include <glad/glad.h>
#include <gtc/type_ptr.hpp>

#include <fstream>

namespace Man520 {

    OpenGLShader::OpenGLShader(const std::string& filepath) {
    
    }

    OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {
        mName = name;
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try 
        {
            // open files
            vShaderFile.open(vertexSrc.c_str());
            fShaderFile.open(fragmentSrc.c_str());
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode   = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            MAN520_CORE_ERROR("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: {0}", e.what());
        }
        const char* vShaderCode = vertexCode.c_str();
        const char * fShaderCode = fragmentCode.c_str();
        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        // shader Program
        mRendererID = glCreateProgram();
        glAttachShader(mRendererID, vertex);
        glAttachShader(mRendererID, fragment);
        glLinkProgram(mRendererID);
        checkCompileErrors(mRendererID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    OpenGLShader::~OpenGLShader() {
        glDeleteProgram(mRendererID);
    }

    void OpenGLShader::bind()  {
        glUseProgram(mRendererID);    
    }
    
    void OpenGLShader::unbind()  {
        glUseProgram(0);
    }
    
    void OpenGLShader::setBool(const std::string &name, bool value) const  {
        uploadUniformInt(name, (int)value);
    }
    
    void OpenGLShader::setInt(const std::string &name, int value) const  {
        uploadUniformInt(name, value);   
    }

    void OpenGLShader::setIntArray(const std::string& name, int* values, uint32_t count) const  {
        uploadUniformIntArray(name, values, count);
    }

    void OpenGLShader::setFloat(const std::string &name, float value) const  {
        uploadUniformFloat(name, value);
    }

    void OpenGLShader::setVec2(const std::string &name, const glm::vec2 &value) const  {
        uploadUniformFloat2(name, value);
    }

    void OpenGLShader::setVec2(const std::string &name, float x, float y) const  {
        uploadUniformFloat2(name, glm::vec2(x, y));
    }

    void OpenGLShader::setVec3(const std::string &name, const glm::vec3 &value) const  {
        uploadUniformFloat3(name, value);
    }

    void OpenGLShader::setVec3(const std::string &name, float x, float y, float z) const  {
        uploadUniformFloat3(name, glm::vec3(x, y, z));
    }

    void OpenGLShader::setVec4(const std::string &name, const glm::vec4 &value) const  {
        uploadUniformFloat4(name, value);
    }

    void OpenGLShader::setVec4(const std::string &name, float x, float y, float z, float w) const  {
        uploadUniformFloat4(name, glm::vec4(x, y, z, w));
    }

    void OpenGLShader::setMat2(const std::string &name, const glm::mat2 &mat) const  {
        uploadUniformMat2(name, mat);    
    }
    
    void OpenGLShader::setMat3(const std::string &name, const glm::mat3 &mat) const  {
        uploadUniformMat3(name, mat);
    }

    void OpenGLShader::setMat4(const std::string &name, const glm::mat4 &mat) const  {
        uploadUniformMat4(name, mat);
    }

    void OpenGLShader::uploadUniformInt(const std::string& name, int value) const {
        GLint location = glGetUniformLocation(mRendererID, name.c_str());
        glUniform1i(location, value); 
    }

    void OpenGLShader::uploadUniformIntArray(const std::string& name, int* values, uint32_t count) const {
        GLint location = glGetUniformLocation(mRendererID, name.c_str());
        glUniform1iv(location, count, values);
    }

    void OpenGLShader::uploadUniformFloat(const std::string& name, float value) const {
        GLint location = glGetUniformLocation(mRendererID, name.c_str());
        glUniform1f(location, value);
    }

    void OpenGLShader::uploadUniformFloat2(const std::string& name, const glm::vec2& value) const {
        GLint location = glGetUniformLocation(mRendererID, name.c_str());
        glUniform2f(location, value.x, value.y);
    }

    void OpenGLShader::uploadUniformFloat3(const std::string& name, const glm::vec3& value) const {
        GLint location = glGetUniformLocation(mRendererID, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void OpenGLShader::uploadUniformFloat4(const std::string& name, const glm::vec4& value) const {
        GLint location = glGetUniformLocation(mRendererID, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::uploadUniformMat2(const std::string& name, const glm::mat2& matrix) const {
        GLint location = glGetUniformLocation(mRendererID, name.c_str());
        glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::uploadUniformMat3(const std::string& name, const glm::mat3& matrix) const {
        GLint location = glGetUniformLocation(mRendererID, name.c_str());
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::uploadUniformMat4(const std::string& name, const glm::mat4& matrix) const {
        GLint location = glGetUniformLocation(mRendererID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void OpenGLShader::checkCompileErrors(unsigned int shader, std::string type) {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                MAN520_CORE_ERROR("ERROR::SHADER_COMPILATION_ERROR of type: {0}", infoLog);
            }
        } else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                MAN520_CORE_ERROR("ERROR::PROGRAM_LINKING_ERROR of type: {0}", infoLog);
            }
        }
    }

}
