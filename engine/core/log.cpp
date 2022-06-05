#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#include "log.h"

namespace Man520 {

    Ref<spdlog::logger> Log::sCoreLogger;
    Ref<spdlog::logger> Log::sClientLogger;
    
    void Log::init() {
        std::vector<spdlog::sink_ptr> logSinks;
        logSinks.emplace_back(createRef<spdlog::sinks::stdout_color_sink_mt>());
        logSinks.emplace_back(createRef<spdlog::sinks::basic_file_sink_mt>("Man520.log", true));

        logSinks[0]->set_pattern("%^[%T] %n: %v%$");
        logSinks[1]->set_pattern("[%T] [%l] %n: %v");

        sCoreLogger = createRef<spdlog::logger>("CORE", begin(logSinks), end(logSinks));
        spdlog::register_logger(sCoreLogger);
        sCoreLogger->set_level(spdlog::level::trace);
        sCoreLogger->flush_on(spdlog::level::trace);

        sClientLogger = createRef<spdlog::logger>("APP", begin(logSinks), end(logSinks));
        spdlog::register_logger(sClientLogger);
        sClientLogger->set_level(spdlog::level::trace);
        sClientLogger->flush_on(spdlog::level::trace);
    }

}
