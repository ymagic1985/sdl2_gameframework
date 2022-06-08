#include "openGLTexture.h"

#include <stb_image.h>

namespace Man520 {

    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height) : mWidth(width), mHeight(height) {
        mInternalFormat = GL_RGBA8;
        mDataFormat = GL_RGBA;

        glGenTextures(1, &mRendererID);
#ifdef MAN520_PLATFORM_MACOS //MACOS Stuck with OpenGL 4.1
        glBindTexture(GL_TEXTURE_2D, mRendererID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
#else
        //TODO: Upgrade openGL to verison 4.5 to support the following
        glCreateTextures(GL_TEXTURE_2D, 1, &mRendererID);
        glTextureStorage2D(mRendererID, 1, mInternalFormat, mWidth, mHeight);
#endif
      
        glTextureParameteri(mRendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(mRendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureParameteri(mRendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(mRendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : mPath(path), mInternalFormat(0), mDataFormat(0) {
#ifdef MAN520_PLATFORM_MACOS //MACOS Stuck with OpenGL 4.1
        glGenTextures(1, &mRendererID);
        glBindTexture(GL_TEXTURE_2D, mRendererID); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
#else
        glCreateTextures(GL_TEXTURE_2D, 1, &mRendererID);
#endif

        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);       // set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(1); //tell stb_image.h to flip loaded texture's on the y-axis
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            mWidth = width;
            mHeight = height;

            if(nrChannels == 4) {
                mInternalFormat = GL_RGBA8;
                mDataFormat = GL_RGBA;
            }
            else if(nrChannels == 3) {
                mInternalFormat = GL_RGB8;
                mDataFormat = GL_RGB;
            }

            MAN520_CORE_ASSERT(mInternalFormat & mDataFormat, "Format not supported!");
            
#ifdef MAN520_PLATFORM_MACOS //MACOS Stuck with OpenGL 4.1
            glTexImage2D(GL_TEXTURE_2D, 0, mInternalFormat, mWidth, mHeight, 0, mDataFormat, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
#else
            //TODO: Upgrade openGL to verison 4.5 to support the following
            glTextureStorage2D(mRendererID, 1, mInternalFormat, mWidth, mHeight);
            glTextureSubImage2D(mRendererID, 0, 0, 0, mWidth, mHeight, mDataFormat, GL_UNSIGNED_BYTE, data);
#endif
            stbi_image_free(data);
        }
        else {
            MAN520_CORE_WARN("Failed to load texture at: {0}", path);
        }
    }

    OpenGLTexture2D::~OpenGLTexture2D() {
        glDeleteTextures(1, &mRendererID);
    }

    void OpenGLTexture2D::setData(void* data, uint32_t size) {
        uint32_t bpp = mDataFormat == GL_RGBA ? 4 : 3;
        MAN520_CORE_ASSERT(size == mWidth * mHeight * bpp, "Data must be the entire texture!");
#ifdef MAN520_PLATFORM_MACOS //MACOS Stuck with OpenGL 4.1
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mWidth, mHeight, mDataFormat, GL_UNSIGNED_BYTE, data);
#else
        //TODO: Upgrade openGL to verison 4.5 to support the following
        glTextureSubImage2D(mRendererID, 0, 0, 0, mWidth, mHeight, mDataFormat, GL_UNSIGNED_BYTE, data);
#endif
    }

    void OpenGLTexture2D::bind(uint32_t slot) const {
        //TODO: Upgrade openGL to verison 4.5 to support the following
        //glBindTextureUnit(slot, mRendererID);
#ifdef MAN520_PLATFORM_MACOS //MACOS Stuck with OpenGL 4.1
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, mRendererID);
#else
        //TODO: Upgrade openGL to verison 4.5 to support the following
        //glBindTextureUnit(slot, mRendererID);
#endif
    }

    bool OpenGLTexture2D::operator==(const Texture& rhs) const {
        return mRendererID == ((OpenGLTexture2D&)rhs).mRendererID;
    }

}
