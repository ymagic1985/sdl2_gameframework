#pragma once
#include "mzpch.h"

namespace Man520 {

    enum class ShaderDataType {
        None = 0,
        Float, 
        Float2,
        Float3,
        Float4,
        Mat3,
        Mat4,
        Int,
        Int2,
        Int3,
        Int4,
        Bool
    };

    static uint32_t ShaderDataTypeSize(ShaderDataType type) {
        switch(type) {
            case ShaderDataType::Float:  return 4;
            case ShaderDataType::Float2: return 4 * 2;
            case ShaderDataType::Float3: return 4 * 3;
            case ShaderDataType::Float4: return 4 * 4;
            case ShaderDataType::Mat3:   return 4 * 3 * 3;
            case ShaderDataType::Mat4:   return 4 * 4 * 4;
            case ShaderDataType::Int:    return 4;
            case ShaderDataType::Int2:   return 4 * 2;
            case ShaderDataType::Int3:   return 4 * 3;
            case ShaderDataType::Int4:   return 4 * 4;
            case ShaderDataType::Bool:   return 1;
            default: return 0;
        }

        MAN520_CORE_ERROR("Unknown ShaderDataType passed in ShaderDataTypeSize()");
        return 0;
    }

    struct BufferElement {
        std::string Name;
        ShaderDataType Type;
        uint32_t Size;
        size_t Offset;
        bool Normalized;

        BufferElement() = default;

        BufferElement(ShaderDataType type, const std::string& name, bool normalized = false) : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {}

        uint32_t getComponentCount() const {
            switch(Type) {
                case ShaderDataType::Float:   return 1;
                case ShaderDataType::Float2:  return 2;
                case ShaderDataType::Float3:  return 3;
                case ShaderDataType::Float4:  return 4;
                case ShaderDataType::Mat3:    return 3; // 3* float3
                case ShaderDataType::Mat4:    return 4; // 4* float4
                case ShaderDataType::Int:     return 1;
                case ShaderDataType::Int2:    return 2;
                case ShaderDataType::Int3:    return 3;
                case ShaderDataType::Int4:    return 4;
                case ShaderDataType::Bool:    return 1;
                default: return 0;
            }

            MAN520_CORE_ERROR("Unknown ShaderDataType passed in getComponentCount()");
            return 0;
        }
    };

    class BufferLayout {
        public:
            BufferLayout() {}

            BufferLayout(std::initializer_list<BufferElement> elements) : mElements(elements) {
                calculateOffsetsAndStride();
            }

            uint32_t getStride() const { return mStride; }
            const std::vector<BufferElement>& getElements() const { return mElements; }

            std::vector<BufferElement>::iterator begin() { return mElements.begin(); }
            std::vector<BufferElement>::iterator end() { return mElements.end(); }
            std::vector<BufferElement>::const_iterator begin() const { return mElements.begin(); }
            std::vector<BufferElement>::const_iterator end() const { return mElements.end(); }
        private:
            void calculateOffsetsAndStride() {
                size_t offset = 0;
                mStride = 0;
                for(auto& element : mElements) {
                    element.Offset = offset;
                    offset += element.Size;
                    mStride += element.Size;
                }
            }
        private:
            std::vector<BufferElement> mElements;
            uint32_t mStride = 0;
    };

    class VertexBuffer {
        public:
            virtual ~VertexBuffer() = default;

            virtual void bind() const = 0;
            virtual void unbind() const = 0;

            virtual void setData(const void* data, uint32_t size) = 0;

            virtual const BufferLayout& getLayout() const = 0;
            virtual void setLayout(const BufferLayout& layout) = 0;

            static Ref<VertexBuffer> create(uint32_t size);
            static Ref<VertexBuffer> create(float* vertices, uint32_t size);
    };

    //supports 32-bit index buffers only for now
    class IndexBuffer {
        public:
            virtual ~IndexBuffer() = default;

            virtual void bind() const = 0;
            virtual void unbind() const = 0;
            virtual uint32_t getCount() const = 0;

            static Ref<IndexBuffer> create(uint32_t* indices, uint32_t count);
    };

}
