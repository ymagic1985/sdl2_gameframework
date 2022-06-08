
#include <glad/glad.h>

#include "openGLVertexArray.h"


namespace Man520 {

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:    return GL_FLOAT;
            case ShaderDataType::Float2:   return GL_FLOAT;
            case ShaderDataType::Float3:   return GL_FLOAT;
            case ShaderDataType::Float4:   return GL_FLOAT;
            case ShaderDataType::Mat3:     return GL_FLOAT;
            case ShaderDataType::Mat4:     return GL_FLOAT;
            case ShaderDataType::Int:      return GL_INT;
            case ShaderDataType::Int2:     return GL_INT;
            case ShaderDataType::Int3:     return GL_INT;
            case ShaderDataType::Int4:     return GL_INT;
            case ShaderDataType::Bool:     return GL_BOOL;
            default: break;
        }

        MAN520_CORE_ASSERT(false, "Unknown ShaderDataType passed in ShaderDataTypeToOpenGLBaseType!");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray() {
#ifdef MAN520_PLATFORM_MACOS
        glGenVertexArrays(1, &mRendererID);
#else
        glCreateVertexArrays(1, &mRendererID);
#endif
    }

    OpenGLVertexArray::~OpenGLVertexArray() {
        glDeleteVertexArrays(1, &mRendererID);
    }

    void OpenGLVertexArray::bind() const {
        glBindVertexArray(mRendererID);
    }

    void OpenGLVertexArray::unbind() const {
        glBindVertexArray(0);
    }
    
    void OpenGLVertexArray::addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
        MAN520_CORE_ASSERT(vertexBuffer->getLayout().getElements().size(), "Vertex Buffer has no layout!");
        glBindVertexArray(mRendererID);
        vertexBuffer->bind();

        const auto& layout = vertexBuffer->getLayout();
        for (const auto& element : layout) {
            switch (element.Type) {
                case ShaderDataType::Float:
                case ShaderDataType::Float2:
                case ShaderDataType::Float3:
                case ShaderDataType::Float4:
                {
                    glEnableVertexAttribArray(mVertexBufferIndex);
                    glVertexAttribPointer(mVertexBufferIndex,
                            element.getComponentCount(),
                            ShaderDataTypeToOpenGLBaseType(element.Type),
                            element.Normalized ? GL_TRUE : GL_FALSE,
                            layout.getStride(),
                            (const void*)element.Offset);
                    mVertexBufferIndex++;
                    break;
                }
                case ShaderDataType::Int:
                case ShaderDataType::Int2:
                case ShaderDataType::Int3:
                case ShaderDataType::Int4:
                case ShaderDataType::Bool:
                {
                    glEnableVertexAttribArray(mVertexBufferIndex);
                    glVertexAttribIPointer(mVertexBufferIndex,
                            element.getComponentCount(),
                            ShaderDataTypeToOpenGLBaseType(element.Type),
                            layout.getStride(),
                            (const void*)element.Offset);
                    mVertexBufferIndex++;
                    break;
                }
                case ShaderDataType::Mat3:
                case ShaderDataType::Mat4:
                {
                    uint8_t count = element.getComponentCount();
                    for (uint8_t i = 0; i < count; i++) {
                        glEnableVertexAttribArray(mVertexBufferIndex);
                        glVertexAttribPointer(mVertexBufferIndex,
                                count,
                                ShaderDataTypeToOpenGLBaseType(element.Type),
                                element.Normalized ? GL_TRUE : GL_FALSE,
                                layout.getStride(),
                                (const void*)(element.Offset + sizeof(float) * count * i));
                        glVertexAttribDivisor(mVertexBufferIndex, 1);
                        mVertexBufferIndex++;
                    }
                    break;
                }
                default:
                    MAN520_CORE_ASSERT(false, "Unknown ShaderDataType passed in OpenGLVertexArray::addVertexBuffer()");
            }
        }

        mVertexBuffers.push_back(vertexBuffer);
    }
    
    void OpenGLVertexArray::setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
        glBindVertexArray(mRendererID);
        indexBuffer->bind();
        mIndexBuffer = indexBuffer;
    }

}
