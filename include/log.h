#pragma once

//This ignores all warnings rasied inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

#include "base.h"

namespace Man520 {

    class Log {
    public:
        static void init();
        
        static Ref<spdlog::logger>& getCoreLogger() { return sCoreLogger; }
        static Ref<spdlog::logger>& getClientLogger() { return sClientLogger; }

    private:
        static Ref<spdlog::logger> sCoreLogger;
        static Ref<spdlog::logger> sClientLogger;
    };

}

// Core log macros
#define MAN520_CORE_TRACE(...)    ::Man520::Log::getCoreLogger()->trace(__VA_ARGS__)
#define MAN520_CORE_INFO(...)     ::Man520::Log::getCoreLogger()->info(__VA_ARGS__)
#define MAN520_CORE_WARN(...)     ::Man520::Log::getCoreLogger()->warn(__VA_ARGS__)
#define MAN520_CORE_ERROR(...)    ::Man520::Log::getCoreLogger()->error(__VA_ARGS__)
#define MAN520_CORE_CRITICAL(...) ::Man520::Log::getCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define MAN520_TRACE(...)         ::Man520::Log::getClientLogger()->trace(__VA_ARGS__)
#define MAN520_INFO(...)          ::Man520::Log::getClientLogger()->info(__VA_ARGS__)
#define MAN520_WARN(...)          ::Man520::Log::getClientLogger()->warn(__VA_ARGS__)
#define MAN520_ERROR(...)         ::Man520::Log::getClientLogger()->error(__VA_ARGS__)
#define MAN520_CRITICAL(...)      ::Man520::Log::getClientLogger()->critical(__VA_ARGS__)
        
