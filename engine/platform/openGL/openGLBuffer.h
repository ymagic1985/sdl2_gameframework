#pragma once

#include "renderer/buffer.h"

namespace Man520 {

    class OpenGLVertexBuffer : public VertexBuffer {
	public:
            OpenGLVertexBuffer(uint32_t size);
            OpenGLVertexBuffer(float* vertices, uint32_t size);
            virtual ~OpenGLVertexBuffer();

            virtual void bind() const override;
            virtual void unbind() const override;
            virtual void setData(const void* data, uint32_t size) override;
            virtual const BufferLayout& getLayout() const override { return mLayout; }
            virtual void setLayout(const BufferLayout& layout) override { mLayout = layout; }
	private:
            uint32_t mRendererID;
            BufferLayout mLayout;
    };

    class OpenGLIndexBuffer : public IndexBuffer {
	public:
            OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
            virtual ~OpenGLIndexBuffer();

            virtual void bind() const;
            virtual void unbind() const;
            virtual uint32_t getCount() const { return mCount; }
	private:
            uint32_t mRendererID;
            uint32_t mCount;
    };

}
