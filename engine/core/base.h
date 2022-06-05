#pragma once

#include <memory>

#include "platformDetection.h"

#ifdef MAN520_DEBUG
	#if defined(MAN520_PLATFORM_WINDOWS)
		#define MAN520_DEBUGBREAK() __debugbreak()
	#elif defined(MAN520_PLATFORM_LINUX) || defined(MAN520_PLATFORM_MACOS)
 		#include <signal.h>
		#define MAN520_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define MAN520_ENABLE_ASSERTS
#else
	#define MAN520_DEBUGBREAK()
#endif

#define MAN520_EXPAND_MACRO(x) x
#define MAN520_STRINGIFY_MACRO(x) #x

namespace Man520 {
  
  template<typename T>
  using Scope = std::unique_ptr<T>;
  template<typename T, typename ... Args>
  constexpr Scope<T> createScope(Args&& ... args) {
      return std::make_unique<T>(std::forward<Args>(args)...);
  }   
  
  template <typename T>
  using Ref = std::shared_ptr<T>;
  template<typename T, typename ... Args>
  constexpr Ref<T> createRef(Args&& ... args) {
      return std::make_shared<T>(std::forward<Args>(args)...);
  }

}

#include "assert.h"
#include "log.h"
