#include "openGLContext.h"

#include <glad/glad.h>

namespace Man520 {
        
    OpenGLContext::OpenGLContext(SDL_Window* windowHandle) : mWindowHandle(windowHandle) {
        MAN520_CORE_ASSERT(windowHandle, "Window handle is null!");
    }
        
    OpenGLContext::~OpenGLContext() {
        SDL_GL_DeleteContext(mGLContext);
    }

    void OpenGLContext::init() {
        // Before we create our window, specify OpenGL version
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); //required on MAC
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);                                     
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);            
          
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);                                               
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        mGLContext = SDL_GL_CreateContext(mWindowHandle);
        int status = gladLoadGLLoader(SDL_GL_GetProcAddress);
        
        SDL_GL_MakeCurrent(mWindowHandle, mGLContext);
        SDL_GL_SetSwapInterval(1); // Enable vsync
        
        MAN520_CORE_ASSERT(status, "Failed to Initialize GLAD!");

        MAN520_CORE_INFO("OpenGL Info:");
        MAN520_CORE_INFO("  Vendor: {0}", std::string(reinterpret_cast<const char*>(glGetString(GL_VENDOR))));
        MAN520_CORE_INFO("  Renderer: {0}", std::string(reinterpret_cast<const char*>(glGetString(GL_RENDERER))));
        MAN520_CORE_INFO("  Version: {0}", std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));
        
#ifdef MAN520_PLATFORM_MACOS
        MAN520_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 1), "OpenGL version 4.1 or above is required!");
#else
        //TODO: upgrade openGL core version 4.5
        MAN520_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "OpenGL version 4.5 or above is required!");
#endif
    }

    void OpenGLContext::swapBuffers() {
        SDL_GL_SwapWindow(mWindowHandle);
    }

}

