#include "mzpch.h"
#include "openGLBuffer.h"

#include <glad/glad.h>

namespace Man520 {
    
    OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size) {
#ifdef MAN520_PLATFORM_MACOS
        glGenBuffers(1, &mRendererID);
#else
        glCreateBuffers(1, &mRendererID);
#endif
        glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) {
#ifdef MAN520_PLATFORM_MACOS
        glGenBuffers(1, &mRendererID);
#else
        glCreateBuffers(1, &mRendererID);
#endif
        glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &mRendererID);
    }

    void OpenGLVertexBuffer::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
    }

    void OpenGLVertexBuffer::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void OpenGLVertexBuffer::setData(const void* data, uint32_t size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : mCount(count) {
#ifdef MAN520_PLATFORM_MACOS
        glGenBuffers(1, &mRendererID);
#else
        glCreateBuffers(1, &mRendererID);
#endif
        // GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
        // Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state. 
        glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
        glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        glDeleteBuffers(1, &mRendererID);
    }

    void OpenGLIndexBuffer::bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
    }

    void OpenGLIndexBuffer::unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

}

