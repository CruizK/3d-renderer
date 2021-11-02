#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>


std::shared_ptr<spdlog::logger> Log::_coreLogger = nullptr;

void Log::Init()
{
  spdlog::set_pattern("%^[%T] %n: %v%$");
  _coreLogger = spdlog::stdout_color_mt("Core");
  _coreLogger->set_level(spdlog::level::trace);
}
