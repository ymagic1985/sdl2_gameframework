#pragma once

#include <filesystem>
#include "base.h"
#include "log.h"

#ifdef MAN520_ENABLE_ASSERTS
  // Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
  // provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
  #define MAN520_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { MAN520##type##ERROR(msg, __VA_ARGS__); MAN520_DEBUGBREAK(); } }
  //#define MAN520_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { MANS20##TYPE##ERROR(msg, __VA_ARGS__); MANS20_DEBUGBREAK(); } }
  #define MAN520_INTERNAL_ASSERT_WITH_MSG(type, check, ...) MAN520_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
  #define MAN520_INTERNAL_ASSERT_NO_MSG(type, check) MAN520_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", MAN520_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

  #define MAN520_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
  #define MAN520_INTERNAL_ASSERT_GET_MACRO(...) MAN520_EXPAND_MACRO( MAN520_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, MAN520_INTERNAL_ASSERT_WITH_MSG, MAN520_INTERNAL_ASSERT_NO_MSG) )

  // Currently accepts at least the condition and one additional parameter (the message) being optional
  #define MAN520_ASSERT(...) MAN520_EXPAND_MACRO( MAN520_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
  #define MAN520_CORE_ASSERT(...) MAN520_EXPAND_MACRO( MAN520_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
        /*#define MAN520_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!check) { MANS20##TYPE##ERROR(msg, __VA_ARGS__); MANS20_DEBUGBREAK(); } }
        #define MANS20_INTERNAL_ASSERT_WITH_MSG(type, check, ...) MAN520_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
        #define MANS20_INTERNAL_ASSERT_NO_MSG(type, check) MAN520_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", \
            MAN520_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

        #define MAN520_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
        #define MAN520_INTERNAL_ASSERT_GET_MACRO MAN520_EXPAND_MACRO( MAN520_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, MAN520_INTERNAL_ASSERT_WITH_MSG, \
            MAN520_INTERNAL_ASSERT_NO_MSG) )

        #define MAN520_ASSERT(...) MAN520_EXPAND_MACRO(MAN520_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_,__VA_ARGS__) )
        #define MAN520_CORE_ASSERT(...) MAN520_EXPAND_MACRO( MAN520_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )*/
#else
  #define MAN520_ASSERT(...)
  #define MAN520_CORE_ASSERT(...)
#endif

